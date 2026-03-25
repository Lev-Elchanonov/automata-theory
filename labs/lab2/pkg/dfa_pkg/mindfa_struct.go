package dfa

import (
	"fmt"
	nfa "lab2/pkg/nfa_pkg"
	"lab2/pkg/regex_pkg"
	"sort"
	"strings"
)

type Group struct {
	Id int
	States map[int]*DfaState
}
type Partition struct {
	Groups map[int]*Group
	GroupsCount int
}
func (p *Partition) addGroup(gr *Group) {
	p.Groups[gr.Id] = gr
	p.GroupsCount++
}


func Minimize(d *Dfa) *Dfa{
	pset := &Partition{
		Groups: make(map[int]*Group),
		GroupsCount: 0,
	}
	errorStates := make(map[int]*DfaState)
	errorStates[d.ErrorState.ID] = d.ErrorState
	errorGroup := createGroup(0, errorStates)
	pset.addGroup(errorGroup)

	acceptStates := createStatesMap(d.AcceptStates)
	acceptGroup := createGroup(1, acceptStates)
	notAcceptStates := make(map[int]*DfaState)
	for _, state := range d.States {
		if !state.IsAcceptable && state != d.ErrorState {
			notAcceptStates[state.ID] = state
		}
	}
	notAcceptGroup := createGroup(2, notAcceptStates)


	pset.addGroup(acceptGroup)
	pset.addGroup(notAcceptGroup)


	cont := true
	subgroupsLen := 1
	for cont {
		cont = false
		newpset := &Partition{
			Groups: make(map[int]*Group),
			GroupsCount: 0,
		}
		groupIDs := make([]int, 0, len(pset.Groups))
		for id := range pset.Groups {
			groupIDs = append(groupIDs, id)
		}
		sort.Ints(groupIDs)

		for _, groupID := range groupIDs { // для каждой группы из П
			group := pset.Groups[groupID]
			containsError := false


			for _, state := range group.States {
				if state == d.ErrorState {
					containsError = true
					break
				}
			}
			if containsError {
				group.Id = newpset.GroupsCount
				newpset.addGroup(group)
				continue
			}


			if len(group.States) == 1 { // тривиальная группа
				group.Id = newpset.GroupsCount
				newpset.addGroup(group)
				continue
			}

			subgroups := splitGroup(group, d, pset)
			cont = true


			sort.Slice(subgroups, func(i, j int) bool {
				// получаем минимальный ID в каждой подгруппе
				minI := getMinStateID(subgroups[i])
				minJ := getMinStateID(subgroups[j])
				return minI < minJ
			})

			for _, subgroup := range subgroups {
				subgroup.Id = newpset.GroupsCount
				newpset.addGroup(subgroup)
			}
			if len(subgroups) == 1 && subgroupsLen == 1{
				cont = false
			}
			subgroupsLen = len(subgroups)

		}
		pset = newpset

	}


	return buildMinimizedDFA(d, pset)
}



func getMinStateID(group *Group) int {
	minID := int(^uint(0) >> 1)
	for id := range group.States {
		if id < minID {
			minID = id
		}
	}
	return minID
}


func createStatesMap (states []*DfaState) map[int]*DfaState {
	res := make(map[int]*DfaState, len(states))
	for _, state := range states {
		res[state.ID] = state
	}
	return res
}
func createGroup (id int, states map[int]*DfaState) *Group {
	return &Group{
		Id: id,
		States: states,
	}
}

func findGroup(curState *DfaState, pset *Partition) *Group{
	for _, group := range pset.Groups {
		if _,exists := group.States[curState.ID]; exists{
			return group
		}
	}
	return nil
}

// разбивка группы
func splitGroup(group *Group, d *Dfa, pset *Partition) []*Group {
	signMap := make(map[string][]*DfaState) // мапа название новой группировки -> массив перейденных в нее состояний
	for _, state := range group.States {
		sig := make(map[byte]int) // карта отображения символ - id группы перехода
		for _, symbol := range d.Alphabet {
			nextState := state.Transitions[symbol]
			if nextState != nil {
				foundedGroup := findGroup(nextState, pset) // группа, которой принадлежит найденное состояние
				if foundedGroup != nil {
					sig[symbol] = foundedGroup.Id
				} else {
					sig[symbol] = -1
				}
			} else {
				sig[symbol] = -1
			}
		}

		key := signKey(sig, d.Alphabet)
		signMap[key] = append(signMap[key], state)
	}

	keys := make([]string, 0, len(signMap))
	for key := range signMap {
		keys = append(keys, key)
	}
	sort.Strings(keys)


	subgroups := make([]*Group, 0, len(signMap))
	for _, states := range signMap { // для каждого массива состояний
		stateMap := make(map[int]*DfaState)
		for _, state := range states {
			stateMap[state.ID] = state
		}
		subgroups = append(subgroups, &Group{
			States: stateMap,
		})
	}
	return subgroups
}




func signKey(sig map[byte]int, alphabet []byte) string {
	var builder strings.Builder
	for _, symbol := range alphabet {
		builder.WriteString(fmt.Sprintf("%d|", sig[symbol]))
	}
	return builder.String()
}


func buildMinimizedDFA(oldDfa *Dfa, partition *Partition) *Dfa {
	newDfa := &Dfa{
		Alphabet:     oldDfa.Alphabet,
		States:       make([]*DfaState, 0),
		AcceptStates: make([]*DfaState, 0),
		StateCount:   0,
		ErrorState:   nil,
	}

	groupToState := make(map[int]*DfaState) // группа -> состояние

	groupIDs := make([]int, 0, len(partition.Groups))
	for id := range partition.Groups {
		groupIDs = append(groupIDs, id)
	}
	sort.Ints(groupIDs)


	for _, groupID := range groupIDs {
		group := partition.Groups[groupID]

		newState := newDfaState(newDfa.StateCount, nil)
		newDfa.StateCount++
		newDfa.States = append(newDfa.States, newState)
		groupToState[groupID] = newState

		for _, state := range group.States { // пометка принимающих
			if state.IsAcceptable {
				newState.IsAcceptable = true
				newDfa.AcceptStates = append(newDfa.AcceptStates, newState)
				break
			}
		}

		for _, state := range group.States { // пометка стартовых
			if state == oldDfa.StartState {
				newDfa.StartState = newState
				break
			}
		}

		for _, state := range group.States { // пометка ошибки
			if state == oldDfa.ErrorState {
				newDfa.ErrorState = newState
				break
			}
		}
	}

	for _, groupID := range groupIDs {
		group := partition.Groups[groupID]
		newState := groupToState[groupID]

		var representative *DfaState
		for _, state := range group.States {
			representative = state
			break
		} // берем рандом состояние из группы

		for _, symbol := range newDfa.Alphabet {
			nextState := representative.Transitions[symbol]
			if nextState != nil {
				targetGroup := findGroup(nextState, partition)
				if targetGroup != nil {
					newState.Transitions[symbol] = groupToState[targetGroup.Id] // переход по символу из одной группы в другую
				}
			}
		}
	}

	return newDfa
}




func BuildDfa(expression string) (*Dfa, *nfa.Nfa, error){
	Tree, err := regex_pkg.BuildSyntaxTree(expression)
	if err != nil {return nil, nil, err}
	Nfa := nfa.BuildNfaFromTree(Tree)
	if Nfa == nil  {
		return nil, nil, fmt.Errorf("Cant build nfa\n")
	}
	df, err := BuildDfaFromNfa(Nfa)
	if err != nil {
		return nil, Nfa, nil
	}
	minDf := Minimize(df)
	if minDf == nil {
		return nil, nil, fmt.Errorf("Cant minimize Dfa\n")
	}
	return minDf, nil, nil
}



func AreEquivalent(dfa1, dfa2 *Dfa) bool {
	diff1 := Difference(dfa1, dfa2)
	diff2 := Difference(dfa2, dfa1)

	if !isLanguageEmpty(diff1) || !isLanguageEmpty(diff2){
		return false
	}
	return true
}


func isLanguageEmpty(d *Dfa) bool {
	visited := make(map[*DfaState]bool)
	queue := []*DfaState{d.StartState}
	visited[d.StartState] = true

	for len(queue) > 0 {
		current := queue[0]
		queue = queue[1:]

		if current.IsAcceptable {
			return false
		}

		for _, next := range current.Transitions {
			if next != nil && next != d.ErrorState && !visited[next] {
				visited[next] = true
				queue = append(queue, next)
			}
		}
	}
	return true
}