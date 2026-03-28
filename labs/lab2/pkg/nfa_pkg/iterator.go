package nfa

type MatchIterator struct {
	nfa     *Nfa
	text    string
	pos     int
	allMatches []*MatchResult
	index      int
	current    *MatchResult
}



func (it *MatchIterator) Next() bool {
	if it.index >= len(it.allMatches) {
		return false
	}
	it.current = it.allMatches[it.index]
	it.index++
	return true
}


func (it *MatchIterator) Value() *MatchResult {
	return it.current
}


func (it *MatchIterator) Index(idx int) *MatchResult {
	if idx < 0 || idx >= len(it.allMatches) {
		return nil
	}
	return it.allMatches[idx]
}

