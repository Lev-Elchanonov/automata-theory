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
		if (err != nil) {
			fmt.Println(err)
			continue
		}
		fmt.Println("Syntax tree is ready!")
		reader.ReadString('\n')


		nfaAutomaton := nfa.BuildNfaFromTree(tree)
		fmt.Println("NFA is ready!")
		graph.SaveAndOpenGraphVizNfa(nfaAutomaton, "graphs/nfa_graph.dot")


		reader.ReadString('\n')


		dfaAutomaton, err := dfa.BuildDfaFromNfa(nfaAutomaton)
		if (err != nil) {
			fmt.Println(err)
			if err.Error() != "Nfa has Named Groups or references. Please inter expression before compile\n"{
				continue
			}
			fmt.Println("Regex contains named groups or refs.\nEnter expression: ")
			expr, _ := reader.ReadString('\n')
			expr = strings.TrimSuffix(expr, "\n")


			//debug_pkg.Print(nfaAutomaton)
			dfaAutomaton, err = dfa.Compile(input, expr, nfaAutomaton)
			if err != nil {
				fmt.Println(err)
				return
			}
		}
		fmt.Println("DFA is ready!")
		err = graph.SaveAndOpenGraphVizDfa(dfaAutomaton, "graphs/dfa_graph.dot")

		reader.ReadString('\n')


		minimizedDfa := dfa.Minimize(dfaAutomaton)
		fmt.Println("minDFA is ready!")


		err = graph.SaveAndOpenGraphVizDfa(minimizedDfa, "graphs/mindfa_graph.dot")

		reader.ReadString('\n')
		for {
			fmt.Println("Inter string for check: ")
			str,_ := reader.ReadString('\n')
			str = strings.TrimSuffix(str, "\n")
			res := minimizedDfa.CheckString(str)
			if res {
				fmt.Println("SUCCESS")
			} else {
				fmt.Println("FAILURE")
			}
			input, err = reader.ReadString('\n')
			if input == "\n" {
				break
			}
		}

	}
}

