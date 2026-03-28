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
			search(reader)
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




func search(reader *bufio.Reader) {
	fmt.Println("=== SEARCH MODE ===")
	fmt.Println("Select operation:")
	fmt.Println("1. Search - find first match (with groups)")
	fmt.Println("2. SearchAll - find all matches (with iterator)")
	fmt.Println("3. Accepts - check if whole string matches")
	fmt.Println("4. SearchFrom - find match from specific position")
	fmt.Print("Choose (1-4): ")

	choice, err := reader.ReadString('\n')
	if err != nil {
		fmt.Printf("Input error: %v\n", err)
		return
	}
	choice = strings.TrimSpace(choice)

	fmt.Print("Enter regex: ")
	regex, err := reader.ReadString('\n')
	if err != nil {
		fmt.Printf("Input error: %v\n", err)
		return
	}
	regex = strings.TrimSpace(regex)

	fmt.Print("Enter text: ")
	text, err := reader.ReadString('\n')
	if err != nil {
		fmt.Printf("Input error: %v\n", err)
		return
	}
	text = strings.TrimSpace(text)

	automDfa, automNfa, err := dfa.BuildDfa(regex)
	if err != nil {
		fmt.Printf("Error building automata: %v\n", err)
		return
	}

	switch choice {
	case "1":
		searchFirstMatch(automDfa, automNfa, text)

	case "2":
		searchAllMatches(automDfa, automNfa, text)

	case "3":
		checkAccepts(automDfa, automNfa, text)

	case "4":
		searchFromPosition(reader, automDfa, automNfa, text)

	default:
		fmt.Printf("Invalid choice: %s\n", choice)
	}
}


func searchFirstMatch(automDfa *dfa.Dfa, automNfa *nfa.Nfa, text string) {
	fmt.Println("\n--- FIRST MATCH SEARCH ---")

	var result *nfa.MatchResult

	if automDfa != nil {
		dfaResult := automDfa.Search(text)
		if dfaResult != nil {
			result = &nfa.MatchResult{
				Start:  dfaResult.Start,
				End:    dfaResult.End,
				Text:   dfaResult.Text,
				Groups: make(map[string]string),
			}
		}
	} else if automNfa != nil {
		result = automNfa.Search(text)
	}

	if result == nil {
		fmt.Println("No match found")
		return
	}

	fmt.Printf("Match found: '%s' [%d:%d]\n", result.Text, result.Start, result.End)

	if len(result.Groups) > 0 {
		fmt.Println("Captured groups:")
		for _, name := range result.GroupNames() {
			fmt.Printf("  %s: '%s'\n", name, result.Group(name))
		}
	}
}

func searchAllMatches(automDfa *dfa.Dfa, automNfa *nfa.Nfa, text string) {
	fmt.Println("\n--- ALL MATCHES SEARCH ---")

	if automDfa != nil {
		iter := automDfa.SearchAll(text)
		if iter == nil {
			fmt.Println("No matches found")
			return
		}

		matches := make([]*nfa.MatchResult, 0)
		for iter.Next() {
			dfaMatch := iter.Value()
			if dfaMatch != nil {
				matches = append(matches, &nfa.MatchResult{
					Start:  dfaMatch.Start,
					End:    dfaMatch.End,
					Text:   dfaMatch.Text,
					Groups: make(map[string]string),
				})
			}
		}

		if len(matches) == 0 {
			fmt.Println("No matches found")
			return
		}

		fmt.Println("\n--- Access by index (operator indexing) ---")
		for i := 0; i < len(matches); i++ {
			match := iter.Index(i)
			if match != nil {
				fmt.Printf("  Index %d: '%s'\n", i, match.Text)
			}
		}

	} else if automNfa != nil {
		iter := automNfa.SearchAll(text)
		if iter == nil {
			fmt.Println("No matches found")
			return
		}

		matches := make([]*nfa.MatchResult, 0)
		for iter.Next() {
			match := iter.Value()
			if match != nil {
				matches = append(matches, match)
			}
		}

		if len(matches) == 0 {
			fmt.Println("No matches found")
			return
		}

		fmt.Printf("Found %d match(es):\n", len(matches))
		for i, match := range matches {
			fmt.Printf("\nMatch %d: '%s' [%d:%d]\n", i+1, match.Text, match.Start, match.End)
			if len(match.Groups) > 0 {
				fmt.Println("  Groups:")
				for _, name := range match.GroupNames() {
					fmt.Printf("    %s: '%s'\n", name, match.Group(name))
				}
			}
		}

		fmt.Println("\n--- Access by index (operator indexing) ---")
		for i := 0; i < len(matches); i++ {
			match := iter.Index(i)
			if match != nil {
				fmt.Printf("  Index %d: '%s'\n", i, match.Text)
			}
		}
	} else {
		fmt.Println("No automaton available")
	}
}


func checkAccepts(automDfa *dfa.Dfa, automNfa *nfa.Nfa, text string) {
	fmt.Println("\n--- ACCEPTS CHECK ---")
	fmt.Printf("Checking if whole string '%s' matches the regex...\n", text)

	var result bool

	if automDfa != nil {
		result = automDfa.Accepts(text)
	} else if automNfa != nil {
		result = automNfa.Accepts(text)
	}

	if result {
		fmt.Println("✓ String ACCEPTED - the whole string matches the regex")
	} else {
		fmt.Println("✗ String REJECTED - the whole string does NOT match the regex")
	}
}


func searchFromPosition(reader *bufio.Reader, automDfa *dfa.Dfa, automNfa *nfa.Nfa, text string) {
	fmt.Println("\n--- SEARCH FROM POSITION ---")

	fmt.Print("Enter start position: ")
	startPosStr, err := reader.ReadString('\n')
	if err != nil {
		fmt.Printf("Input error: %v\n", err)
		return
	}
	startPosStr = strings.TrimSpace(startPosStr)

	startPos, err := strconv.Atoi(startPosStr)
	if err != nil {
		fmt.Printf("Invalid position: %v\n", err)
		return
	}

	if startPos < 0 || startPos > len(text) {
		fmt.Printf("Position %d out of range [0, %d]\n", startPos, len(text))
		return
	}

	var result *nfa.MatchResult

	if automDfa != nil {
		dfaResult := automDfa.SearchFrom(text, startPos)
		if dfaResult != nil {
			result = &nfa.MatchResult{
				Start:  dfaResult.Start,
				End:    dfaResult.End,
				Text:   dfaResult.Text,
				Groups: make(map[string]string),
			}
		}
	} else if automNfa != nil {
		result = automNfa.SearchFrom(text, startPos)
	}

	if result == nil {
		fmt.Printf("No match found starting from position %d\n", startPos)
		return
	}

	fmt.Printf("Match found at position %d: '%s' [%d:%d]\n",
		startPos, result.Text, result.Start, result.End)

	if len(result.Groups) > 0 {
		fmt.Println("Captured groups:")
		for _, name := range result.GroupNames() {
			fmt.Printf("  %s: '%s'\n", name, result.Group(name))
		}
	}
}