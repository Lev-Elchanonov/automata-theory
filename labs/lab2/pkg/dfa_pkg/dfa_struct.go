package dfa

import (
	"fmt"
	nfa "lab2/pkg/nfa_pkg"
	reg "lab2/pkg/regex_pkg"
	"sort"
	"strconv"
	"strings"
)

type DfaState struct {
	ID int
	NfaStates map[int]*nfa.NfaState
	Transitions map[byte]*DfaState
	IsAcceptable bool
	Name string
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
	}
}


func BuildDfaFromNfa(n *nfa.Nfa) (*Dfa, error){
	if n.RefCount != 0 || len(n.Groups) != 0 {
		return nil, fmt.Errorf("Nfa has Named Groups or references. Please inter expression before compile\n")
	}
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
	startClosure := epsilonClosure(startNfaStates) // добавка всех e-замыканий

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
			if existing, ok := markedStates[key]; ok { // если такое состояние уже мы создали раньше
				targetState = existing
			} else { // если такого состояния еще не было
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
	return dfa, nil
}


func (this * Dfa) addState(nfast map[int]*nfa.NfaState) *DfaState{
	this.StateCount++
	state := newDfaState(this.StateCount, nfast)
	this.States = append(this.States, state)
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




//---------------------------
type Context struct {
	State *nfa.NfaState
	Groups map[string]string
	GroupStart map[string]int
	GroupClosed map[string]bool
	Pos int
}

func checkString(n *nfa.Nfa, input string) (bool, map[string]string) {
	contexts := []Context{{
		State:      n.StartState,
		Groups:     make(map[string]string),
		GroupStart: make(map[string]int),
		GroupClosed: make(map[string]bool),
		Pos:        0,
	}}

	for len(contexts) > 0 {
		newContexts := []Context{}

		for _, ctx := range contexts {
			if ctx.Pos == len(input) {
				if ctx.State.IsAcceptable {
					res := make(map[string]string)
					for grpName, text := range ctx.Groups {
						res[grpName] = text
					}
					for grpName, start := range ctx.GroupStart {
						if _, exists := res[grpName]; !exists {
							res[grpName] = input[start:ctx.Pos]
						}
					}
					return true, res

				}
				for _, eps := range ctx.State.Epsilons {
					newContexts = append(newContexts, Context{
						State:       eps,
						Groups:      ctx.Groups,
						GroupStart:  ctx.GroupStart,
						GroupClosed: ctx.GroupClosed,
						Pos:         ctx.Pos,

					})

				}

				continue
			}

			if ctx.State.IsRef {
				handleRef(ctx, input, &newContexts)
				continue
			}

			ch := input[ctx.Pos]
			if targets, ok := ctx.State.Transitions[ch]; ok {
				for _, target := range targets {
					newCtx := Context{
						State:       target,
						Groups:      copyGroups(ctx.Groups),
						GroupStart:  copyGroupStarts(ctx.GroupStart),
						GroupClosed: copyGroupClosed(ctx.GroupClosed),
						Pos:         ctx.Pos + 1,

					}

					for groupName, isStart := range target.GroupInfo {
						if isStart {
							newCtx.GroupStart[groupName] = ctx.Pos
						}
					}
					newContexts = append(newContexts, newCtx)
				}
			}

			for _, eps := range ctx.State.Epsilons {

				newCtx := Context{
					State:       eps,
					Groups:      copyGroups(ctx.Groups),
					GroupStart:  copyGroupStarts(ctx.GroupStart),
					GroupClosed: copyGroupClosed(ctx.GroupClosed),
					Pos:         ctx.Pos,
				}

				for groupName, isStart := range ctx.State.GroupInfo {
					if isStart && !ctx.GroupClosed[groupName] {
						newCtx.GroupStart[groupName] = ctx.Pos
					}
				}
				for groupName, isStart := range eps.GroupInfo {
					if isStart && !ctx.GroupClosed[groupName] {
						newCtx.GroupStart[groupName] = ctx.Pos
					}
				}

				for groupName := range ctx.GroupStart {
					if ctx.GroupClosed[groupName] {
						continue
					}

					_, currentInGroup := ctx.State.GroupInfo[groupName]
					_, nextInGroup := eps.GroupInfo[groupName]

					if currentInGroup && !nextInGroup {
						if start, ok := ctx.GroupStart[groupName]; ok {
							captured := input[start:ctx.Pos]
							//fmt.Printf("DEBUG: Группа %s захватила '%s' (позиции %d-%d)\n", groupName, captured, start, ctx.Pos)
							newCtx.Groups[groupName] = captured
							delete(newCtx.GroupStart, groupName)
							newCtx.GroupClosed[groupName] = true
						}
					}
				}

				newContexts = append(newContexts, newCtx)
			}
		}

		sortContextsByCapturedLength(newContexts)

		contexts = newContexts
		//printContexts(contexts)
	}
	return false, nil
}

// Сортировка: сначала контексты с большим количеством захваченных символов
func sortContextsByCapturedLength(contexts []Context) {
	sort.Slice(contexts, func(i, j int) bool {
		lenI := 0
		lenJ := 0
		for _, text := range contexts[i].Groups {
			lenI += len(text)
		}
		for _, text := range contexts[j].Groups {
			lenJ += len(text)
		}
		return lenI > lenJ
	})
}


/*
func printContexts(contexts []Context) {
	for _, ctx := range contexts {
		fmt.Printf("state: %d\n", ctx.State.ID)
	}
	fmt.Println("\n")
}
*/
func copyGroups(original map[string]string) map[string]string {
	result := make(map[string]string)
	for k, v := range original {
		result[k] = v
	}
	return result
}

func copyGroupStarts(original map[string]int) map[string]int {
	result := make(map[string]int)
	for k, v := range original {
		result[k] = v
	}
	return result
}

func copyGroupClosed(original map[string]bool) map[string]bool {
	result := make(map[string]bool)
	for k, v := range original {
		result[k] = v
	}
	return result
}

func handleRef (ctx Context, input string, newContexts *[]Context) {
	expectedText := ctx.Groups[ctx.State.RefGroup]
	//fmt.Println("expected: "+expectedText)
	if expectedText == ""{
		return // если нет текста, то группа не захвачена
	}
	if ctx.Pos+len(expectedText) <= len(input) && input[ctx.Pos:ctx.Pos+len(expectedText)] == expectedText {
		for _, epsilon := range ctx.State.Epsilons {
			*newContexts = append(*newContexts, Context{
				State:      epsilon,
				Groups:     ctx.Groups,
				GroupStart: ctx.GroupStart,
				Pos:        ctx.Pos + len(expectedText),
			})
		}
	}
}

func Compile(regex, new_regex string, n *nfa.Nfa) (*Dfa, error) {
	is_true, groups := checkString(n, new_regex)
	if !is_true{
		return nil, fmt.Errorf("regex '%s' is not valid", new_regex)
	}
	result := regex
	for groupName, text := range groups {
		//fmt.Println("группа на замену: "+groupName+"\n")
		//fmt.Println("замена на: "+text+"\n")

		result = replaceFirstGroupContent(result, groupName, text)

		result = strings.ReplaceAll(result, "<"+groupName+">", text)
	}
	//fmt.Println("->  "+result)
	newTree, ok := reg.BuildSyntaxTree(result)
	if ok != nil {
		return nil, ok
	}
	newNfa := nfa.BuildNfaFromTree(newTree)
	n = newNfa
	dfa, ok := BuildDfaFromNfa(newNfa)
	if ok != nil {
		return nil, ok
	}
	minDfa := Minimize(dfa)
	if minDfa == nil {
		return nil, fmt.Errorf("Minimize dfa fail\n")
	}
	return minDfa, nil
}


func replaceFirstGroupContent(regex string, groupName string, replacement string) string {
	search := "(<" + groupName + ">"
	startIdx := strings.Index(regex, search)
	if startIdx == -1 {
		return regex
	}
	balance := 1
	i := startIdx + len(search)
	for i < len(regex) && balance > 0 {
		if regex[i] == '(' {
			balance++
		} else if regex[i] == ')' {
			balance--
		}
		i++
	}
	if balance != 0 {
		return regex
	}
	return regex[:startIdx] + "(" + replacement + ")" + regex[i:]
}