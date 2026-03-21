package nfa_test

import (
	"lab2/pkg/nfa_pkg"
	"lab2/pkg/regex_pkg"
	"testing"
)


func buildTestNFA(t *testing.T, pattern string) *nfa.Nfa {
	tree, err := regex_pkg.BuildSyntaxTree(pattern)
	if err != nil {
		t.Fatalf("Error building syntax tree for '%s': %v", pattern, err)
	}
	nfaAutomaton := nfa.BuildNfaFromTree(tree)
	if nfaAutomaton == nil {
		t.Fatalf("Error building NFA for '%s'", pattern)
	}
	return nfaAutomaton
}

// TestSearch проверяет поиск первого вхождения
func TestSearch(t *testing.T) {
	tests := []struct {
		name     string
		pattern  string
		text     string
		expected *nfa.MatchResult
	}{
		{
			name:    "simple_word",
			pattern: "hello",
			text:    "hello world",
			expected: &nfa.MatchResult{
				Start:  0,
				End:    5,
				Text:   "hello",
				Groups: map[string]string{},
			},
		},
		{
			name:    "word_in_middle",
			pattern: "hello",
			text:    "say hello to world",
			expected: &nfa.MatchResult{
				Start:  4,
				End:    9,
				Text:   "hello",
				Groups: map[string]string{},
			},
		},
		{
			name:    "word_in_end",
			pattern: "hello",
			text:    "my world cant say hello",
			expected: &nfa.MatchResult{
				Start:  18,
				End:    23,
				Text:   "hello",
				Groups: map[string]string{},
			},
		},
		{
			name:     "no_matches",
			pattern:  "mephi",
			text:     "i can say hello world",
			expected: nil,
		},
	}

	for _, test := range tests {
		t.Run(test.name, func(t *testing.T) {
			nfaAutomaton := buildTestNFA(t, test.pattern)
			result := nfaAutomaton.Search(test.text)

			if test.expected == nil {
				if result != nil {
					t.Errorf("Expected nil, received %v", result)
				}
				return
			}

			if result == nil {
				t.Fatal("Expected match, received nil")
			}

			if result.Start != test.expected.Start {
				t.Errorf("Start: expected %d, received %d", test.expected.Start, result.Start)
			}
			if result.End != test.expected.End {
				t.Errorf("End: expected %d, received %d", test.expected.End, result.End)
			}
			if result.Text != test.expected.Text {
				t.Errorf("Text: expected %s, received %s", test.expected.Text, result.Text)
			}
		})
	}
}

// ТЕСТЫ ДЛЯ ГРУПП ЗАХВАТА
func TestGroups(t *testing.T) {
	tests := []struct {
		name     string
		pattern  string
		text     string
		expected map[string]string
	}{
		{
			name:    "single_group",
			pattern: "hello (<world>ww...oo...rr...ll...dd...)",
			text:    "hello wwwoooorllldddddd",
			expected: map[string]string{
				"world": "wwwoooorllldddddd",
			},
		},
		{
			name:    "multiple_groups",
			pattern: "(<first>a...) (<second>19...8?)",
			text:    "aaaaaaaaaaaaaaaaa 199999999999",
			expected: map[string]string{
				"first":  "aaaaaaaaaaaaaaaaa",
				"second": "199999999999",
			},
		},
		{
			name:    "email_pattern",
			pattern: "(<username>user|l{3}e{5}v{2})@(<domain>mephi).(<tld>com|ru)",
			text:    "user@mephi.com",
			expected: map[string]string{
				"username": "user",
				"domain":   "mephi",
				"tld":      "com",
			},
		},
		{
			name:    "email_pattern_2",
			pattern: "(<username>user|l{3}e{5}v{2})@(<domain>mephi).(<tld>com|ru)",
			text:    "llleeeeevv@mephi.ru",
			expected: map[string]string{
				"username": "llleeeeevv",
				"domain":   "mephi",
				"tld":      "ru",
			},
		},
		{
			name:    "group_with_closure",
			pattern: "(<digits>(0|1|2|3|4|5|6|7|8|9)...)",
			text:    "12345123141354135135143213134523523452321341241352452352352452652",
			expected: map[string]string{
				"digits": "12345123141354135135143213134523523452321341241352452352352452652",
			},
		},
		{
			name:    "group_with_question",
			pattern: "(<optional>a?)b",
			text:    "b",
			expected: map[string]string{
				"optional": "",
			},
		},
	}

	for _, test := range tests {
		t.Run(test.name, func(t *testing.T) {
			Tree, err := regex_pkg.BuildSyntaxTree(test.pattern)
			if err != nil{
				t.Fatalf("Error building syntax tree: %v", err)
			}
			nfa2 := nfa.BuildNfaFromTree(Tree)
			if nfa2 == nil {
				t.Fatalf("Error building NFA")
			}

			result := nfa2.Search(test.text)

			if result == nil {
				t.Fatal("Expected match, received nil")
			}

			for name, expected := range test.expected {
				actual := result.Group(name)
				if actual != expected {
					t.Errorf("Group %s: expected %s, received %s", name, expected, actual)
				}
			}
		})
	}
}



// TestReferences проверяет ссылки на группы (backreferences)
func TestReferences(t *testing.T) {
	tests := []struct {
		name     string
		pattern  string
		text     string
		expected bool
		groups   map[string]string
	}{
		{
			name:    "simple_ref_success",
			pattern: "(<abc>r...)-<abc>",
			text:    "rrr-rrr",
			expected: true,
			groups: map[string]string{
				"abc": "rrr",
			},
		},
		{
			name:    "simple_ref_failure",
			pattern: "(<abc>r...)-<abc>",
			text:    "rrr-xxx",
			expected: false,
			groups:   nil,
		},
		{
			name:    "ref_with_closure",
			pattern: "(<tag>a...b...c...)-<tag>",
			text:    "abc-abc",
			expected: true,
			groups: map[string]string{
				"tag": "abc",
			},
		},
		{
			name:    "multiple_refs",
			pattern: "(<first>a...)-<first>-(<second>b...)-<second>",
			text:    "aaa-aaa-bbb-bbb",
			expected: true,
			groups: map[string]string{
				"first":  "aaa",
				"second": "bbb",
			},
		},
		{
			name:    "ref_with_question",
			pattern: "(<optional>a?)b-<optional>",
			text:    "b-",
			expected: true,
			groups: map[string]string{
				"optional": "",
			},
		},
		{
			name:    "nested_refs",
			pattern: "(<outer>a(<inner>b)c)-<outer>-<inner>",
			text:    "abc-abc-b",
			expected: true,
			groups: map[string]string{
				"outer": "abc",
				"inner": "b",
			},
		},
	}

	for _, test := range tests {
		t.Run(test.name, func(t *testing.T) {
			nfaAutomaton := buildTestNFA(t, test.pattern)
			result := nfaAutomaton.Search(test.text)

			if test.expected {
				if result == nil {
					t.Fatal("Expected match, received nil")
				}
				for name, expected := range test.groups {
					actual := result.Group(name)
					if actual != expected {
						t.Errorf("Group %s: expected '%s', received '%s'", name, expected, actual)
					}
				}
			} else {
				if result != nil {
					t.Errorf("Expected no match, received '%s'", result.Text)
				}
			}
		})
	}
}

// TestSearchFrom проверяет поиск с указанной позиции
func TestSearchFrom(t *testing.T) {
	tests := []struct {
		name     string
		pattern  string
		text     string
		startPos int
		expected string
	}{
		{
			name:     "search_from_beginning",
			pattern:  "foo",
			text:     "foo bar foo",
			startPos: 0,
			expected: "foo",
		},
		{
			name:     "search_after_first_match",
			pattern:  "foo",
			text:     "foo bar foo",
			startPos: 4,
			expected: "foo",
		},
		{
			name:     "search_after_last_match",
			pattern:  "foo",
			text:     "foo bar foo",
			startPos: 12,
			expected: "",
		},
		{
			name:     "search_with_refs",
			pattern:  "(<abc>r...)-<abc>",
			text:     "rrr-rrr xxx-xxx",
			startPos: 0,
			expected: "rrr-rrr",
		},
	}

	for _, test := range tests {
		t.Run(test.name, func(t *testing.T) {
			nfaAutomaton := buildTestNFA(t, test.pattern)
			result := nfaAutomaton.SearchFrom(test.text, test.startPos)

			if test.expected == "" {
				if result != nil {
					t.Errorf("Expected nil, received %v", result)
				}
			} else {
				if result == nil {
					t.Fatal("Expected match, received nil")
				}
				if result.Text != test.expected {
					t.Errorf("Expected '%s', received '%s'", test.expected, result.Text)
				}
			}
		})
	}
}

// TestSearchAll проверяет итератор по всем совпадениям
func TestSearchAll(t *testing.T) {
	tests := []struct {
		name        string
		pattern     string
		text        string
		expectedLen int
		expected    []string
	}{
		{
			name:        "no_matches",
			pattern:     "xyz",
			text:        "hello world",
			expectedLen: 0,
			expected:    []string{},
		},
		{
			name:        "one_match",
			pattern:     "hello",
			text:        "hello world",
			expectedLen: 1,
			expected:    []string{"hello"},
		},
		{
			name:        "multiple_matches",
			pattern:     "a",
			text:        "a b a c a",
			expectedLen: 3,
			expected:    []string{"a", "a", "a"},
		},
		{
			name:        "matches_with_groups",
			pattern:     "(<word>ww...)",
			text:        "w wwwww www wwwwww",
			expectedLen: 4,
			expected:    []string{"w", "wwwww", "www", "wwwwww"},
		},
		{
			name:        "matches_with_refs",
			pattern:     "(<abc>r...|a...)-<abc>",
			text:        "rrr-rrr xxx-xxx aaa-aaa",
			expectedLen: 2,
			expected:    []string{"rrr-rrr", "aaa-aaa"},
		},
	}

	for _, test := range tests {
		t.Run(test.name, func(t *testing.T) {
			nfaAutomaton := buildTestNFA(t, test.pattern)
			iter := nfaAutomaton.SearchAll(test.text)

			matches := make([]string, 0)
			for iter.Next() {
				m := iter.Value()
				matches = append(matches, m.Text)
			}

			if len(matches) != test.expectedLen {
				t.Errorf("Match count: expected %d, received %d", test.expectedLen, len(matches))
			}

			for i, expected := range test.expected {
				if i >= len(matches) {
					break
				}
				if matches[i] != expected {
					t.Errorf("Match %d: expected '%s', received '%s'", i, expected, matches[i])
				}
			}
		})
	}
}

// TestIteratorIndex проверяет доступ по индексу через итератор
func TestIteratorIndex(t *testing.T) {
	pattern := "(<word>[a-z]+)"
	text := "hello world foo bar"

	nfaAutomaton := buildTestNFA(t, pattern)
	iter := nfaAutomaton.SearchAll(text)

	// Проверяем доступ по индексам
	first := iter.Index(0)
	if first == nil {
		t.Fatal("First match not found")
	}
	if first.Text != "hello" {
		t.Errorf("First match: expected 'hello', received '%s'", first.Text)
	}
	if first.Group("word") != "hello" {
		t.Errorf("First group: expected 'hello', received '%s'", first.Group("word"))
	}

	second := iter.Index(1)
	if second == nil {
		t.Fatal("Second match not found")
	}
	if second.Text != "world" {
		t.Errorf("Second match: expected 'world', received '%s'", second.Text)
	}

	third := iter.Index(2)
	if third == nil {
		t.Fatal("Third match not found")
	}
	if third.Text != "foo" {
		t.Errorf("Third match: expected 'foo', received '%s'", third.Text)
	}

	fourth := iter.Index(3)
	if fourth == nil {
		t.Fatal("Fourth match not found")
	}
	if fourth.Text != "bar" {
		t.Errorf("Fourth match: expected 'bar', received '%s'", fourth.Text)
	}

	fifth := iter.Index(4)
	if fifth != nil {
		t.Error("Fifth match should not exist")
	}

	// Проверяем отрицательный индекс
	negative := iter.Index(-1)
	if negative != nil {
		t.Error("Negative index should return nil")
	}
}

// TestMatchResultMethods проверяет методы MatchResult
func TestMatchResultMethods(t *testing.T) {
	pattern := "(<username>[a-z]+)@(<domain>[a-z]+).(<tld>[a-z]+)"
	text := "user@example.com"

	nfaAutomaton := buildTestNFA(t, pattern)
	result := nfaAutomaton.Search(text)

	if result == nil {
		t.Fatal("Expected match, received nil")
	}

	// Проверяем GroupNames
	names := result.GroupNames()
	expectedNames := []string{"domain", "tld", "username"}
	if len(names) != len(expectedNames) {
		t.Errorf("GroupNames count: expected %d, received %d", len(expectedNames), len(names))
	}

	// Проверяем HasGroup
	if !result.HasGroup("username") {
		t.Error("HasGroup should return true for 'username'")
	}
	if result.HasGroup("nonexistent") {
		t.Error("HasGroup should return false for nonexistent group")
	}

	// Проверяем Group
	if result.Group("username") != "user" {
		t.Errorf("Group 'username': expected 'user', received '%s'", result.Group("username"))
	}
	if result.Group("domain") != "example" {
		t.Errorf("Group 'domain': expected 'example', received '%s'", result.Group("domain"))
	}
	if result.Group("tld") != "com" {
		t.Errorf("Group 'tld': expected 'com', received '%s'", result.Group("tld"))
	}
}

// TestEdgeCases проверяет граничные случаи
func TestEdgeCases(t *testing.T) {
	tests := []struct {
		name     string
		pattern  string
		text     string
		expected bool
	}{
		{
			name:     "empty_string",
			pattern:  "a",
			text:     "",
			expected: false,
		},
		{
			name:     "empty_pattern",
			pattern:  "",
			text:     "hello",
			expected: false,
		},
		{
			name:     "long_string",
			pattern:  "a",
			text:     "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa",
			expected: true,
		},
		{
			name:     "ref_with_empty_group",
			pattern:  "(<empty>a?)b-<empty>",
			text:     "b-",
			expected: true,
		},
	}

	for _, test := range tests {
		t.Run(test.name, func(t *testing.T) {
			if test.pattern == "" {
				return
			}
			nfaAutomaton := buildTestNFA(t, test.pattern)
			result := nfaAutomaton.Search(test.text)

			if test.expected && result == nil {
				t.Error("Expected match, received nil")
			}
			if !test.expected && result != nil {
				t.Errorf("Expected no match, received '%s'", result.Text)
			}
		})
	}
}

// TestGreedyMatch проверяет жадность поиска
func TestGreedyMatch(t *testing.T) {
	tests := []struct {
		name        string
		pattern     string
		text        string
		expected    string
		expectedLen int
	}{
		{
			name:        "greedy_closure",
			pattern:     "a...",
			text:        "aaa",
			expected:    "aaa",
			expectedLen: 3,
		},
		{
			name:        "greedy_with_ref",
			pattern:     "(<abc>r...)-<abc>",
			text:        "rrr-rrr",
			expected:    "rrr-rrr",
			expectedLen: 7,
		},
		{
			name:        "greedy_choice",
			pattern:     "a...|b...",
			text:        "aaaaa",
			expected:    "aaaaa",
			expectedLen: 5,
		},
	}

	for _, test := range tests {
		t.Run(test.name, func(t *testing.T) {
			nfaAutomaton := buildTestNFA(t, test.pattern)
			result := nfaAutomaton.Search(test.text)

			if result == nil {
				t.Fatal("Expected match, received nil")
			}
			if result.Text != test.expected {
				t.Errorf("Expected '%s', received '%s'", test.expected, result.Text)
			}
			if len(result.Text) != test.expectedLen {
				t.Errorf("Length: expected %d, received %d", test.expectedLen, len(result.Text))
			}
		})
	}
}

// BenchmarkSearch тест производительности
func BenchmarkSearch(b *testing.B) {
	pattern := "(<username>user)@(<domain>example).(<tld>org)"
	text := "my email is user@example.com and admin@test.org"

	nfaAutomaton := buildTestNFA(nil, pattern)

	b.ResetTimer()
	for i := 0; i < b.N; i++ {
		nfaAutomaton.Search(text)
	}
}

