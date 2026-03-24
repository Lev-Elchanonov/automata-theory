package dialogue

import (
	"bufio"
	"fmt"
	dfa "lab2/pkg/dfa_pkg"
	graph "lab2/pkg/graph_pkg"
	kp "lab2/pkg/kpath_pkg"
	"os"
	"strconv"
	"strings"
)

func Dialogue () {
	reader := bufio.NewReader(os.Stdin)
	var automata *dfa.Dfa
	for {
		printInfo()
		fmt.Print("> ")
		input, err := reader.ReadString('\n')
		if err != nil {fmt.Println(err); return }

		input = strings.TrimSpace(input)
		value, err := strconv.Atoi(input)
		if err != nil {fmt.Println(err); continue}

		if value == 9 {return}
		switch value {
		case 1:
			automata, err = case1(*reader)
			if err != nil {fmt.Println(err); return}
			err = graph.SaveAndOpenGraphVizDfa(automata, "graphs/dfa.dot")
			if err != nil {fmt.Println(err); return}
			break
		case 2:
			fmt.Println("In work:D\n")
			break
		case 3:
			if automata == nil {
				automata, err = case1(*reader)
				if err != nil {fmt.Println(err); return}
			}
			invertedDfa := automata.Invert()
			err = graph.SaveAndOpenGraphVizDfa(invertedDfa, "graphs/inverted.dot")
			if err != nil {fmt.Println(err); return}
			automata = invertedDfa
			break
		case 4:
			if automata == nil {
				automata, err = case1(*reader)
				if err != nil {fmt.Println(err); return}
			}
			reversedDfa := automata.Reverse()
			err = graph.SaveAndOpenGraphVizDfa(reversedDfa, "graphs/reversed.dot")
			if err != nil {fmt.Println(err); return}
			automata = reversedDfa
			break
		case 5:
			if automata == nil {
				automata, err = case1(*reader)
				if err != nil {fmt.Println(err); return}
			}
			automata2, err := case1(*reader)
			if err != nil {fmt.Println(err); return}
			result := dfa.Composition(automata, automata2)
			if result == nil {return}
			err = graph.SaveAndOpenGraphVizDfa(result, "graphs/composition.dot")
			automata = result
			break
		case 6:
			if automata == nil {
				automata, err = case1(*reader)
				if err != nil {fmt.Println(err); return}
			}
			automata2, err := case1(*reader)
			if err != nil {fmt.Println(err); return}
			result := dfa.Difference(automata, automata2)
			if result == nil {return}
			err = graph.SaveAndOpenGraphVizDfa(result, "graphs/difference.dot")
			if err != nil {fmt.Println(err); return}
			automata = result
			break
		case 7:
			if automata == nil {
				automata, err = case1(*reader)
				if err != nil {fmt.Println(err); return}
			}
			reg, err := kp.BuildRegexFromDFA(automata)
			if err != nil {fmt.Println(err); return}
			fmt.Printf("\tRegex: %s", reg)
			fmt.Printf("\n")
			break
		case 8:
			automata = nil
			break
		default:
			fmt.Println("Invalid value: ", value)
		}
	}
}

func case1(reader bufio.Reader) (*dfa.Dfa, error) {
	fmt.Printf("Enter regex: ")
	str, err := reader.ReadString('\n')
	str = strings.TrimSpace(str)
	if err != nil {
		fmt.Println(err);
		return nil, err
	}
	automata, err := dfa.BuildDfa(str)
	if err != nil {
		fmt.Println(err);
		return nil, err
	}
	return automata, nil
}

func printInfo() {
	fmt.Println("1: Build DFA")
	fmt.Println("2: Search menu")
	fmt.Println("3: Invert DFA")
	fmt.Println("4: Reverse DFA")
	fmt.Println("5: Composition")
	fmt.Println("6: Difference")
	fmt.Println("7: K-path")
	fmt.Println("8: Clear DFA")
	fmt.Println("9: Exit")
}