package dfa

type MatchResult struct {
	Start int
	End int
	Text string
}

type MatchIterator struct {
	dfa *Dfa
	text string
	pos int
	current *MatchResult
}


func (iter *MatchIterator) Next() bool {
	result := iter.dfa.SearchFrom(iter.text, iter.pos)
	if result == nil {
		return false
	}
	iter.current = result
	iter.pos = result.End
	return true
}

func (iter *MatchIterator) Value() *MatchResult{
	return iter.current
}

func (iter *MatchIterator) Index(ind int) *MatchResult {
	if ind < 0{
		return nil
	}
	pos := 0
	count := 0
	for {
		result := iter.dfa.SearchFrom(iter.text, pos)
		if result == nil {
			return nil
		}
		if count == ind{
			return result
		}
		count++
		pos = result.End
	}
}



