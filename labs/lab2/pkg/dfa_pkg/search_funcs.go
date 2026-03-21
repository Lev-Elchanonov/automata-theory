package dfa

// -------------------------------------------
//SEARCH

type SearchContext struct {
	State *DfaState
	Groups map[string]string
	GroupStart map[string]int
	GroupClosed map[string]bool
	Pos int
	StartPos int
}


func (it *MatchIterator) Current() *MatchResult {
	return it.current
}


func (d *Dfa) Search(text string) *MatchResult{
	return d.SearchFrom(text, 0)
}

func (d *Dfa) SearchFrom(text string, start int) *MatchResult{
	for i := start; i < len(text); i++ {
		result := d.matchAt(text, i)
		if result != nil {
			return result
		}
	}
	return nil
}



func (d *Dfa) matchAt(text string, start int) *MatchResult {
	currentState := d.StartState
	groupStarts := make(map[string]int)
	lastAcceptPos := -1
	lastAcceptGroups := make(map[string]string)

	pos := start

	for pos < len(text) {
		ch := text[pos]

		nextState := currentState.Transitions[ch]
		if nextState == nil || nextState == d.ErrorState {
			break
		}

		for groupName, isStart := range nextState.GroupInfo {
			if isStart {
				groupStarts[groupName] = pos
			}
		}

		currentState = nextState
		pos++

		if currentState.IsAcceptable {
			lastAcceptPos = pos
			lastAcceptGroups = make(map[string]string)
			for groupName, startPos := range groupStarts {
				lastAcceptGroups[groupName] = text[startPos:pos]
			}
		}
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

func (d *Dfa) SearchAll(text string) *MatchIterator {
	return &MatchIterator{
		dfa:  d,
		text: text,
		pos:  0,
	}
}
