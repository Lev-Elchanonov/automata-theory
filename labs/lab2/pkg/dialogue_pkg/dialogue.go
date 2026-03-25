package dialogue

import (
	"bufio"
	"fmt"
	dfa "lab2/pkg/dfa_pkg"
	graph "lab2/pkg/graph_pkg"
	nfa "lab2/pkg/nfa_pkg"
	"os"
	"strconv"
	"strings"
)

func Dialogue () {
	reader := bufio.NewReader(os.Stdin)
	var automataDfa *dfa.Dfa
	var automataNfa *nfa.Nfa
	for {
		printInfo()
		fmt.Print("> ")
		input, err := reader.ReadString('\n')
		if err != nil {fmt.Println(err); return }

		input = strings.TrimSpace(input)
		value, err := strconv.Atoi(input)
		if err != nil {fmt.Println(err); continue}

		if value == 8 {return}
		switch value {
		case 1:
			automataDfa, automataNfa, err = case1(*reader)
			if err != nil {fmt.Println(err); return}
			if automataDfa != nil{
				err = graph.SaveAndOpenGraphVizDfa(automataDfa, "graphs/dfa.dot")
			} else if automataNfa != nil{
				fmt.Println("\t> Regex contains groups, NFA build")
				err = graph.SaveAndOpenGraphVizNfa(automataNfa, "graphs/nfa_dot")
			}
			if err != nil {fmt.Println(err); return}
			break
		case 2:
			fmt.Println("In work:D")
			break
		case 3:
			if automataDfa == nil {
				automataDfa, automataNfa, err = case1(*reader)
				if err != nil {fmt.Println(err); return}
				if automataDfa == nil && automataNfa != nil {
					fmt.Println("\t> Cant invert NFA")
					break
				}
			}
			invertedDfa := automataDfa.Invert()
			err = graph.SaveAndOpenGraphVizDfa(invertedDfa, "graphs/inverted.dot")
			if err != nil {fmt.Println(err); return}
			automataDfa = invertedDfa
			break
		case 4:
			if automataDfa == nil {
				automataDfa,automataNfa, err = case1(*reader)
				if err != nil {fmt.Println(err); return}
				if automataDfa == nil && automataNfa != nil {
					fmt.Println("\t> Cant reverse NFA")
					break
				}
			}
			reversedDfa := automataDfa.Reverse()
			err = graph.SaveAndOpenGraphVizDfa(reversedDfa, "graphs/reversed.dot")
			if err != nil {fmt.Println(err); return}
			automataDfa = reversedDfa
			break
		case 5:
			if automataDfa == nil {
				automataDfa, automataNfa, err = case1(*reader)
				if err != nil {fmt.Println(err); return}
				if automataDfa == nil && automataNfa != nil {
					fmt.Println("\t> Cant execute difference on NFA")
					break
				}
			}
			automata2Dfa, automata2Nfa, err := case1(*reader)
			if err != nil {fmt.Println(err); return}
			if automata2Dfa == nil && automata2Nfa != nil {
				fmt.Println("\t> Cant execute difference on NFA")
				break
			}
			result := dfa.Difference(automataDfa, automata2Dfa)
			if result == nil {return}
			err = graph.SaveAndOpenGraphVizDfa(result, "graphs/difference.dot")
			if err != nil {fmt.Println(err); return}
			automataDfa = result
			break
		case 6:
			if automataDfa == nil {
				automataDfa, automataNfa, err = case1(*reader)
				if err != nil {fmt.Println(err); return}
				if automataDfa == nil && automataNfa != nil {
					fmt.Println("\t> Cant execute k-path on NFA")
				}
			}
			reg, err := dfa.BuildRegexFromDFA(automataDfa)
			if err != nil {fmt.Println(err); return}
			fmt.Printf("\tRegex: %s", reg)
			fmt.Printf("\n")
			break
		case 7:
			automataDfa = nil
			automataNfa = nil
			break
		default:
			fmt.Println("\t> Invalid value: ", value)
		}
	}
}

func case1(reader bufio.Reader) (*dfa.Dfa, *nfa.Nfa, error) {
	fmt.Printf("Enter regex: ")
	str, err := reader.ReadString('\n')
	str = strings.TrimSpace(str)
	if err != nil {
		fmt.Println(err);
		return nil, nil, err
	}
	automataDfa, automataNfa, err := dfa.BuildDfa(str)
	if err != nil {
		fmt.Println(err);
		return nil, nil, err
	}
	return automataDfa, automataNfa, nil
}

func printInfo() {
	fmt.Println("1: Build DFA")
	fmt.Println("2: Search menu")
	fmt.Println("3: Invert DFA")
	fmt.Println("4: Reverse DFA")
	fmt.Println("5: Difference")
	fmt.Println("6: K-path")
	fmt.Println("7: Clear")
	fmt.Println("8: Exit")
}