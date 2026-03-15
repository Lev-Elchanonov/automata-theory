package debug_pkg

import (
	"fmt"
	nfa "lab2/pkg/nfa_pkg"
	rg "lab2/pkg/regex_pkg"
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

