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

type Group struct {
	Id int
	States map[int]*DfaState
}
type Partition struct {
	Groups map[int]*Group
	GroupsCount int
}
func (p *Partition) addGroup(gr *Group) {
	p.Groups[gr.Id] = gr
	p.GroupsCount++
}

func Minimize(d *Dfa) *Dfa{
	pset := &Partition{
		Groups: make(map[int]*Group),
		GroupsCount: 0,
	}
	errorStates := make(map[int]*DfaState)
	errorStates[d.ErrorState.ID] = d.ErrorState
	errorGroup := createGroup(0, errorStates)
	pset.addGroup(errorGroup)

	acceptStates := createStatesMap(d.AcceptStates)
	acceptGroup := createGroup(1, acceptStates)
	notAcceptStates := make(map[int]*DfaState)
	for _, state := range d.States {
		if !state.IsAcceptable {
			notAcceptStates[state.ID] = state
		}
	}
	notAcceptStates[d.ErrorState.ID] = d.ErrorState
	notAcceptGroup := createGroup(2, notAcceptStates)


	pset.addGroup(acceptGroup)
	pset.addGroup(notAcceptGroup)

	cont := true
	for cont {
		cont = false
		newpset := &Partition{
			Groups: make(map[int]*Group),
			GroupsCount: 0,
		}
		groupIDs := make([]int, 0, len(pset.Groups))
		for id := range pset.Groups {
			groupIDs = append(groupIDs, id)
		}
		sort.Ints(groupIDs)

		for _, groupID := range groupIDs {
			group := pset.Groups[groupID]
			if groupID == 0 {
				group.Id = newpset.GroupsCount
				newpset.addGroup(group)
				continue
			}


			if len(group.States) == 1 {
				fmt.Printf("\tAlone state, GroupsCount: %d\n", newpset.GroupsCount)
				group.Id = newpset.GroupsCount
				newpset.addGroup(group)
				continue
			} // тривиальные группы пропускаем
			subgroups := splitGroup(group, d, pset)
			cont = true

			sort.Slice(subgroups, func(i, j int) bool {
				// получаем минимальный ID в каждой подгруппе
				minI := getMinStateID(subgroups[i])
				minJ := getMinStateID(subgroups[j])
				return minI < minJ
			})

			for _, subgroup := range subgroups {
				for _, state := range subgroup.States {
					fmt.Printf("#%d", state.ID)
				}
				subgroup.Id = newpset.GroupsCount
				fmt.Printf("  GroupsCount: %d\n", newpset.GroupsCount)
				newpset.addGroup(subgroup)

			}
			if len(subgroups) == 1 { cont = false }
		}
		pset = newpset
		print_pset(pset)
		fmt.Println("\n")
	}
	return buildMinimizedDFA(d, pset)
}

func getMinStateID(group *Group) int {
	minID := int(^uint(0) >> 1)
	for id := range group.States {
		if id < minID {
			minID = id
		}
	}
	return minID
}
func print_pset(pset *Partition) {
	for _, group := range pset.Groups {
		fmt.Printf("->%d: ", group.Id)
		for _, state := range group.States {
			fmt.Printf("%d,", state.ID)
		}
		fmt.Printf("\n")
	}
}
func createStatesMap (states []*DfaState) map[int]*DfaState {
	res := make(map[int]*DfaState, len(states))
	for _, state := range states {
		res[state.ID] = state
	}
	return res
}
func createGroup (id int, states map[int]*DfaState) *Group {
	return &Group{
		Id: id,
		States: states,
	}
}
func findGroup(curState *DfaState, pset *Partition) *Group{
	for _, group := range pset.Groups {
		if _,exists := group.States[curState.ID]; exists{
			return group
		}
	}
	return nil
}

/*
func splitGroup(group *Group, d *Dfa, pset *Partition) []*Group {
	signMap := make(map[string][]*DfaState)

	for _, state := range group.States {
		sig := make(map[byte]int)
		for _, symbol := range d.Alphabet {
			nextState := state.Transitions[symbol]
			if nextState != nil {
				foundedGroup := findGroup(nextState, pset)
				if (foundedGroup != nil) {
					sig[symbol] = foundedGroup.Id
				} else {
					sig[symbol] = -1
				}
			} else {
				sig[symbol] = -1
			}
		}
		key := signKey(sig, d.Alphabet)
		signMap[key] = append(signMap[key], state)
	}
	subgroups := make([]*Group, 0, len(signMap))
	for _, states := range signMap {
		stateMap := make(map[int]*DfaState)
		for _, state := range states {
			stateMap[state.ID] = state
		}
		subgroups = append(subgroups, &Group{
			States: stateMap,
		})
	}
	return subgroups
}
*/

func splitGroup(group *Group, d *Dfa, pset *Partition) []*Group {
	fmt.Printf("    Разбиение группы\n")
	for _, state := range group.States {
		fmt.Printf("%d, ", state.ID)
	}
	fmt.Printf("\n")

	signMap := make(map[string][]*DfaState)

	for _, state := range group.States {
		sig := make(map[byte]int)
		fmt.Printf("      Состояние %d: сигнатура [", state.ID)

		for _, symbol := range d.Alphabet {
			nextState := state.Transitions[symbol]
			if nextState != nil {
				foundedGroup := findGroup(nextState, pset)
				if foundedGroup != nil {
					sig[symbol] = foundedGroup.Id
					fmt.Printf(" %c->%d", symbol, foundedGroup.Id)
				} else {
					sig[symbol] = -1
					fmt.Printf(" %c->-1", symbol)
				}
			} else {
				sig[symbol] = -1
				fmt.Printf(" %c->-1", symbol)
			}
		}
		fmt.Printf(" ]\n")

		key := signKey(sig, d.Alphabet)
		signMap[key] = append(signMap[key], state)
	}

	keys := make([]string, 0, len(signMap))
	for key := range signMap {
		keys = append(keys, key)
	}
	sort.Strings(keys)

	fmt.Printf("      Получено подгрупп: %d\n", len(signMap))
	for key, states := range signMap {
		ids := make([]int, 0, len(states))
		for _, s := range states {
			ids = append(ids, s.ID)
		}
		sort.Ints(ids)
		fmt.Printf("        Ключ %s: %v\n", key, ids)
	}

	subgroups := make([]*Group, 0, len(signMap))
	for _, states := range signMap {
		stateMap := make(map[int]*DfaState)
		for _, state := range states {
			stateMap[state.ID] = state
		}
		subgroups = append(subgroups, &Group{
			States: stateMap,
		})
	}
	return subgroups
}


func signKey(sig map[byte]int, alphabet []byte) string {
	var builder strings.Builder
	for _, symbol := range alphabet {
		builder.WriteString(fmt.Sprintf("%d|", sig[symbol]))
	}
	return builder.String()
}

/*
func buildMinimizedDFA(oldDfa *Dfa, partition *Partition) *Dfa {
	newDfa := &Dfa{
		Alphabet:     oldDfa.Alphabet,
		States:       make([]*DfaState, 0),
		AcceptStates: make([]*DfaState, 0),
		StateCount:   0,
	}

	groupToState := make(map[int]*DfaState)

	// добавили все состояния в автомат
	for _, group := range partition.Groups {
		newState := newDfaState(newDfa.StateCount, nil)
		newDfa.StateCount++
		newDfa.States = append(newDfa.States, newState)
		groupToState[group.Id] = newState

		for _, state := range group.States {
			if state.IsAcceptable {
				newState.IsAcceptable = true
				newDfa.AcceptStates = append(newDfa.AcceptStates, newState)
				break
			}
		}

		for _, state := range group.States {
			if state == oldDfa.StartState {
				newDfa.StartState = newState
				break
			}
		}
	}

	// переходы
	for _, group := range partition.Groups {
		var representative *DfaState
		for _, state := range group.States {
			representative = state
			break
		}

		newState := groupToState[group.Id]

		for _, symbol := range newDfa.Alphabet {
			nextState := representative.Transitions[symbol]
			if nextState != nil {
				targetGroup := findGroup(nextState, partition)
				if targetGroup != nil {
					newState.Transitions[symbol] = groupToState[targetGroup.Id]
				}
			}
		}
	}

	return newDfa
}
*/


func buildMinimizedDFA(oldDfa *Dfa, partition *Partition) *Dfa {
	fmt.Println("\n=== ПОСТРОЕНИЕ МИНИМАЛЬНОГО ДКА ===")

	newDfa := &Dfa{
		Alphabet:     oldDfa.Alphabet,
		States:       make([]*DfaState, 0),
		AcceptStates: make([]*DfaState, 0),
		StateCount:   0,
		ErrorState:   nil,
	}

	groupToState := make(map[int]*DfaState)

	// Сортируем группы для детерминированного порядка
	groupIDs := make([]int, 0, len(partition.Groups))
	for id := range partition.Groups {
		groupIDs = append(groupIDs, id)
	}
	sort.Ints(groupIDs)

	fmt.Println("Группы в финальном разбиении:")
	for _, groupID := range groupIDs {
		group := partition.Groups[groupID]
		ids := make([]int, 0, len(group.States))
		for id := range group.States {
			ids = append(ids, id)
		}
		sort.Ints(ids)

		// Проверяем, есть ли в группе принимающие состояния
		hasAcceptable := false
		for _, state := range group.States {
			if state.IsAcceptable {
				hasAcceptable = true
				break
			}
		}
		fmt.Printf("  Группа %d: %v (принимающая: %v)\n", groupID, ids, hasAcceptable)
	}

	// Создаем новые состояния
	for _, groupID := range groupIDs {
		group := partition.Groups[groupID]

		newState := newDfaState(newDfa.StateCount, nil)
		newDfa.StateCount++
		newDfa.States = append(newDfa.States, newState)
		groupToState[groupID] = newState

		// Проверяем, является ли группа принимающей
		for _, state := range group.States {
			if state.IsAcceptable {
				newState.IsAcceptable = true
				newDfa.AcceptStates = append(newDfa.AcceptStates, newState)
				fmt.Printf("  Состояние %d (группа %d) помечено как принимающее\n",
					newState.ID, groupID)
				break
			}
		}

		// Проверяем, является ли группа начальной
		for _, state := range group.States {
			if state == oldDfa.StartState {
				newDfa.StartState = newState
				fmt.Printf("  Состояние %d (группа %d) - начальное\n",
					newState.ID, groupID)
				break
			}
		}

		// Проверяем, является ли группа состоянием ошибки
		for _, state := range group.States {
			if state == oldDfa.ErrorState {
				newDfa.ErrorState = newState
				fmt.Printf("  Состояние %d (группа %d) - состояние ошибки\n",
					newState.ID, groupID)
				break
			}
		}
	}

	// Добавляем переходы
	for _, groupID := range groupIDs {
		group := partition.Groups[groupID]
		newState := groupToState[groupID]

		// Берем представителя группы
		var representative *DfaState
		for _, state := range group.States {
			representative = state
			break
		}

		for _, symbol := range newDfa.Alphabet {
			nextState := representative.Transitions[symbol]
			if nextState != nil {
				targetGroup := findGroup(nextState, partition)
				if targetGroup != nil {
					newState.Transitions[symbol] = groupToState[targetGroup.Id]
				}
			}
		}
	}

	return newDfa
}




func (d *Dfa) DebugPrint() {
	fmt.Println("\n=== ДЕТАЛЬНЫЙ ДЕБАГ ДКА ===")
	fmt.Printf("Всего состояний: %d\n", len(d.States))
	fmt.Printf("Алфавит: %s\n", string(d.Alphabet))
	fmt.Printf("Начальное состояние: %d\n", d.StartState.ID)

	// Принимающие состояния
	fmt.Printf("Принимающие состояния (%d шт): ", len(d.AcceptStates))
	for i, state := range d.AcceptStates {
		if i > 0 {
			fmt.Printf(", ")
		}
		fmt.Printf("%d", state.ID)
	}
	fmt.Println()

	// Состояние ошибки
	if d.ErrorState != nil {
		fmt.Printf("Состояние ошибки: %d\n", d.ErrorState.ID)
	}

	fmt.Println("\n--- Таблица переходов ---")

	// Заголовок
	fmt.Printf("%-10s", "Состояние")
	for _, sym := range d.Alphabet {
		fmt.Printf(" | '%c'", sym)
	}
	fmt.Println()
	fmt.Println(strings.Repeat("-", 10+len(d.Alphabet)*8))

	// Сортируем состояния для красивого вывода
	states := make([]*DfaState, 0, len(d.States))
	for _, state := range d.States {
		states = append(states, state)
	}
	sort.Slice(states, func(i, j int) bool { return states[i].ID < states[j].ID })

	for _, state := range states {
		// Маркеры для особых состояний
		marker := "  "
		if state == d.ErrorState {
			marker = "ERR"
		} else if state.IsAcceptable {
			marker = "ACC"
		} else if state == d.StartState {
			marker = "STR"
		}

		fmt.Printf("%-10s", fmt.Sprintf("%d %s", state.ID, marker))

		for _, sym := range d.Alphabet {
			nextState := state.Transitions[sym]
			if nextState != nil {
				fmt.Printf(" | %-6d", nextState.ID)
			} else {
				fmt.Printf(" | %-6s", "—")
			}
		}
		fmt.Println()
	}
}

// DebugPartition выводит информацию о текущем разбиении при минимизации
func (p *Partition) DebugPrint(step int) {
	fmt.Printf("\n=== Шаг %d: Разбиение ===\n", step)
	fmt.Printf("Всего групп: %d\n", p.GroupsCount)

	// Сортируем группы по ID
	groups := make([]*Group, 0, len(p.Groups))
	for _, group := range p.Groups {
		groups = append(groups, group)
	}
	sort.Slice(groups, func(i, j int) bool { return groups[i].Id < groups[j].Id })

	for _, group := range groups {
		// Собираем ID состояний в группе
		stateIDs := make([]int, 0, len(group.States))
		for id := range group.States {
			stateIDs = append(stateIDs, id)
		}
		sort.Ints(stateIDs)

		// Форматируем вывод
		statesStr := fmt.Sprintf("%v", stateIDs)
		fmt.Printf("  Группа %2d: %s\n", group.Id, statesStr)
	}
}

// DebugMinimizationProcess показывает весь процесс минимизации
func (d *Dfa) DebugMinimizationProcess() {
	fmt.Println("\n=== ПРОЦЕСС МИНИМИЗАЦИИ ДКА ===")

	// Шаг 1: Начальное разбиение
	fmt.Println("\n--- Шаг 1: Начальное разбиение ---")
	acceptIDs := make([]int, 0, len(d.AcceptStates))
	for _, state := range d.AcceptStates {
		acceptIDs = append(acceptIDs, state.ID)
	}
	sort.Ints(acceptIDs)
	fmt.Printf("Принимающие состояния: %v\n", acceptIDs)

	nonAcceptIDs := make([]int, 0)
	for _, state := range d.States {
		if !state.IsAcceptable && state != d.ErrorState {
			nonAcceptIDs = append(nonAcceptIDs, state.ID)
		}
	}
	sort.Ints(nonAcceptIDs)
	fmt.Printf("Непринимающие состояния: %v\n", nonAcceptIDs)

	if d.ErrorState != nil {
		fmt.Printf("Состояние ошибки: %d\n", d.ErrorState.ID)
	}
}