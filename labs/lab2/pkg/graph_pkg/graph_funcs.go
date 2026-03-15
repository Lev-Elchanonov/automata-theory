package graph_pkg

import (
	"fmt"
	nfa "lab2/pkg/nfa_pkg"
	"os"
	"os/exec"
	"runtime"
	"strings"
)

func GraphViz(n *nfa.Nfa) string {
	var builder strings.Builder

	builder.WriteString("digraph NFA {\n")
	builder.WriteString("  rankdir=LR;\n")
	builder.WriteString("  node [shape = circle];\n")

	builder.WriteString(fmt.Sprintf("  start [shape = point, label = \"\"];\n"))
	builder.WriteString(fmt.Sprintf("  start -> %d;\n", n.StartState.ID))

	for _, state := range n.States {
		if state.IsAcceptable {
			builder.WriteString(fmt.Sprintf("  %d [shape = doublecircle];\n", state.ID))
		}
	}
	for _, state := range n.States {
		for _, eps := range state.Epsilons {
			builder.WriteString(fmt.Sprintf("  %d -> %d [label = \"ε\"];\n", state.ID, eps.ID))
		}

		for ch, targets := range state.Transitions {
			for _, target := range targets {

				label := string(ch)
				if ch == '"' {
					label = "\\\""
				} else if ch == '\\' {
					label = "\\\\"
				}
				builder.WriteString(fmt.Sprintf("  %d -> %d [label = \"%s\"];\n",
					state.ID, target.ID, label))
			}
		}

		if len(state.GroupInfo) > 0 {
			groupLabels := make([]string, 0)
			for groupName, isStart := range state.GroupInfo {
				if isStart {
					groupLabels = append(groupLabels, fmt.Sprintf("start:%s", groupName))
				} else {
					groupLabels = append(groupLabels, groupName)
				}
			}
			builder.WriteString(fmt.Sprintf("  %d [xlabel=\"%s\"];\n",
				state.ID, strings.Join(groupLabels, ", ")))
		}
	}

	builder.WriteString("}\n")
	return builder.String()
}


func openFile(n* nfa.Nfa, filename string) error {
	var cmd *exec.Cmd

	switch runtime.GOOS {
	case "windows":
		cmd = exec.Command("cmd", "/c", "start", filename)
	case "darwin": // macOS
		cmd = exec.Command("open", filename)
	default: // Linux и другие Unix-like
		cmd = exec.Command("xdg-open", filename)
	}

	if err := cmd.Start(); err != nil {
		return fmt.Errorf("ошибка открытия файла: %v", err)
	}

	return nil
}


func  SaveAndOpenGraphViz(n *nfa.Nfa, filename string) error {
	content := GraphViz(n)
	err := os.WriteFile(filename, []byte(content), 0644)
	if err != nil {
		return fmt.Errorf("ошибка сохранения файла: %v", err)
	}

	pngFilename := strings.TrimSuffix(filename, ".dot") + ".png"

	cmd := exec.Command("dot", "-Tpng", filename, "-o", pngFilename)
	if err := cmd.Run(); err != nil {
		return fmt.Errorf("ошибка генерации PNG (установлен ли graphviz?): %v", err)
	}

	fmt.Printf("Граф сохранен в %s и %s\n", filename, pngFilename)

	return openFile(n, pngFilename)
}

