package strOpers

import (
	dfa "lab2/pkg/dfa_pkg"
	nfa "lab2/pkg/nfa_pkg"
)



func Search(regex, incomingText string) (*dfa.MatchResult, *nfa.MatchResult){
	automataDfa, automataNfa, err := dfa.BuildDfa(regex)
	if err != nil {return nil, nil}
	if automataDfa != nil && automataNfa == nil{
		return automataDfa.Search(incomingText), nil
	} else if automataDfa == nil && automataNfa != nil {
		return nil, automataNfa.Search(incomingText)
	}
	return nil, nil
}

func SearchFrom(regex, incomingText string, pos int)  (*dfa.MatchResult, *nfa.MatchResult){
	automataDfa, automataNfa, err := dfa.BuildDfa(regex)
	if err != nil {return nil, nil}
	if automataDfa != nil && automataNfa == nil{
		return automataDfa.SearchFrom(incomingText, pos), nil
	} else if automataDfa == nil && automataNfa != nil {
		return nil, automataNfa.SearchFrom(incomingText, pos)
	}
	return nil, nil
}

func Accepts(regex, incomingText string) bool{
	automataDfa, automataNfa, err := dfa.BuildDfa(regex)
	if err != nil{
		return false
	}
	if automataDfa != nil && automataNfa == nil{
		return automataDfa.Accepts(incomingText)
	} else if automataDfa == nil && automataNfa != nil {
		return automataNfa.Accepts(incomingText)
	}
	return false
}

func SearchAll(regex, incomingText string) (*dfa.MatchIterator, *nfa.MatchIterator) {
	automataDfa, automataNfa, err := dfa.BuildDfa(regex)
	if err != nil {return nil, nil}
	if automataDfa != nil && automataNfa == nil{
		return automataDfa.SearchAll(incomingText), nil
	} else if automataDfa == nil && automataNfa != nil {
		return nil, automataNfa.SearchAll(incomingText)
	}
	return nil, nil
}