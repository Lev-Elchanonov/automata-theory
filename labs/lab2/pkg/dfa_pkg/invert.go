package dfa

import nfa "lab2/pkg/nfa_pkg"



func (this *Dfa) Invert() *Dfa{
	inverted := &Dfa{
		Alphabet: this.Alphabet,
		States: make([]*DfaState, 0),
		StateCount: 0,
		AcceptStates: make([]*DfaState, 0),
		ErrorState: nil,
	}
	stateMap := make(map[*DfaState]*DfaState)

	for _, oldState := range this.States {
		newState := &DfaState{
			ID: inverted.StateCount,
			Transitions: make(map[byte]*DfaState),
			IsAcceptable: false,
		}
		inverted.StateCount++
		inverted.States = append(inverted.States, newState)
		stateMap[oldState] = newState
	}

	for oldState, newState := range stateMap {
		for symbol, target := range oldState.Transitions {
			newState.Transitions[symbol] = stateMap[target]
		}
	}

	for _, oldState := range this.States{
		newState := stateMap[oldState]

		if oldState == this.ErrorState{
			newState.IsAcceptable = false
			inverted.ErrorState = newState
		} else {
			newState.IsAcceptable = !oldState.IsAcceptable
			if newState.IsAcceptable {
				inverted.AcceptStates = append(inverted.AcceptStates, newState)
			}
		}
	}
	inverted.StartState = stateMap[this.StartState]
	return inverted
}

// просто переворачивает регулярку: abc -> cba
func (d *Dfa) Reverse() *Dfa{
	reversedNfa := d.buildReversedNfa()
	dfaReverse, err := BuildDfaFromNfa(reversedNfa)
	if err != nil {
		return nil
	}
	return Minimize(dfaReverse)
}

func (d *Dfa) buildReversedNfa() *nfa.Nfa{
	reversedNfa := nfa.NewNfa()

	stateMap := make(map[*DfaState]*nfa.NfaState)

	for _, oldState := range d.States {
		newState := reversedNfa.AddState()
		stateMap[oldState] = newState
	}

	for _, oldState := range d.States {
		newFrom := stateMap[oldState]

		for symbol, target := range oldState.Transitions {
			newTo := stateMap[target]

			newTo.Transitions[symbol] = append(newTo.Transitions[symbol], newFrom)
		}
	}

	newStart := reversedNfa.AddState()

	for _, oldAccept := range d.AcceptStates {
		OneOfStarts := stateMap[oldAccept]
		// ε-переход из нового начального в каждое из бывших принимающих
		newStart.Epsilons = append(newStart.Epsilons, OneOfStarts)
	}

	// Новые принимающие состояния = старое начальное состояние
	newAcceptState := stateMap[d.StartState]
	newAcceptState.IsAcceptable = true

	reversedNfa.StartState = newStart

	return reversedNfa
}