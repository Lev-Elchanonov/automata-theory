package regex_pkg

import (
	"fmt"
	"strings"
	"unicode"
)

type NodeType int

const (
	LeafNode NodeType = iota
	ConcatNode
	UnionNode
	KliniNode
	QuestionNode
	RepeatNode
	GroupNode
	RefNode
)

type Node struct {
	Type NodeType
	Value string
	Left *Node
	Right *Node
	Repeat int
	Nullable bool
	FirstPos []int
	LastPos []int
	Position int
}

type SyntaxTree struct{
	Root *Node
	Leaves []*Node
	PosCount int
}


func BuildSyntaxTree (regex string) (*SyntaxTree, error) {
	regex = "(" + regex + ")"
	tree := &SyntaxTree{
		Leaves:   make([]*Node, 0),
		PosCount: 0,
	}
	stack := make([]interface{}, 0)
	groupsCount := make(map[string]int, 0)
	for i := 0; i < len(regex); i++ {
		ch := regex[i]
		switch {
		case ch == '(':
			i = processOpBrace(&regex, i, &stack, &groupsCount)
			if i == -1 {
				return nil, fmt.Errorf("unclosed group name")
			}
		case ch == ')':
			err := processClBrace(&stack, tree, &groupsCount)
			if err != nil {
				return nil, err
			}
		case ch == '|':
			stack = append(stack, '|')
		case ch == '.' && i+2 < len(regex) && regex[i+1] == '.' && regex[i+2] == '.':
			i = processKlini(&stack, i)
		case ch == '?':
			processQuestion(&stack)
		case ch == '{':
			i = processOpFigBrace(&regex, i, &stack)
			if i == -1 {
				return nil, fmt.Errorf("invalid figure brace")
			}
		case ch == '<' && i > 0 && regex[i-1] != '(':
			i = processOpTreeBrace(&regex, i, &stack, &groupsCount)
			if i == -1{
				return nil, fmt.Errorf("unclosed group name")
			}
		default:
			i = processDefault(ch, i, &regex, tree, &stack)
			if i == -1 {
				return nil, fmt.Errorf("invalid syntax")
			}
		}
	}
	if len(stack) != 1{

		return nil, fmt.Errorf("unknown regex")
	}
	tree.Root = stack[0].(*Node)
	return tree, nil
}



func createLeafNode (value string, tree *SyntaxTree) *Node {
	tree.PosCount++
	node := &Node{
		Type: LeafNode,
		Value: value,
		Position: tree.PosCount,
	}
	tree.Leaves = append(tree.Leaves, node)
	return node;
}

func createEpsilonNode() *Node{
	node := &Node{
		Type: LeafNode,
		Value: "epsilon",
		Position: 0,
	}
	return node
}

func processNodes(nodes []interface{}, tree *SyntaxTree) *Node {
	if len(nodes) == 0{
		return createEpsilonNode()
	}
	var result *Node
	current := make([]interface{}, 0)
	for i := 0; i < len(nodes); i++ {
		if nodes[i] == '|' {
			left := processConcat(current, tree)
			right := processNodes(nodes[i+1:], tree)
			result = &Node{
				Type:  UnionNode,
				Left:  left,
				Right: right,
			}
			break
		} else {
			current = append(current, nodes[i])
		}
	}
	if result == nil{
		result = processConcat(current, tree)
	}
	return result
}

func processConcat(nodes []interface{}, tree *SyntaxTree) *Node {
	if len(nodes) == 0{
		return createEpsilonNode()
	}
	if len(nodes) == 1{
		return nodes[0].(*Node)
	}
	//тут построение дерева
	var result *Node
	for i := 0; i < len(nodes); i++ {
		if node, ok := nodes[i].(*Node); ok{
			if result == nil{
				result = node
			} else {
				result = &Node{
					Type: ConcatNode,
					Left: result,
					Right: node,
				}
			}
		}
	}
	return result
}

func isMeta(ch byte) bool {
	return ch == '(' || ch == ')' || ch == '|' || ch == '.' ||
		ch == '?' || ch == '{' || ch == '}' || ch == '<' ||
		ch == '>' || ch == '%'
}


func (tree *SyntaxTree) Print() {
	fmt.Println("=== Syntax Tree ===")
	printNode(tree.Root, 0)
	fmt.Println("Leaves:")
	for _, leaf := range tree.Leaves {
		fmt.Printf("  Pos %d: %s\n", leaf.Position, leaf.Value)
	}
}


// для отладки, потом уберу
func printNode(node *Node, level int) {
	if node == nil {
		return
	}

	indent := strings.Repeat("  ", level)

	switch node.Type {
	case LeafNode:
		fmt.Printf("%sLeaf: %s (pos:%d)\n", indent, node.Value, node.Position)
	case ConcatNode:
		fmt.Printf("%sConcat\n", indent)
		printNode(node.Left, level+1)
		printNode(node.Right, level+1)
	case UnionNode:
		fmt.Printf("%sUnion\n", indent)
		printNode(node.Left, level+1)
		printNode(node.Right, level+1)
	case KliniNode:
		fmt.Printf("%sKlini (...)\n", indent)
		printNode(node.Left, level+1)
	case QuestionNode:
		fmt.Printf("%sQuestion (?)\n", indent)
		printNode(node.Left, level+1)
	case RepeatNode:
		fmt.Printf("%sRepeat{%d}\n", indent, node.Repeat)
		printNode(node.Left, level+1)
	case GroupNode:
		fmt.Printf("%sGroup(%s)\n", indent, node.Value)
		printNode(node.Left, level+1)
	case RefNode:
		fmt.Printf("%sRef(%s)\n", indent, node.Value)
	}
}


func processOpBrace (regex *string, i int, stack *[]interface{}, existGroups *map[string]int) (int) {
	if i+1 < len(*regex) && (*regex)[i+1] == '<' {
		endNamePos := -1
		var name string
		is_open := false
		for j := i + 2; j < len(*regex); j++ {
			if (*regex)[j] == '<' || (*regex)[j] == '>'{

				if (*regex)[j] == '<' && !is_open{
					is_open = true
				}
				if j >= 1 && j+1 < len(*regex) && (*regex)[j-1] == '%' && (*regex)[j+1] == '%' {
					j = changePers(regex, j, &name)
					continue
				}
				if (*regex)[j] == '<' && is_open{
					return -1
				}
				if (*regex)[j] == '>' {
					endNamePos = j
					break
				}
			}

			name += string((*regex)[j])
		}
		if endNamePos == -1 {
			return -1
		}
		fmt.Printf("Имя группы: '%s'\n", name)
		value, exists := (*existGroups)[name]
		if exists {
			(*existGroups)[name] = value+1
		} else {
			(*existGroups)[name] = 0
		}
		*stack = append(*stack, fmt.Sprintf("<%s>", name))
		i = endNamePos
		return endNamePos
	} else {
		*stack = append(*stack, '(')
	}
	return i
}


func changePers(regex *string, j int, name *string) (int) {
	*regex = (*regex)[:j-1] + string('_') + (*regex)[j:]
	*regex = (*regex)[:j+1] + string('_') + (*regex)[j+2:]
	*name = (*name)[:len(*name)-1]
	*name += string((*regex)[j])

	j += 1
	return j
}

func processClBrace (stack *[]interface{}, tree *SyntaxTree, existGroups *map[string]int) (error) {
	nodes := make([]interface{}, 0)
	var groupName string
	groupFound := false
	for len(*stack) > 0 {
		top := (*stack)[len(*stack)-1]
		*stack = (*stack)[:len(*stack)-1]
		if str, ok := top.(string); ok && strings.HasPrefix(str, "<") && strings.HasSuffix(str, ">") {
			groupName = strings.TrimPrefix(str, "<")
			groupName = strings.TrimSuffix(groupName, ">")
			groupFound = true
			break
		}
		if top == '(' {
			break
		}
		nodes = append([]interface{}{top}, nodes...)
	}
	innerNode := processNodes(nodes, tree)
	if !groupFound{
		*stack = append(*stack, innerNode)
		return nil
	}

	count, exists := (*existGroups)[groupName]
	fmt.Println(groupName)
	if !exists || (groupName == "") {
		fmt.Printf("Stack size: %d\n", len(*stack))
		fmt.Printf("GroupFound: %b\n", groupFound)
		if len(*stack) == 0{
			*stack = append(*stack, innerNode)
			return nil
		} else {
			return fmt.Errorf("unknown name")
		}
	}

	if count == 0{
		fmt.Println("declaring group")
		groupNode := &Node{
			Type:  GroupNode,
			Value: groupName,
			Left:  innerNode,
		}
		*stack = append(*stack, groupNode)
	} else {
		fmt.Println("referencing group")
		refNode := &Node{
			Type:  RefNode,
			Value: groupName,
		}
		if innerNode != nil && innerNode.Type != LeafNode && innerNode.Value != "epsilon" {
			concatNode := &Node{
				Type:  ConcatNode,
				Left:  refNode,
				Right: innerNode,
			}
			*stack = append(*stack, concatNode)
		} else {
			*stack = append(*stack, refNode)
		}
	}
	return nil
}

func processKlini(stack *[]interface{}, i int) (int){
	if len(*stack) > 0 {
		last := (*stack)[len(*stack)-1]
		if node, ok := last.(*Node); ok {
			starNode := &Node{
				Type: KliniNode,
				Left: node,
			}
			(*stack)[len(*stack)-1] = starNode
		}
	}
	i += 2
	return i
}

func processQuestion(stack *[]interface{}) {
	if len(*stack) > 0 {
		last := (*stack)[len(*stack)-1]
		if node, ok := last.(*Node); ok {
			questNode := &Node{
				Type: QuestionNode,
				Left: node,
			}
			(*stack)[len(*stack)-1] = questNode
		}
	}
}

func processOpFigBrace(regex *string, i int, stack *[]interface{}) (int){
	endBrace := strings.Index((*regex)[i:], "}")
	if endBrace == -1 {
		return -1
	}
	var count int
	for k := i+1; k < i+endBrace; k++ {
		if !unicode.IsNumber(rune((*regex)[k])){
			return -1
		}
	}
	_, err := fmt.Sscanf((*regex)[i+1:i+endBrace], "%d", &count)
	if err != nil {
		return -1
	}
	if len(*stack) > 0 {
		last := (*stack)[len(*stack)-1]
		if node, ok := last.(*Node); ok {
			repeatNode := &Node{
				Type:   RepeatNode,
				Left:   node,
				Repeat: count,
			}
			(*stack)[len(*stack)-1] = repeatNode
		}
	}
	i += endBrace
	return i
}

func processOpTreeBrace(regex *string, i int, stack *[]interface{}, groupsCount *map[string]int) (int){
	endNamePos := -1
	var name string
	is_open := false
	for j := i + 1; j < len(*regex); j++ {
		if (*regex)[j] == '<' || (*regex)[j] == '>'{
			if (*regex)[j] == '<' && !is_open{
				is_open = true
			}
			if j >= 1 && j+1 < len(*regex) && (*regex)[j-1] == '%' && (*regex)[j+1] == '%' {
				j = changePers(regex, j, &name)
				continue
			}
			if (*regex)[j] == '<' && is_open{
				return -1
			}
			if (*regex)[j] == '>' {
				endNamePos = j
				break
			}
		}
		name += string((*regex)[j])
	}
	fmt.Printf("%s\n", name)
	if endNamePos == -1 {
		return -1
	}
	_, exists := (*groupsCount)[name]
	if !exists || name == ""{
		return -1;
	}

	refNode := &Node{
		Type:  RefNode,
		Value: name,
	}
	*stack = append(*stack, refNode)
	i = endNamePos
	return i
}


func processDefault(ch byte, i int, regex *string, tree *SyntaxTree, stack *[]interface{}) (int) {
	if ch == '%' && i+2 < len(*regex) && i+2 < len(*regex) && (*regex)[i+2] == '%' {
		leafNode := createLeafNode(string((*regex)[i+1]), tree)
		*stack = append(*stack, leafNode)
		i += 2
	} else if !isMeta(ch) {
		leafNode := createLeafNode(string(ch), tree)
		*stack = append(*stack, leafNode)
	} else if isMeta(ch) {
		return -1
	}
	return i
}
