package nfa

import (
	reg "lab2/pkg/regex_pkg"
)
type NfaState struct {
	ID int
	Transitions map[byte][]*NfaState
	Epsilons []*NfaState
	IsAcceptable bool
	GroupInfo map[string]bool
}

type GroupInfo struct {
	Name string
	StartPos int // позиция в синтаксическом дереве
	EndPos int
	IsRef bool
	RefName string
}
type GroupAutomata struct {
	Start *NfaState
	End *NfaState
}
type Nfa struct {
	StartState *NfaState
	AcceptState *NfaState
	States []*NfaState
	StateCount int
	Groups map[string]*GroupInfo //Инфо о группах захвата
	GroupAutos map[string]*GroupAutomata
}

func newNfaState(id int) *NfaState {
	return &NfaState{
		ID: id,
		Transitions: make(map[byte][]*NfaState),
		Epsilons: make([]*NfaState, 0),
		GroupInfo: make(map[string]bool),
		IsAcceptable: false,
	}
}

func newNfa() *Nfa{
	return &Nfa{
		States: make([]*NfaState, 0),
		StateCount: 0,
		Groups: make(map[string]*GroupInfo),
		GroupAutos: make(map[string]*GroupAutomata),
	}
}


func (n* Nfa) addState() *NfaState {
	n.StateCount++
	state := newNfaState(n.StateCount)
	n.States = append(n.States, state)
	return state
}


func BuildNfaFromTree (tree *reg.SyntaxTree) *Nfa {
	nfa := newNfa()

	collectGroups(tree.Root, &nfa.Groups) // сбор инфы о группах захвата

	start, accept := buildNfaFromNode(tree.Root, nfa)
	nfa.StartState = start
	nfa.AcceptState = accept
	return nfa
}


func collectGroups(node *reg.Node, groups *map[string]*GroupInfo) {
	if node == nil{ return }
	switch node.Type{
		case reg.GroupNode:
			(*groups)[node.Value] = &GroupInfo{
				Name: node.Value,
				StartPos: node.Position,
			}
		case reg.RefNode:
			if info, exists := (*groups)[node.Value]; exists{
				info.IsRef = true
				info.RefName = node.Value
			}
	}
	collectGroups(node.Left, groups)
	collectGroups(node.Right, groups)
}


func buildNfaFromNode(node *reg.Node, nfa *Nfa) (*NfaState, *NfaState){
	if node == nil { return buildEpsilonNfa(nfa) }

	switch node.Type {
	case reg.LeafNode:
		return buildLeafNfa(node, nfa)
	case reg.ConcatNode:
		return buildConcatNfa(node, nfa)
	case reg.UnionNode:
		return buildUnionNfa(node, nfa)
	case reg.KliniNode:
		return buildKliniNfa(node, nfa)
	case reg.QuestionNode:
		return buildQuestionNfa(node, nfa)
	case reg.RepeatNode:
		return buildRepeatNfa(node, nfa)
	case reg.GroupNode:
		return buildGroupNfa(node, nfa)
	case reg.RefNode: return buildRefNfa(node, nfa)
	default: // по умолчанию строим эпсилон
		return buildEpsilonNfa(nfa)
	}
}

func buildEpsilonNfa (nfa *Nfa) (*NfaState, *NfaState){
	start := nfa.addState()
	accept := nfa.addState()
	start.Epsilons = append(start.Epsilons, accept)
	accept.IsAcceptable = true
	return start, accept
}

func buildLeafNfa(node *reg.Node, nfa *Nfa) (*NfaState, *NfaState){
	start := nfa.addState()
	accept := nfa.addState()
	if node.Value == "epsilon"{
		start.Epsilons = append(start.Epsilons, accept)
	} else {
		ch := node.Value[0]
		start.Transitions[ch] = append(start.Transitions[ch], accept)
	}
	accept.IsAcceptable = true
	return start, accept
}

func buildConcatNfa (node *reg.Node, nfa *Nfa) (*NfaState, *NfaState){
	leftStart, leftAccept := buildNfaFromNode(node.Left, nfa)
	rightStart, rightAccept := buildNfaFromNode(node.Right, nfa)

	leftAccept.Epsilons = append(leftAccept.Epsilons, rightStart)
	leftAccept.IsAcceptable = false
	return leftStart, rightAccept
}

func buildUnionNfa(node* reg.Node, nfa *Nfa) (*NfaState, *NfaState){
	newStart := nfa.addState()
	newAccept := nfa.addState()

	leftStart, leftAccept := buildNfaFromNode(node.Left, nfa)
	rightStart, rightAccept := buildNfaFromNode(node.Right, nfa)

	newStart.Epsilons = append(newStart.Epsilons, leftStart, rightStart)

	leftAccept.IsAcceptable = false
	rightAccept.IsAcceptable = false


	newAccept.IsAcceptable = true
	leftAccept.Epsilons = append(leftAccept.Epsilons, newAccept)
	rightAccept.Epsilons = append(rightAccept.Epsilons, newAccept)
	return newStart, newAccept
}

func buildKliniNfa(node *reg.Node, nfa *Nfa) (*NfaState, *NfaState){
	newStart := nfa.addState()
	newAccept := nfa.addState()
	newAccept.IsAcceptable = true

	nodeStart, nodeAccept := buildNfaFromNode(node.Left, nfa)
	nodeAccept.IsAcceptable = false

	newStart.Epsilons = append(newStart.Epsilons, newAccept, nodeStart)

	nodeAccept.Epsilons = append(nodeAccept.Epsilons, nodeStart, newAccept)
	return newStart, newAccept
}

func buildQuestionNfa (node *reg.Node, nfa *Nfa) (*NfaState, *NfaState){ // eps|r
	newStart := nfa.addState()
	newAccept := nfa.addState()
	newAccept.IsAcceptable = true

	nodeStart, nodeAccept := buildNfaFromNode(node.Left, nfa)
	nodeAccept.IsAcceptable = false

	newStart.Epsilons = append(newStart.Epsilons, newAccept, nodeStart)
	nodeAccept.Epsilons = append(nodeAccept.Epsilons, newAccept)
	return newStart, newAccept
}

func buildRepeatNfa(node *reg.Node, nfa *Nfa) (*NfaState, *NfaState) {
	if node.Repeat == 0 {
		return buildEpsilonNfa(nfa)
	}
	if node.Repeat == 1 {
		return buildNfaFromNode(node.Left, nfa)
	}

	templateNfa := newNfa()
	templateStart, templateAccept := buildNfaFromNode(node.Left, templateNfa)

	templateStates := make(map[*NfaState]bool)
	collectStates(templateStart, templateStates)

	firstStart, firstAccept := importTemplate(templateStart, templateAccept, nfa, templateStates)
	firstAccept.IsAcceptable = false

	prevAccept := firstAccept

	for i := 1; i < node.Repeat; i++ {
		copyStart, copyAccept := importTemplate(templateStart, templateAccept, nfa, templateStates)

		prevAccept.Epsilons = append(prevAccept.Epsilons, copyStart)
		prevAccept = copyAccept

		if i < node.Repeat-1 {
			prevAccept.IsAcceptable = false
		}
	}

	prevAccept.IsAcceptable = true
	return firstStart, prevAccept
}


func collectStates(start *NfaState, states map[*NfaState]bool) {
	queue := []*NfaState{start}
	visited := make(map[*NfaState]bool)

	for len(queue) > 0 {
		current := queue[0]
		queue = queue[1:]

		if visited[current] {
			continue
		}
		visited[current] = true
		states[current] = true

		for _, targets := range current.Transitions {
			for _, target := range targets {
				if !visited[target] {
					queue = append(queue, target)
				}
			}
		}
		for _, target := range current.Epsilons {
			if !visited[target] {
				queue = append(queue, target)
			}
		}
	}
}



func importTemplate(templateStart, templateAccept *NfaState, targetNfa *Nfa,
	templateStates map[*NfaState]bool) (*NfaState, *NfaState) {

	stateMap := make(map[*NfaState]*NfaState)

	for oldState := range templateStates {
		newState := targetNfa.addState()
		stateMap[oldState] = newState
	}

	for oldState, newState := range stateMap {
		for ch, targets := range oldState.Transitions {
			for _, target := range targets {
				if newTarget, ok := stateMap[target]; ok {
					newState.Transitions[ch] = append(newState.Transitions[ch], newTarget)
				}
			}
		}
		for _, target := range oldState.Epsilons {
			if newTarget, ok := stateMap[target]; ok {
				newState.Epsilons = append(newState.Epsilons, newTarget)
			}
		}
		newState.IsAcceptable = oldState.IsAcceptable
	}

	return stateMap[templateStart], stateMap[templateAccept]
}


func buildGroupNfa (node *reg.Node, nfa *Nfa) (*NfaState, *NfaState){
	nodeStart, nodeAccept := buildNfaFromNode(node.Left, nfa)

	nodeStart.GroupInfo[node.Value] = true // помечаем что это состояние начало группы
	markGroupStates(nodeStart, nodeStart, node.Value)
	nfa.GroupAutos[node.Value] = &GroupAutomata{
		Start: nodeStart,
		End:   nodeAccept,
	}
	return nodeStart, nodeAccept
}


func markGroupStates(state, startState *NfaState, groupName string) {
	visited := make(map[*NfaState]bool)
	markGroupStatesHelper(state, startState, groupName, visited)
}

func markGroupStatesHelper(state, startState *NfaState, groupName string, visited map[*NfaState]bool) {
	if state == nil || visited[state] {
		return
	}
	visited[state] = true

	if state != startState {
		state.GroupInfo[groupName] = false
	}

	for _, target := range state.Epsilons {
		markGroupStatesHelper(target, startState, groupName, visited)
	}
	for _, targets := range state.Transitions {
		for _, target := range targets {
			markGroupStatesHelper(target, startState, groupName, visited)
		}
	}
}



func buildRefNfa (node *reg.Node, nfa *Nfa) (*NfaState, *NfaState){
	groupAuto := nfa.GroupAutos[node.Value]
	cloneStart, cloneAccept := cloneNfa(groupAuto.Start, groupAuto.End, nfa, node.Value)

	markAsRef(cloneStart, node.Value)
	return cloneStart, cloneAccept
}

func markAsRef(state *NfaState, groupName string) {
	visited := make(map[*NfaState]bool)
	markAsRefHelper(state, groupName, visited)
}

func markAsRefHelper(state *NfaState, groupName string, visited map[*NfaState]bool) {
	if state == nil || visited[state] {
		return
	}
	visited[state] = true

	state.GroupInfo["ref:"+groupName] = true

	for _, target := range state.Epsilons {
		markAsRefHelper(target, groupName, visited)
	}
	for _, targets := range state.Transitions {
		for _, target := range targets {
			markAsRefHelper(target, groupName, visited)
		}
	}
}


func cloneNfa(start, accept *NfaState, targetNfa *Nfa, groupName string) (*NfaState, *NfaState) {
	allStates := make(map[*NfaState]bool)
	collectGroupStates(start, allStates, groupName)

	stateMap := make(map[*NfaState]*NfaState)


	for oldState := range allStates {
		newState := targetNfa.addState()
		stateMap[oldState] = newState
	}

	for oldState, newState := range stateMap {

		for ch, targets := range oldState.Transitions {
			for _, target := range targets {
				if newTarget, ok := stateMap[target]; ok {
					newState.Transitions[ch] = append(newState.Transitions[ch], newTarget)
				}
			}
		}


		for _, target := range oldState.Epsilons {
			if newTarget, ok := stateMap[target]; ok {
				newState.Epsilons = append(newState.Epsilons, newTarget)
			}
		}

		newState.IsAcceptable = oldState.IsAcceptable
	}
	markAsRef(stateMap[start], groupName)

	return stateMap[start], stateMap[accept]
}


func collectGroupStates(state *NfaState, visited map[*NfaState]bool, groupName string) {
	if state == nil || visited[state] {
		return
	}

	if _, belongs := state.GroupInfo[groupName]; !belongs {
		return
	}

	visited[state] = true

	for _, target := range state.Epsilons {
		collectGroupStates(target, visited, groupName)
	}
	for _, targets := range state.Transitions {
		for _, target := range targets {
			collectGroupStates(target, visited, groupName)
		}
	}
}


