package main

import (
	"bufio"
	"fmt"
	dfa "lab2/pkg/dfa_pkg"
	nfa "lab2/pkg/nfa_pkg"
	reg "lab2/pkg/regex_pkg"
	"os"
	"strings"
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
	//Tree.Print()
	fmt.Println("\n\n")
	Nfa := nfa.BuildNfaFromTree(Tree)
	//Nfa.Print()
	Nfa.SaveAndOpenGraphViz("graphs/nfa_graph.dot")
	Dfa := dfa.BuildDfaFromNfa(Nfa)
	Dfa.PrintDebug(Nfa)
	Dfa.SaveAndOpenGraphViz("graphs/dfa_graph.dot")
	minDfa := Minimize
	return
}