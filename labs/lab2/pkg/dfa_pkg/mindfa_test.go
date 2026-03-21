package dfa_test

import (
	dfa "lab2/pkg/dfa_pkg"
	nfa2 "lab2/pkg/nfa_pkg"
	"lab2/pkg/regex_pkg"
	"testing"
)

func TestSearch(t *testing.T){
	tests := []struct{
		name string
		pattern string
		text string
		expected *dfa.MatchResult
	}{
		{
			name: "simple_word",
			pattern: "hello",
			text: "hello world",
			expected: &dfa.MatchResult{
				Start: 0,
				End: 5,
				Text: "hello",
			},
		},
		{
			name: "word_in_middle",
			pattern: "hello",
			text: "say hello to world",
			expected: &dfa.MatchResult{
				Start: 4,
				End: 9,
				Text: "hello",
			},
		},
		{
			name: "word_in_end",
			pattern: "hello",
			text: "my world cant say hello",
			expected: &dfa.MatchResult{
				Start: 18,
				End: 23,
				Text: "hello",
			},
		},
		{
			name: "no_matches",
			pattern: "mephi",
			text: "i can say hello world every time i write tests",
			expected: nil,
		},
	}

	for _, test := range tests {
		t.Run(test.name, func(t *testing.T) {
			minDfa, err := dfa.BuildDfa(test.pattern)
			if err != nil {
				t.Errorf("Error building DFA: %s", err)
			}
			result := minDfa.Search(test.text)


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


// ТЕСТЫ НА ПРОВЕРКУ ВХОЖДЕНИЯ НАЧИНАЯ С КАКОГО ТО СИМВОЛА
func TestSearchFrom(t *testing.T) {
	tests := []struct {
		name     string
		pattern  string
		text     string
		startPos int
		expected *dfa.MatchResult
	}{
		{
			name:     "search_from_beginning",
			pattern:  "foo",
			text:     "foo bar foo",
			startPos: 0,
			expected: &dfa.MatchResult{
				Start:  0,
				End:    3,
				Text:   "foo",
			},
		},
		{
			name:     "search_after_first_match",
			pattern:  "foo",
			text:     "foo bar foo",
			startPos: 4,
			expected: &dfa.MatchResult{
				Start:  8,
				End:    11,
				Text:   "foo",
			},
		},
		{
			name:     "search_after_last_match",
			pattern:  "foo",
			text:     "foo bar foo",
			startPos: 12,
			expected: nil,
		},
		{
			name:     "search_with_overlap",
			pattern:  "aa",
			text:     "aaa",
			startPos: 0,
			expected: &dfa.MatchResult{
				Start:  0,
				End:    2,
				Text:   "aa",
			},
		},
	}

	for _, test := range tests {
		t.Run(test.name, func(t *testing.T) {
			minDfa, err := dfa.BuildDfa(test.pattern)
			if err != nil {
				t.Fatalf("Error building DFA: %v", err)
			}
			result := minDfa.SearchFrom(test.text, test.startPos)

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


// ТЕСТЫ НА ПРОВЕРКУ ВХОЖДЕНИЯ ПАТТЕРНА ВО ВСЕЙ СТРОКЕ В ЦЕЛОМ
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
			name:        "consecutive_matches",
			pattern:     "aa",
			text:        "aaa",
			expectedLen: 1,
			expected:    []string{"aa"},
		},
		{
			name:        "digits",
			pattern:     "0|1|2|3|4|5|6|7|8|9",
			text:        "abc123def456",
			expectedLen: 6,
			expected:    []string{"1", "2", "3", "4", "5", "6"},
		},
	}

	for _, test := range tests {
		t.Run(test.name, func(t *testing.T) {
			minDfa, err := dfa.BuildDfa(test.pattern)
			if err != nil {
				t.Fatalf("Error building DFA: %v", err)
			}
			iter := minDfa.SearchAll(test.text)

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
					t.Errorf("Match %d: expected %s, received %s", i, expected, matches[i])
				}
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
			nfa := nfa2.BuildNfaFromTree(Tree)
			if nfa == nil {
				t.Fatalf("Error building NFA")
			}

			result := nfa.Search(test.text)

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


// ПРОВЕРКА ЭКРАНИРОВАННЫХ СИМВОЛОВ
func TestSearchWithSpecialChars(t *testing.T) {
	tests := []struct {
		name     string
		pattern  string
		text     string
		expected string
	}{
		{
			name:     "escaped_dot",
			pattern:  "a%.%%.%%.%b",
			text:     "a...b",
			expected: "a...b",
		},
		{
			name:     "escaped_star",
			pattern:  "a%?%b",
			text:     "a?b",
			expected: "a?b",
		},
		{
			name:     "escaped_parens",
			pattern:  "%(%hello%)%",
			text:     "(hello)",
			expected: "(hello)",
		},
		{
			name:     "escaped_pipe",
			pattern:  "a%|%b",
			text:     "a|b",
			expected: "a|b",
		},
		{
			name:     "escaped_question",
			pattern:  "a%{%3%}%b",
			text:     "a{3}b",
			expected: "a{3}b",
		},
	}

	for _, test := range tests {
		t.Run(test.name, func(t *testing.T) {
			minDfa, err := dfa.BuildDfa(test.pattern)
			if err != nil {
				t.Fatalf("Error building DFA: %v", err)
			}
			result := minDfa.Search(test.text)

			if result == nil {
				t.Fatal("Expected match, received nil")
			}
			if result.Text != test.expected {
				t.Errorf("Expected %s, received %s", test.expected, result.Text)
			}
		})
	}
}


// ПРОВЕРКА ПРИОРИТЕТА ОПЕРАТОРОВ
func TestOperatorPrecedence(t *testing.T) {
	tests := []struct {
		name     string
		pattern  string
		text     string
		expected string
	}{
		{
			name:     "concat_vs_union_first",
			pattern:  "ab|cd",
			text:     "ab",
			expected: "ab",
		},
		{
			name:     "concat_vs_union_second",
			pattern:  "ab|cd",
			text:     "cd",
			expected: "cd",
		},
		{
			name:     "closure_vs_concat",
			pattern:  "a...b",
			text:     "aaab",
			expected: "aaab",
		},
		{
			name:     "parentheses_override",
			pattern:  "a(b|c)",
			text:     "ac",
			expected: "ac",
		},
		{
			name:     "nested_parentheses",
			pattern:  "(a(b|c))...",
			text:     "abab",
			expected: "abab",
		},
		{
			name:     "nested_parentheses_2",
			pattern:  "(a(b|c))...",
			text:     "abacabacacac",
			expected: "abacabacacac",
		},
	}

	for _, test := range tests {
		t.Run(test.name, func(t *testing.T) {
			minDfa, err := dfa.BuildDfa(test.pattern)
			if err != nil {
				t.Fatalf("Error building DFA: %v", err)
			}
			result := minDfa.Search(test.text)

			if result == nil {
				t.Fatal("Expected match, received nil")
			}
			if result.Text != test.expected {
				t.Errorf("Expected %s, received %s", test.expected, result.Text)
			}
		})
	}
}

// ГРАНИЧНЫЕ СЛУЧАИ
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
			name:     "whitespace",
			pattern:  "  ...",
			text:     "hello         world",
			expected: true,
		},
	}

	for _, test := range tests {
		t.Run(test.name, func(t *testing.T) {
			if test.pattern == "" {
				return
			}
			minDfa, err := dfa.BuildDfa(test.pattern)
			if err != nil {
				t.Fatalf("Error building DFA: %v", err)
			}
			result := minDfa.Search(test.text)

			if test.expected && result == nil {
				t.Error("Expected match, received nil")
			}
			if !test.expected && result != nil {
				t.Errorf("Expected no match, received %s", result.Text)
			}
		})
	}
}



// ТЕСТЫ ПРИНЯТИЯ ВСЕЙ СТРОКИ
func TestAccepts(t *testing.T) {
	tests := []struct {
		name     string
		pattern  string
		text     string
		expected bool
	}{
		{
			name:     "full_match",
			pattern:  "abc",
			text:     "abc",
			expected: true,
		},
		{
			name:     "partial_match",
			pattern:  "abc",
			text:     "abcd",
			expected: false,
		},
		{
			name:     "closure_match",
			pattern:  "a...",
			text:     "aaaaaaaaaaaaaaaaaaa",
			expected: true,
		},
		{
			name:     "empty_string_match",
			pattern:  "a...?",
			text:     "",
			expected: true,
		},
		{
			name:     "union_match_first",
			pattern:  "ab|cd",
			text:     "ab",
			expected: true,
		},
		{
			name:     "union_match_second",
			pattern:  "ab|cd",
			text:     "cd",
			expected: true,
		},
		{
			name:     "hard_string",
			pattern:  "(((a?b?)...)?|(abc)...)?|((a?)?){2}|((b?d?){3}){2}",
			text:     "a",
			expected: true,
		},

	}

	for _, test := range tests {
		t.Run(test.name, func(t *testing.T) {
			minDfa, err := dfa.BuildDfa(test.pattern)
			if err != nil {
				t.Fatalf("Error building DFA: %v", err)
			}
			result := minDfa.Accepts(test.text)

			if result != test.expected {
				t.Errorf("Expected %v, received %v", test.expected, result)
			}
		})
	}
}


// ТЕСТЫ ПРИНЯТИЯ СЛОЖНОЙ РЕГУЛЯРКИ ЦЕЛИКОМ
func TestHardString(t *testing.T) {
	regex := "(((a?b?)...)?|(abc)...)?|((a?)?){2}|((b?d?){3}){2}"
	tests := []struct {
		name     string
		pattern  string
		text     string
		expected bool
	}{
		{
			name:     "hard_string_1",
			pattern:  regex,
			text:     "",
			expected: true,
		},
		{
			name:     "hard_string_2",
			pattern:  regex,
			text:     "aa",
			expected: true,
		},
		{
			name:     "hard_string_3",
			pattern:  regex,
			text:     "aaaa",
			expected: true,
		},
		{
			name:     "hard_string_4",
			pattern:  regex,
			text:     "bbddbbdd",
			expected: true,
		},
		{
			name:     "hard_string_5",
			pattern:  regex,
			text:     "abcabcabc",
			expected: true,
		},
		{
			name:     "hard_string_6",
			pattern:  regex,
			text:     "aaaaaaaaabbbbbbbbbbbb",
			expected: true,
		},
		{
			name:     "hard_string_7",
			pattern:  regex,
			text:     "ababababababababababababa",
			expected: true,
		},
		{
			name:     "hard_string_8",
			pattern:  regex,
			text:     "r",
			expected: false,
		},
		{
			name:     "hard_string_9",
			pattern:  regex,
			text:     "bddbddbddbdd",
			expected: false,
		},
		{
			name:     "hard_string_10",
			pattern:  regex,
			text:     "acacacacacacac",
			expected: false,
		},

	}

	for _, test := range tests {
		t.Run(test.name, func(t *testing.T) {
			minDfa, err := dfa.BuildDfa(test.pattern)
			if err != nil {
				t.Fatalf("Error building DFA: %v", err)
			}
			result := minDfa.Accepts(test.text)

			if result != test.expected {
				t.Errorf("Expected %v, received %v", test.expected, result)
			}
		})
	}
}

// ДОСТУП ПО ИНДЕКСУ ЧЕРЕЗ ИТЕРАТОР
func TestIteratorIndex(t *testing.T) {
	pattern := "hh...ee...lll...o...|world|foo|bar"
	text := "hello world foo bar"

	minDfa, err := dfa.BuildDfa(pattern)
	if err != nil {
		t.Fatalf("Error building DFA: %v", err)
	}

	iter := minDfa.SearchAll(text)

	// Проверяем доступ по индексам
	first := iter.Index(0)
	if first == nil {
		t.Fatal("First match not found")
	}
	if first.Text != "hello" {
		t.Errorf("First match: expected hello, received %s", first.Text)
	}

	second := iter.Index(1)
	if second == nil {
		t.Fatal("Second match not found")
	}
	if second.Text != "world" {
		t.Errorf("Second match: expected world, received %s", second.Text)
	}

	third := iter.Index(2)
	if third == nil {
		t.Fatal("Third match not found")
	}
	if third.Text != "foo" {
		t.Errorf("Third match: expected foo, received %s", third.Text)
	}

	fourth := iter.Index(3)
	if fourth == nil {
		t.Fatal("Fourth match not found")
	}
	if fourth.Text != "bar" {
		t.Errorf("Fourth match: expected bar, received %s", fourth.Text)
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