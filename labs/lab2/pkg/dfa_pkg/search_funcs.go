package dfa

// -------------------------------------------
//SEARCH

type SearchContext struct {
	State *DfaState
	Pos int
	StartPos int
}


func (it *MatchIterator) Current() *MatchResult {
	return it.current
}


func (this *Dfa) Search(text string) *MatchResult{
	return this.SearchFrom(text, 0)
}

func (this *Dfa) SearchFrom(text string, start int) *MatchResult{
	for i := start; i < len(text); i++ {
		result := this.matchAt(text, i)
		if result != nil {
			return result
		}
	}
	return nil
}



func (this *Dfa) matchAt(text string, start int) *MatchResult {
	currentState := this.StartState
	lastAcceptPos := -1
	pos := start
	for pos < len(text) {
		ch := text[pos]
		nextState := currentState.Transitions[ch]
		if nextState == nil || nextState == this.ErrorState {break}

		currentState = nextState
		pos++

		if currentState.IsAcceptable {lastAcceptPos = pos}
	}

	if lastAcceptPos != -1 {
		return &MatchResult{
			Start:  start,
			End:    lastAcceptPos,
			Text:   text[start:lastAcceptPos],
		}
	}

	return nil
}

func (this *Dfa) Accepts(text string) bool{
	currentState := this.StartState
	for i := 0; i < len(text); i++ {
		nextState := currentState.Transitions[text[i]]
		if nextState == nil || nextState == this.ErrorState {
			return false
		}
		currentState = nextState
	}
	return currentState.IsAcceptable
}

func (this *Dfa) SearchAll(text string) *MatchIterator {
	return &MatchIterator{
		dfa:  this,
		text: text,
		pos:  0,
	}
}
