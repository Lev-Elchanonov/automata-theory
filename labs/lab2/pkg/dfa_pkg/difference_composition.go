package dfa

import (
	nfa "lab2/pkg/nfa_pkg"
	"sort"
	"strconv"
)

type ProductState struct {
	State1 *DfaState
	State2 *DfaState
}

func Difference(firstDfa, secondDfa *Dfa) *Dfa {
	return mainCycle(firstDfa, secondDfa)
}




func mainCycle (first, second *Dfa) *Dfa {
	newAlphabet := mergeAlphabets(first.Alphabet, second.Alphabet)

	result := &Dfa{
		Alphabet: newAlphabet,
		StateCount: 0,
		States: make([]*DfaState, 0),
		AcceptStates: make([]*DfaState, 0),
		ErrorState: nil,
	}

	stateMap := make(map[ProductState]*DfaState)

	errorPair := ProductState{first.ErrorState, second.ErrorState}
	errorState := result.addProductState(&errorPair)
	stateMap[errorPair] = errorState
	result.ErrorState = errorState

	queue := []ProductState{{first.StartState, second.StartState}}

	startState := result.addProductState(&queue[0])
	stateMap[queue[0]] = startState
	result.StartState = startState


	if queue[0].State1.IsAcceptable && !queue[0].State2.IsAcceptable {
		startState.IsAcceptable = true
		result.AcceptStates = append(result.AcceptStates, startState)
	}


	for len(queue) > 0{
		current := queue[0]
		queue = queue[1:]
		currentState := stateMap[current]

		for _, symbol := range newAlphabet{
			next1 := current.State1.Transitions[symbol]
			next2 := current.State2.Transitions[symbol]
			if next1 == nil{
				next1 = first.ErrorState
			}
			if next2 == nil{
				next2 = second.ErrorState
			}


			nextPair := ProductState{next1, next2}
			var nextState *DfaState
			if existing, ok := stateMap[nextPair]; ok{
				nextState = existing
			} else {
				if next1 == first.ErrorState && next2 == second.ErrorState {
					nextState = errorState
				} else {
					nextState = result.addProductState(&nextPair)
					stateMap[nextPair] = nextState
					queue = append(queue, nextPair)
					if nextPair.State1.IsAcceptable && !nextPair.State2.IsAcceptable {
						nextState.IsAcceptable = true
						result.AcceptStates = append(result.AcceptStates, nextState)
					}

				}

			}
			currentState.Transitions[symbol] = nextState
		}
	}

	for _, symbol := range newAlphabet {
		errorState.Transitions[symbol] = errorState
	}

	for _, state := range result.States {
		if state == errorState {
			continue
		}
		for _, symbol := range newAlphabet {
			if _, ok := state.Transitions[symbol]; !ok {
				state.Transitions[symbol] = errorState
			}
		}
	}

	return result
}

func (d *Dfa) addProductState(pair *ProductState) *DfaState{
	newState := &DfaState{
		ID:           d.StateCount,
		NfaStates:    make(map[int]*nfa.NfaState),
		Transitions:  make(map[byte]*DfaState),
		IsAcceptable: false,
		Name: strconv.Itoa(pair.State1.ID) + "|" + strconv.Itoa(pair.State2.ID),
	}

	for id, state := range pair.State1.NfaStates {
		newState.NfaStates[id] = state
	}
	for id, state := range pair.State2.NfaStates {
		newState.NfaStates[id] = state
	}
	d.StateCount++
	d.States = append(d.States, newState)
	return newState
}



func mergeAlphabets(alph1, alph2 []byte) []byte{
	set := make(map[byte]bool)
	for _, s := range alph1{
		set[s] = true
	}
	for _, s := range alph2{
		set[s] = true
	}
	result := make([]byte, 0, len(set))
	for s := range set{
		result = append(result, s)
	}
	sort.Slice(result, func(i, j int) bool {
		return result[i] < result[j]
	})
	return result
}
