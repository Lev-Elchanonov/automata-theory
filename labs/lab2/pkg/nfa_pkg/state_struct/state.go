package state

type State struct {
	ID         int
	Transition map[rune][]*State
	Epsilon    []*State
	IsAccept   bool
	// тут еще мб че то про группы захвата
}

func NewState(id int) *State {
	return &State{
		ID: id,
		Transition: make(map[rune][]*State),
		Epsilon:    make([]*State, 0),
		IsAccept:   false,
	}
}

func (s* State) AddTransition(name rune, to_state* State){
	s.Transition[name] = append(s.Transition[name], to_state)
}

func (s* State) AddEpsilon(to_state* State){
	s.Epsilon = append(s.Epsilon, to_state)
}




