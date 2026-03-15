package main

import (
	"bufio"
	"fmt"
	dfa "lab2/pkg/dfa_pkg"
	nfa "lab2/pkg/nfa_pkg"
	reg "lab2/pkg/regex_pkg"
	"os"
	"strings"
	graph "lab2/pkg/graph_pkg"
	debug "lab2/pkg/debug_pkg"
)

func main() {
	reader := bufio.NewReader(os.Stdin)
	fmt.Printf("Enter regex: ")
	input, err := reader.ReadString('\n')
	input = strings.TrimSuffix(input, "\n")
	Tree, err := reg.BuildSyntaxTree(input)
	if Tree == nil{
		fmt.Println(err)
		return
	}

	Nfa := nfa.BuildNfaFromTree(Tree)
	debug.Print(Nfa)
	graph.SaveAndOpenGraphViz(Nfa, "graphs/nfa_graph.dot")

	Dfa := dfa.BuildDfaFromNfa(Nfa)
	Dfa.PrintDebug(Nfa)
	Dfa.SaveAndOpenGraphViz("graphs/dfa_graph.dot")
	minDfa := dfa.Minimize(Dfa)

	minDfa.SaveAndOpenGraphViz("graphs/mindfa_graph.dot")
	Dfa.DebugMinimizationProcess()
	minDfa.DebugPrint()
	return
}