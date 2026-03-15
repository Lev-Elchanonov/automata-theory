package dialogue

import (
	"bufio"
	"fmt"
	dfa "lab2/pkg/dfa_pkg"
	graph "lab2/pkg/graph_pkg"
	nfa "lab2/pkg/nfa_pkg"
	reg "lab2/pkg/regex_pkg"
	"os"
	"strings"
)

func Dialogue () {
	reader := bufio.NewReader(os.Stdin)

	for {
		fmt.Println("Input regex: ")
		input, err := reader.ReadString('\n')
		input = strings.TrimSuffix(input, "\n")
		if err != nil {
			continue
		}


		tree, err := reg.BuildSyntaxTree(input)
		fmt.Println("Syntax tree is ready!\n")
		reader.ReadString('\n')


		nfaAutomaton := nfa.BuildNfaFromTree(tree)
		fmt.Println("NFA is ready!\n")
		graph.SaveAndOpenGraphVizNfa(nfaAutomaton, "graphs/nfa_graph.dot")


		reader.ReadString('\n')


		dfaAutomaton := dfa.BuildDfaFromNfa(nfaAutomaton)
		fmt.Println("DFA is ready!\n")
		err = graph.SaveAndOpenGraphVizDfa(dfaAutomaton, "graphs/dfa_graph.dot")

		reader.ReadString('\n')


		minimizedDfa := dfa.Minimize(dfaAutomaton)
		fmt.Println("minDFA is ready!\n")

		err = graph.SaveAndOpenGraphVizDfa(minimizedDfa, "graphs/mindfa_graph.dot")

		reader.ReadString('\n')
		for {
			fmt.Println("Inter string for check: ")
			str,_ := reader.ReadString('\n')
			str = strings.TrimSuffix(str, "\n")
			res := minimizedDfa.CheckString(str)
			if res {
				fmt.Println("SUCCESS\n")
			} else {
				fmt.Println("FAILURE\n")
			}
			input, err = reader.ReadString('\n')
			if input == "\n" {
				break
			}
		}

	}
}