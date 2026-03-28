package nfa

import (
	"fmt"
	"sort"
)

type MatchResult struct {
	Start  int
	End    int
	Text   string
	Groups map[string]string
}

type SearchContext struct {
	State       *NfaState
	Groups      map[string]string
	GroupStart  map[string]int
	GroupClosed map[string]bool
	Pos         int
	StartPos    int
}


func (n *Nfa) Search(text string) *MatchResult {
	return n.SearchFrom(text, 0)
}


func (n *Nfa) SearchFrom(text string, startPos int) *MatchResult {
	var bestMatch *MatchResult
	for i := startPos; i < len(text); i++ {
		result := n.matchAt(text, i)
		if result != nil {
			if bestMatch == nil || n.isBetterMatch(result, bestMatch) {
				bestMatch = result
			}
		}
	}
	return bestMatch
}

func (n *Nfa) isBetterMatch(a, b *MatchResult) bool {
	if len(a.Text) != len(b.Text) {
		return len(a.Text) > len(b.Text)
	}
	lenA := 0
	lenB := 0
	for _, text := range a.Groups {
		lenA += len(text)
	}
	for _, text := range b.Groups {
		lenB += len(text)
	}
	return lenA > lenB
}

func (n *Nfa) SearchAll(text string) *MatchIterator {
	allMatches := n.findAllFrom(text, 0)

	sort.Slice(allMatches, func(i, j int) bool {
		if allMatches[i].Start != allMatches[j].Start {
			return allMatches[i].Start < allMatches[j].Start
		}
		return allMatches[i].End < allMatches[j].End
	})

	return &MatchIterator{
		nfa:        n,
		text:       text,
		pos:        0,
		allMatches: allMatches,
		index:      0,
	}
}

func (n *Nfa) matchAt(text string, start int) *MatchResult {
	contexts := n.initContexts(start)
	var bestResult *MatchResult
	bestLength := -1

	for len(contexts) > 0 {
		var newContexts []*SearchContext

		for _, ctx := range contexts {
			if ctx.State.IsAcceptable {
				result := n.buildMatchResult(text, ctx)
				if result != nil && len(result.Text) > bestLength {
					bestLength = len(result.Text)
					bestResult = result
				}
			}
			if ctx.Pos == len(text) {
				for _, eps := range ctx.State.Epsilons {
					if eps.IsRef {
						continue
					}
					newCtx := n.copyContext(ctx)
					newCtx.State = eps
					newContexts = append(newContexts, newCtx)
				}
				continue
			}
			if ctx.State.IsRef {
				n.handleRef(ctx, text, &newContexts)
				continue
			}
			ch := text[ctx.Pos]
			if targets, ok := ctx.State.Transitions[ch]; ok {
				for _, target := range targets {
					newCtx := n.processTarget(ctx, text, target)

					if newCtx.State.IsAcceptable { // для жадности
						result := n.buildMatchResult(text, newCtx)
						if result != nil && len(result.Text) > bestLength {
							bestLength = len(result.Text)
							bestResult = result
						}
					}
					if newCtx.State.IsRef {
						n.handleRef(newCtx, text, &newContexts)
						continue
					}

					n.epsilonClosureForContext(newCtx, text, &newContexts)
					newContexts = append(newContexts, newCtx)
				}
			}

			for _, eps := range ctx.State.Epsilons {
				newCtx := n.processEpsTarget(ctx, eps, text)
				newContexts = append(newContexts, newCtx)
			}
		}
		n.sortContextsByProgress(newContexts)
		contexts = newContexts
	}
	return bestResult
}


func (n *Nfa) initContexts(start int) []*SearchContext{
	contexts := []*SearchContext{{
		State:       n.StartState,
		Groups:      make(map[string]string),
		GroupStart:  make(map[string]int),
		GroupClosed: make(map[string]bool),
		Pos:         start,
		StartPos:    start,
	}}


	for groupName, isStart := range n.StartState.GroupInfo {
		if isStart {
			contexts[0].GroupStart[groupName] = start
		}
	}
	return contexts
}

func (n *Nfa) processTarget(ctx *SearchContext, text string, target *NfaState) *SearchContext{
	newCtx := n.copyContext(ctx)
	newCtx.State = target
	newCtx.Pos = ctx.Pos + 1
	return n.processGroupsInProcess(ctx, newCtx, text, target)
}

func (n *Nfa) processEpsTarget(ctx *SearchContext, eps *NfaState, text string) *SearchContext {
	newCtx := n.copyContext(ctx)
	newCtx.State = eps
	return n.processGroupsInProcess(ctx, newCtx, text, eps)
}

func (n *Nfa) processGroupsInProcess(ctx, newCtx *SearchContext, text string, target *NfaState) *SearchContext {
	for groupName, isStart := range target.GroupInfo {
		if isStart && !ctx.GroupClosed[groupName] {
			newCtx.GroupStart[groupName] = ctx.Pos
		}
	}
	for groupName := range ctx.GroupStart {
		if ctx.GroupClosed[groupName] {
			continue
		}

		_, currentInGroup := ctx.State.GroupInfo[groupName]
		_, nextInGroup := target.GroupInfo[groupName]

		if currentInGroup && !nextInGroup {
			if startPos, ok := ctx.GroupStart[groupName]; ok { // вышли из группы захвата
				captured := text[startPos:ctx.Pos]
				newCtx.Groups[groupName] = captured
				delete(newCtx.GroupStart, groupName)
				newCtx.GroupClosed[groupName] = true
			}
		}
	}
	return newCtx
}

// добавления всех e-замыканий для контекста
func (n *Nfa) epsilonClosureForContext(ctx *SearchContext, text string, newContexts *[]*SearchContext) {
	// Применяем ε-замыкание к ctx.State
	queue := []*SearchContext{ctx}
	visited := make(map[*NfaState]bool)
	visited[ctx.State] = true

	for len(queue) > 0 {
		current := queue[0]
		queue = queue[1:]

		for _, eps := range current.State.Epsilons {
			if visited[eps] {
				continue
			}
			visited[eps] = true

			newCtx := n.copyContext(current)
			newCtx.State = eps
			n.processGroupsInEpsClosure(current, text, eps, newCtx)
			if newCtx.State.IsRef {
				n.handleRef(newCtx, text, newContexts)
			} else {
				*newContexts = append(*newContexts, newCtx)
				queue = append(queue, newCtx)
			}
		}
	}
}

func (n *Nfa) processGroupsInEpsClosure(current *SearchContext, text string, eps *NfaState, newCtx *SearchContext) {
	for groupName := range current.GroupStart {
		if current.GroupClosed[groupName] {
			continue
		}
		_, currentInGroup := current.State.GroupInfo[groupName]
		_, nextInGroup := eps.GroupInfo[groupName]
		if currentInGroup && !nextInGroup {
			if startPos, ok := current.GroupStart[groupName]; ok {
				captured := text[startPos:current.Pos]
				newCtx.Groups[groupName] = captured
				delete(newCtx.GroupStart, groupName)
				newCtx.GroupClosed[groupName] = true
			}
		}
	}
	for groupName, isStart := range eps.GroupInfo {
		if isStart && !current.GroupClosed[groupName] {
			newCtx.GroupStart[groupName] = current.Pos
		}
	}
}
// выбираем самый длинный контекст
func (n *Nfa) sortContextsByProgress(contexts []*SearchContext) {
	sort.Slice(contexts, func(i, j int) bool {
		if contexts[i].Pos != contexts[j].Pos {
			return contexts[i].Pos > contexts[j].Pos
		}
		lenI := 0
		lenJ := 0
		for _, t := range contexts[i].Groups {
			lenI += len(t)
		}
		for _, t := range contexts[j].Groups {
			lenJ += len(t)
		}
		return lenI > lenJ
	})
}

func (n *Nfa) handleRef(ctx *SearchContext, text string, newContexts *[]*SearchContext) {
	expectedText := ctx.Groups[ctx.State.RefGroup]
	if expectedText == "" { // если группа опциональная и не имеет текста
		for _, eps := range ctx.State.Epsilons {
			newCtx := n.copyContext(ctx)
			newCtx.State = eps
			newCtx.Pos = ctx.Pos
			n.addEpsilonClosure(newCtx, text, newContexts)
		}
		return
	}

	if ctx.Pos+len(expectedText) <= len(text) &&
		text[ctx.Pos:ctx.Pos+len(expectedText)] == expectedText {
		for _, eps := range ctx.State.Epsilons {
			newCtx := n.copyContext(ctx)
			newCtx.State = eps
			newCtx.Pos = ctx.Pos + len(expectedText)
			n.addEpsilonClosure(newCtx, text, newContexts)
		}
	}
}

// используется для добавления e-замыканий для ссылок
func (n *Nfa) addEpsilonClosure(ctx *SearchContext, text string, newContexts *[]*SearchContext) {
	visited := make(map[*NfaState]bool)
	queue := []*SearchContext{ctx}
	visited[ctx.State] = true

	for len(queue) > 0 {
		current := queue[0]
		queue = queue[1:]

		if current.State.IsAcceptable {
			result := n.buildMatchResult(text, current)
			if result != nil {
				*newContexts = append(*newContexts, current)
			}
			if current.Pos == len(text) {
				*newContexts = append(*newContexts, current)
			}
		}

		for _, eps := range current.State.Epsilons {
			if visited[eps] {
				continue
			}
			visited[eps] = true
			newCtx := n.copyContext(current)
			newCtx.State = eps
			n.processGroupsInEpsClosure(current, text, eps, newCtx)
			queue = append(queue, newCtx)
			*newContexts = append(*newContexts, newCtx)
		}
	}
}



func (n *Nfa) copyContext(ctx *SearchContext) *SearchContext {
	groups := make(map[string]string)
	for k, v := range ctx.Groups {
		groups[k] = v
	}
	groupStart := make(map[string]int)
	for k, v := range ctx.GroupStart {
		groupStart[k] = v
	}
	groupClosed := make(map[string]bool)
	for k, v := range ctx.GroupClosed {
		groupClosed[k] = v
	}
	return &SearchContext{
		State:       ctx.State,
		Groups:      groups,
		GroupStart:  groupStart,
		GroupClosed: groupClosed,
		Pos:         ctx.Pos,
		StartPos:    ctx.StartPos,
	}
}


func (n *Nfa) buildMatchResult(text string, ctx *SearchContext) *MatchResult {
	result := &MatchResult{
		Start:  ctx.StartPos,
		End:    ctx.Pos,
		Text:   text[ctx.StartPos:ctx.Pos],
		Groups: make(map[string]string),
	}

	for groupName, groupText := range ctx.Groups {
		result.Groups[groupName] = groupText
	}
	for groupName, startPos := range ctx.GroupStart {
		if _, exists := result.Groups[groupName]; !exists {
			result.Groups[groupName] = text[startPos:ctx.Pos]
		}
	}
	return result
}



// Group возвращает текст группы по имени
func (m *MatchResult) Group(name string) string {
	if m.Groups == nil {
		return ""
	}
	return m.Groups[name]
}

// GroupNames возвращает все имена групп
func (m *MatchResult) GroupNames() []string {
	names := make([]string, 0, len(m.Groups))
	for name := range m.Groups {
		names = append(names, name)
	}
	sort.Strings(names)
	return names
}

// HasGroup проверяет существование группы
func (m *MatchResult) HasGroup(name string) bool {
	_, exists := m.Groups[name]
	return exists
}


func (n *Nfa) findAllFrom(text string, startPos int) []*MatchResult {
	var results []*MatchResult
	seen := make(map[string]bool)

	for i := startPos; i < len(text); i++ {
		matches := n.findAllMatchesAt(text, i)
		for _, m := range matches {
			key := fmt.Sprintf("%d-%d", m.Start, m.End)
			if !seen[key] {
				seen[key] = true
				results = append(results, m)
			}
		}
	}

	return results
}

//findAllMatchesAt возвращает ВСЕ совпадения, начинающиеся с позиции start
func (n *Nfa) findAllMatchesAt(text string, start int) []*MatchResult {
	contexts := n.initContexts(start)
	var results []*MatchResult
	for len(contexts) > 0 {
		var newContexts []*SearchContext
		for _, ctx := range contexts {
			if ctx.State.IsAcceptable {
				result := n.buildMatchResult(text, ctx)
				if result != nil {
					results = append(results, result)
				}
			}
			if ctx.Pos == len(text) {
				if ctx.State.IsAcceptable {
					result := n.buildMatchResult(text, ctx)
					results = append(results, result)
				}
				for _, eps := range ctx.State.Epsilons {
					if eps.IsRef {
						continue
					}
					newCtx := n.copyContext(ctx)
					newCtx.State = eps
					newContexts = append(newContexts, newCtx)
				}
				continue
			}
			if ctx.State.IsRef {
				n.handleRef(ctx, text, &newContexts)
				continue
			}
			ch := text[ctx.Pos]
			if targets, ok := ctx.State.Transitions[ch]; ok {
				for _, target := range targets {
					newCtx := n.processTarget(ctx, text, target)

					newContexts = append(newContexts, newCtx)
				}
			}
			for _, eps := range ctx.State.Epsilons {
				newCtx := n.processEpsTarget(ctx, eps, text)
				// Добавляем совпадение, если достигли принимающего состояния
				if newCtx.State.IsAcceptable {
					result := n.buildMatchResult(text, newCtx)
					results = append(results, result)
				}
				newContexts = append(newContexts, newCtx)
			}
		}

		n.sortContextsByProgress(newContexts)
		contexts = newContexts
	}
	return results
}

func (n *Nfa) Accepts(text string) bool {
	result := n.matchAt(text, 0)

	if result != nil && result.Start == 0 && result.End == len(text) {
		return true
	}
	return false
}
