package nfa

type MatchIterator struct {
	nfa     *Nfa
	text    string
	pos     int
	current *MatchResult
}



func (it *MatchIterator) Next() bool {
	result := it.nfa.SearchFrom(it.text, it.pos)
	if result == nil {
		return false
	}
	it.current = result
	it.pos = result.End
	return true
}


func (it *MatchIterator) Value() *MatchResult {
	return it.current
}


func (it *MatchIterator) Index(idx int) *MatchResult {
	if idx < 0 {
		return nil
	}
	pos := 0
	count := 0
	for {
		result := it.nfa.SearchFrom(it.text, pos)
		if result == nil {
			return nil
		}
		if count == idx {
			return result
		}
		count++
		pos = result.End
	}
}