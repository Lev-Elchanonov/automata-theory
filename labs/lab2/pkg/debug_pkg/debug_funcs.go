package debug_pkg

import (
	"fmt"
	dfa "lab2/pkg/dfa_pkg"
	nfa "lab2/pkg/nfa_pkg"
	rg "lab2/pkg/regex_pkg"
	"sort"
	"strings"
)

// FOR SYNTAX TREE
// --------------------------------------------
func printNode(node *rg.Node, level int) {
	if node == nil {
		return
	}

	indent := strings.Repeat("  ", level)

	switch node.Type {
	case rg.LeafNode:
		fmt.Printf("%sLeaf: %s (pos:%d)\n", indent, node.Value, node.Position)
	case rg.ConcatNode:
		fmt.Printf("%sConcat\n", indent)
		printNode(node.Left, level+1)
		printNode(node.Right, level+1)
	case rg.UnionNode:
		fmt.Printf("%sUnion\n", indent)
		printNode(node.Left, level+1)
		printNode(node.Right, level+1)
	case rg.KliniNode:
		fmt.Printf("%sKlini (...)\n", indent)
		printNode(node.Left, level+1)
	case rg.QuestionNode:
		fmt.Printf("%sQuestion (?)\n", indent)
		printNode(node.Left, level+1)
	case rg.RepeatNode:
		fmt.Printf("%sRepeat{%d}\n", indent, node.Repeat)
		printNode(node.Left, level+1)
	case rg.GroupNode:
		fmt.Printf("%sGroup(%s)\n", indent, node.Value)
		printNode(node.Left, level+1)
	case rg.RefNode:
		fmt.Printf("%sRef(%s)\n", indent, node.Value)
	}
}

func PrintSyntaxTree(tree *rg.SyntaxTree) {
	fmt.Println("=== Syntax Tree ===")
	printNode(tree.Root, 0)
	fmt.Println("Leaves:")
	for _, leaf := range tree.Leaves {
		fmt.Printf("  Pos %d: %s\n", leaf.Position, leaf.Value)
	}
}

// --------------------------------------------



// FOR NFA
// --------------------------------------------


func Print(n *nfa.Nfa) {
	fmt.Println("=== NFA ===")
	fmt.Printf("Start state: %d\n", n.StartState.ID)
	fmt.Printf("Accept state: %d\n", n.AcceptState.ID)
	fmt.Println("States:")

	for _, state := range n.States {
		fmt.Printf("  State %d:", state.ID)
		if state.IsAcceptable {
			fmt.Print(" (accepting)")
		}
		fmt.Println()

		if len(state.Epsilons) > 0 {
			fmt.Printf("    ε ->")
			for _, eps := range state.Epsilons {
				fmt.Printf(" %d", eps.ID)
			}
			fmt.Println()
		}

		for ch, targets := range state.Transitions {
			fmt.Printf("    '%c' ->", ch)
			for _, target := range targets {
				fmt.Printf(" %d", target.ID)
			}
			fmt.Println()
		}

		if len(state.GroupInfo) > 0 {
			fmt.Printf("    groups: %v\n", state.GroupInfo)
		}
	}
}



// FOR DFA
// --------------------------------------------


func DebugPrint(d *dfa.Dfa) {
	fmt.Println("\n=== ДЕТАЛЬНЫЙ ДЕБАГ ДКА ===")
	fmt.Printf("Всего состояний: %d\n", len(d.States))
	fmt.Printf("Алфавит: %s\n", string(d.Alphabet))
	fmt.Printf("Начальное состояние: %d\n", d.StartState.ID)

	fmt.Printf("Принимающие состояния (%d шт): ", len(d.AcceptStates))
	for i, state := range d.AcceptStates {
		if i > 0 {
			fmt.Printf(", ")
		}
		fmt.Printf("%d", state.ID)
	}
	fmt.Println()

	if d.ErrorState != nil {
		fmt.Printf("Состояние ошибки: %d\n", d.ErrorState.ID)
	}

	fmt.Println("\n--- Таблица переходов ---")

	// Заголовок
	fmt.Printf("%-10s", "Состояние")
	for _, sym := range d.Alphabet {
		fmt.Printf(" | '%c'", sym)
	}
	fmt.Println()
	fmt.Println(strings.Repeat("-", 10+len(d.Alphabet)*8))


	states := make([]*dfa.DfaState, 0, len(d.States))
	for _, state := range d.States {
		states = append(states, state)
	}
	sort.Slice(states, func(i, j int) bool { return states[i].ID < states[j].ID })

	for _, state := range states {
		marker := "  "
		if state == d.ErrorState {
			marker = "ERR"
		} else if state.IsAcceptable {
			marker = "ACC"
		} else if state == d.StartState {
			marker = "STR"
		}

		fmt.Printf("%-10s", fmt.Sprintf("%d %s", state.ID, marker))

		for _, sym := range d.Alphabet {
			nextState := state.Transitions[sym]
			if nextState != nil {
				fmt.Printf(" | %-6d", nextState.ID)
			} else {
				fmt.Printf(" | %-6s", "—")
			}
		}
		fmt.Println()
	}
}


func DebugPrintPartition(p *dfa.Partition, step int) {
	fmt.Printf("\n=== Шаг %d: Разбиение ===\n", step)
	fmt.Printf("Всего групп: %d\n", p.GroupsCount)

	groups := make([]*dfa.Group, 0, len(p.Groups))
	for _, group := range p.Groups {
		groups = append(groups, group)
	}
	sort.Slice(groups, func(i, j int) bool { return groups[i].Id < groups[j].Id })

	for _, group := range groups {

		stateIDs := make([]int, 0, len(group.States))
		for id := range group.States {
			stateIDs = append(stateIDs, id)
		}
		sort.Ints(stateIDs)


		statesStr := fmt.Sprintf("%v", stateIDs)
		fmt.Printf("  Группа %2d: %s\n", group.Id, statesStr)
	}
}


func DebugMinimizationProcess(d *dfa.Dfa) {
	fmt.Println("\n=== ПРОЦЕСС МИНИМИЗАЦИИ ДКА ===")

	fmt.Println("\n--- Шаг 1: Начальное разбиение ---")
	acceptIDs := make([]int, 0, len(d.AcceptStates))
	for _, state := range d.AcceptStates {
		acceptIDs = append(acceptIDs, state.ID)
	}
	sort.Ints(acceptIDs)
	fmt.Printf("Принимающие состояния: %v\n", acceptIDs)

	nonAcceptIDs := make([]int, 0)
	for _, state := range d.States {
		if !state.IsAcceptable && state != d.ErrorState {
			nonAcceptIDs = append(nonAcceptIDs, state.ID)
		}
	}
	sort.Ints(nonAcceptIDs)
	fmt.Printf("Непринимающие состояния: %v\n", nonAcceptIDs)

	if d.ErrorState != nil {
		fmt.Printf("Состояние ошибки: %d\n", d.ErrorState.ID)
	}
}


func Print_pset(pset *dfa.Partition) {
	for _, group := range pset.Groups {
		fmt.Printf("->%d: ", group.Id)
		for _, state := range group.States {
			fmt.Printf("%d,", state.ID)
		}
		fmt.Printf("\n")
	}
}


