package dfa

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
