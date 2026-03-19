package dfa

import (
	"context"
	nfa "lab2/pkg/nfa_pkg"
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


func BuildDfaFromNfa(n *nfa.Nfa) (*Dfa, error){

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




//---------------------------
type Context struct {
	State *nfa.NfaState
	Groups map[string]string
	GroupStart map[string]int
	Pos int
}


func checkString(n *nfa.Nfa, input string) (bool, map[string]string) {
	contexts := []Context{{
		State: n.StartState,
		Groups: make(map[string]string),
		GroupStart: make(map[string]int),
		Pos: 0,
	}}

	for len(contexts) > 0 {
		newContexts := []Context{}

		for _,ctx := range contexts {
			if ctx.Pos == len(input){ // конец строки
				if ctx.State.IsAcceptable{
					res := make(map[string]string)
					for grpName, start := range ctx.GroupStart{
						res[grpName] = input[start:ctx.Pos]
					}
					return true, res
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
						State:      target,
						Groups:     copyGroups(ctx.Groups),
						GroupStart: copyGroupStarts(ctx.GroupStart),
						Pos:        ctx.Pos + 1,
					}
					// Отслеживаем начала групп
					for groupName, isStart := range target.GroupInfo {
						if isStart {
							newCtx.GroupStart[groupName] = ctx.Pos
						}
					}
					newContexts = append(newContexts, newCtx)
				}
			}
			for _, eps := range ctx.State.Epsilons {
				if !eps.IsRef { // не обрабатываем ссылки как ε
					newContexts = append(newContexts, Context{
						State:      eps,
						Groups:     ctx.Groups,
						GroupStart: ctx.GroupStart,
						Pos:        ctx.Pos,
					})
				}
			}
		}
	contexts = newContexts
	}
	return false, nil
}

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

func handleRef (ctx Context, input string, newContexts *[]Context) {
	expectedText := ctx.Groups[ctx.State.RefGroup]

}