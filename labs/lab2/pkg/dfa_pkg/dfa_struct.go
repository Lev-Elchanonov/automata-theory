package dfa

import (
	"fmt"
	nfa "lab2/pkg/nfa_pkg"
	"os"
	"os/exec"
	"runtime"
	"sort"
	"strconv"
	"strings"
)

type DfaState struct {
	ID int
	NfaStates map[int]*nfa.NfaState
	Transitions map[byte]*DfaState
	IsAcceptable bool
	GroupInfo map[string]bool
}

type Dfa struct {
	StartState *DfaState
	States []*DfaState
	StateCount int
	Alphabet []byte
	AcceptStates []*DfaState
	ErrorState *DfaState
}

func newDfaState(id int, nfastates map[int]*nfa.NfaState) *DfaState {
	return &DfaState{
		ID : id,
		NfaStates : nfastates,
		Transitions : make(map[byte]*DfaState),
		IsAcceptable : false,
		GroupInfo : make(map[string]bool),
	}
}


func BuildDfaFromNfa(n *nfa.Nfa) *Dfa{
	dfa := &Dfa{
		States: make([]*DfaState, 0),
		StateCount : 0,
		Alphabet : collectAlpha(n),
		AcceptStates : make([]*DfaState, 0),
	}

	errorState := createErrorState(dfa)
	dfa.ErrorState = errorState


	startNfaStates := map[int]*nfa.NfaState{}
	startNfaStates[n.StartState.ID] = n.StartState
	startClosure := epsilonClosure(startNfaStates)

	dfaStartState := dfa.addState(startClosure)
	dfa.StartState = dfaStartState

	if isAcceptState(dfaStartState){
		dfaStartState.IsAcceptable = true
		dfa.AcceptStates = append(dfa.AcceptStates, dfaStartState)
	}

	unmarkedStates := []*DfaState{dfaStartState}
	markedStates := make(map[string]*DfaState)
	markedStates[stateKey(startClosure)] = dfaStartState

	for len(unmarkedStates) > 0 {
		current := unmarkedStates[0]
		unmarkedStates = unmarkedStates[1:]

		for _, symbol := range dfa.Alphabet{
			moveRes := move(current.NfaStates, symbol)
			epsClosure := epsilonClosure(moveRes)
			if len(epsClosure) == 0 {
				current.Transitions[symbol] = errorState
				continue
			}

			key := stateKey(epsClosure)
			var targetState *DfaState
			if existing, ok := markedStates[key]; ok {
				targetState = existing
			} else {
				targetState = dfa.addState(epsClosure)
				markedStates[key] = targetState
				unmarkedStates = append(unmarkedStates, targetState)
				if isAcceptState(targetState){
					targetState.IsAcceptable = true
					dfa.AcceptStates = append(dfa.AcceptStates, targetState)
				}
			}
			current.Transitions[symbol] = targetState
		}
	}
	return dfa
}


func (d* Dfa) addState(nfast map[int]*nfa.NfaState) *DfaState{
	d.StateCount++
	state := newDfaState(d.StateCount, nfast)
	d.States = append(d.States, state)
	return state
}

func isAcceptState(dfaSt *DfaState) bool {
	for _,nfaState := range dfaSt.NfaStates {
		if nfaState.IsAcceptable{
			return true
		}
	}
	return false
}

func epsilonClosure(states map[int]*nfa.NfaState) map[int]*nfa.NfaState {
	result := make(map[int]*nfa.NfaState)
	for id, state := range states {
		result[id] = state
	}

	stack := make([]*nfa.NfaState, 0, len(states))
	for _, state := range states {
		stack = append(stack, state)
	}

	for len(stack) > 0 {
		current := stack[len(stack)-1]
		stack = stack[:len(stack)-1]

		for _, epsTarget := range current.Epsilons {
			if _, exist := result[epsTarget.ID]; !exist {
				result[epsTarget.ID] = epsTarget
				stack = append(stack, epsTarget)
			}
		}
	}

	return result
}


func move(currentStates map[int]*nfa.NfaState, c byte) map[int]*nfa.NfaState {
	res := make(map[int]*nfa.NfaState)
	for _, state := range currentStates {
		if targets, exists := state.Transitions[c]; exists{
			for _, target := range targets {
				res[target.ID] = target
			}
		}
	}
	return res
}


func collectAlpha (n* nfa.Nfa) []byte {
	alphaMap := make(map[byte]bool)
	for _, state := range n.States {
		for ch := range state.Transitions {
			alphaMap[ch] = true
		}
	}
	alphabet := make([]byte, 0, len(alphaMap))
	for ch := range alphaMap {
		alphabet = append(alphabet, ch)
	}
	sort.Slice(alphabet, func(i, j int) bool {return alphabet[i] < alphabet[j]})
	return alphabet
}


func stateKey (states map[int]*nfa.NfaState) string {
	ids := make([]int, 0, len(states))
	for id := range states {
		ids = append(ids, id)
	}
	sort.Ints(ids)
	var strBuilder strings.Builder
	strBuilder.WriteString("{")
	for i, id := range ids{
		if i > 0{
			strBuilder.WriteString(",")
		}
		strBuilder.WriteString(strconv.Itoa(id))
	}
	strBuilder.WriteString("}")
	return strBuilder.String()
}


func createErrorState(n *Dfa) *DfaState{
	errorState := n.addState(map[int]*nfa.NfaState{})
	errorState.ID = -1
	for _, symbol := range n.Alphabet{
		errorState.Transitions[symbol] = errorState
	}
	errorState.IsAcceptable = false
	return errorState
}





func (d *Dfa) GraphViz() string {
	var builder strings.Builder

	builder.WriteString("digraph DFA {\n")
	builder.WriteString("  rankdir=LR;\n")  // слева направо
	builder.WriteString("  node [shape = circle];\n")

	builder.WriteString(fmt.Sprintf("  start [shape = point, label = \"\"];\n"))
	builder.WriteString(fmt.Sprintf("  start -> %d;\n", d.StartState.ID))


	for _, state := range d.AcceptStates {
		builder.WriteString(fmt.Sprintf("  %d [shape = doublecircle];\n", state.ID))
	}

	if d.ErrorState != nil {
		builder.WriteString(fmt.Sprintf("  %d [shape = circle, style = dashed, label = \"{}\"];\n",
			d.ErrorState.ID))
	}

	for _, state := range d.States {
		for ch, target := range state.Transitions {
			label := string(ch)
			if ch == '"' {
				label = "\\\""
			} else if ch == '\\' {
				label = "\\\\"
			}

			if target == d.ErrorState {
				builder.WriteString(fmt.Sprintf("  %d -> %d [label = \"%s\"];\n",
					state.ID, target.ID, label))
			} else {
				builder.WriteString(fmt.Sprintf("  %d -> %d [label = \"%s\"];\n",
					state.ID, target.ID, label))
			}
		}
	}

	builder.WriteString("}\n")
	return builder.String()
}


func (d *Dfa) openFile(filename string) error {
	var cmd *exec.Cmd

	switch runtime.GOOS {
	case "windows":
		cmd = exec.Command("cmd", "/c", "start", filename)
	case "darwin": // macOS
		cmd = exec.Command("open", filename)
	default: // Linux и другие Unix-like
		cmd = exec.Command("xdg-open", filename)
	}

	if err := cmd.Start(); err != nil {
		return fmt.Errorf("ошибка открытия файла: %v", err)
	}

	go cmd.Wait()
	return nil
}


func (d *Dfa) SaveAndOpenGraphViz(filename string) error {
	content := d.GraphViz()
	err := os.WriteFile(filename, []byte(content), 0644)
	if err != nil {
		return fmt.Errorf("ошибка сохранения файла: %v", err)
	}
	fmt.Printf("DOT файл сохранен: %s\n", filename)

	pngFilename := strings.TrimSuffix(filename, ".dot") + ".png"


	cmd := exec.Command("dot", "-Tpng", filename, "-o", pngFilename)
	if err := cmd.Run(); err != nil {
		return fmt.Errorf("ошибка генерации PNG (установлен ли graphviz?): %v", err)
	}
	fmt.Printf("PNG файл создан: %s\n", pngFilename)


	return d.openFile(pngFilename)
}



func (d *Dfa) PrintDebug(n *nfa.Nfa) {
	fmt.Println("=== Построение ДКА ===")

	fmt.Println("Состояния в массиве:")
	for i, state := range d.States {
		fmt.Printf("  d.States[%d] = ID:%d, NFA:%v\n",
			i, state.ID, stateKey(state.NfaStates))
	}
	fmt.Println()

	stateNames := make(map[*DfaState]string)
	nameIndex := 0
	for _, state := range d.States {
		if state == d.ErrorState {
			stateNames[state] = "ERR"
		} else {
			stateNames[state] = string('A' + byte(nameIndex))
			nameIndex++
		}
	}

	startKey := stateKey(d.StartState.NfaStates)
	fmt.Printf("1) Z_e(S0_NFA) = Z_e({%d}) = %s -> %s_D\n",
		n.StartState.ID, startKey, stateNames[d.StartState])

	for _, state := range d.States {
		if state == d.ErrorState {
			continue
		}
		stateName := stateNames[state]
		for _, symbol := range d.Alphabet {
			moveRes := move(state.NfaStates, symbol)
			oneStep := epsilonClosure(moveRes)

			moveKey := stateKey(moveRes)
			oneStepKey := stateKey(oneStep)

			target := state.Transitions[symbol]
			targetName := "C_D"
			if target != d.ErrorState {
				targetName = stateNames[target] + "_D"
			}

			fmt.Printf("   Z_e(T_%c(%s_D)) = Z_e(%s) = %s -> %s\n",
				symbol, stateName, moveKey, oneStepKey, targetName)
		}
	}

	fmt.Printf("3) Принимающие состояния — {")
	first := true
	for _, state := range d.AcceptStates {
		if !first {
			fmt.Printf(", ")
		}
		fmt.Printf("%s_D", stateNames[state])
		first = false
	}
	fmt.Println("}")
}