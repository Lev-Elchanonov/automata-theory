package nfa

import (
	st "lab2/nfa_pkg/state_struct"
)

type NFA struct {
	Start *st.State
	Accept *st.State
	States []*st.State
}

func NewNFA() *NFA {
	return &NFA{
		States: make([]*st.State, 0),
	}
}

func (nfa* NFA) addState(st* st.State){
	nfa.States = append(nfa.States, st)
}