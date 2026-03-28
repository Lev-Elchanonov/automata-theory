package test

import (
	dfa "lab2/pkg/dfa_pkg"
	"testing"
)

type TestCase struct {
	startExpr string
}
var SingleCases =  []TestCase{
	{
		startExpr: "abc",
	},
	{
		startExpr: "a...b...c...d...",
	},
	{
		startExpr: "a?b?c?d?f?q?",
	},
	{
		startExpr: "a|bc|d|qw|yui|q",
	},
	{
		startExpr: "a{3}b{0}c{10}",
	},
	{
		startExpr: "r|((a|b)|(c|d)|e|f|g)",
	},
	{
		startExpr: "(a...)...b......((c...)...)...d.........",
	},
	{
		startExpr: "(a?b?)((c?d?)?f?q?)?e?",
	},
	{
		startExpr: "a{3}b{0}c{10}(ab){20}q{0}e{5}{4}",
	},
	{
		startExpr: "||||||||||||",
	},
	{
		startExpr: "((((a...)...)...)...)...",
	},
	{
		startExpr: "(a...b...c...)...",
	},
	{
		startExpr: "((a...)(b...)(c...))...",
	},
	{
		startExpr: "((a|b)...(c|d)...)...",
	},
	{
		startExpr: "((a...)...|(b...)...)...",
	},
	{
		startExpr: "a|b|c|d|e|f|g|h|i|j|k|l|m|n|o|p|q|r|s|t|u|v|w|x|y|z",
	},
	{
		startExpr: "(a|b|c|d|e|f|g|h|i|j|k|l|m|n|o|p|q|r|s|t|u|v|w|x|y|z)...",
	},
	{
		startExpr: "(a...)|(b...)|(c...)|(d...)|(e...)|(f...)",
	},
	{
		startExpr: "((a|b)|(c|d))|((e|f)|(g|h))",
	},
	{
		startExpr: "((a|b)...)|((c|d)...)|((e|f)...)",
	},
	{
		startExpr: "abcdefghijklmnopqrstuvwxyz",
	},
	{
		startExpr: "a...b...c...d...e...f...g...h...i...j...",
	},
	{
		startExpr: "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa",
	},
	{
		startExpr: "(a)(b)(c)(d)(e)(f)(g)(h)(i)(j)(k)(l)(m)",
	},
	{
		startExpr: "((a)(b)(c))((d)(e)(f))((g)(h)(i))",
	},
	{
		startExpr: "((a?b?c?)?(d?e?f?)?)?",
	},
	{
		startExpr: "((((a?)?)?)?)?",
	},
}

var MultipleCases =  []TestCase{
	{
		startExpr: "(((a?b?)...)?|(acb)...)?|((a?)?){2}",
	},
	{
		startExpr: "(a...)?...{3}",
	},
	{
		startExpr: "a?{3}(t...{3}{10})???",
	},
	{
		startExpr: "a%|%%?%%.%%.%%.%e%{%3%}%",
	},
	{
		startExpr: "(a?b?)...|a...b...c...(a?b?)b?b?a?...",
	},
	{
		startExpr: "((a...)?...){3}",
	},
	{
		startExpr: "((a?b?)...){2}(c...){3}",
	},
	{
		startExpr: "(a...)?...{3}(b...){2}?",
	},
	{
		startExpr: "((a...)...)?{3}",
	},
	{
		startExpr: "a?{3}(b...{2})?{5}",
	},
	{
		startExpr: "(((a?b?)...)?c...){2}",
	},
	{
		startExpr: "(a|b)...(c|d)...{2}",
	},
	{
		startExpr: "((a|b)...){2}|(c|d)...{3}",
	},
	{
		startExpr: "(a|b|c)...{3}(d|e|f)?...",
	},
	{
		startExpr: "((a|b)...(c|d)...){2}?",
	},
	{
		startExpr: "(a|b|c|d)...(e|f|g|h)...{2}(i|j)...",
	},
	{
		startExpr: "((((a?b?)...)?|(acb)...)?|((a?)?){2})",
	},
	{
		startExpr: "(((((a...)...)...)...)...)",
	},
	{
		startExpr: "((a?b?c?)?(d?e?f?)?)?(g?h?i?)?",
	},
	{
		startExpr: "((a...)?(b...)?(c...)?)...",
	},
	{
		startExpr: "((a...|b...)?(c...|d...)?)...",
	},
	{
		startExpr: "a?{2}b?{3}c?{4}",
	},
	{
		startExpr: "a{2}?b{3}?c{4}?",
	},
	{
		startExpr: "(a{2}b{3})?{2}",
	},
	{
		startExpr: "a?{3}(t...{3}{10})???",
	},
	{
		startExpr: "a%|%b%?%c%.%d%(%e%)%%{%f%}%",
	},
	{
		startExpr: "%(%a%|%b%|%c%)%...",
	},
	{
		startExpr: "a%?%b%*%c%+%",
	},
	{
		startExpr: "((a%?%b%?%)...)?",
	},
	{
		startExpr: "a%|%%?%%.%%.%%.%e%{%3%}%",
	},
	{
		startExpr: "(%(%a%|%b%)%)...",
	},
}





func runTests(t *testing.T, testCases []TestCase, testFunc func(*testing.T, TestCase)) {
	for _, tc := range testCases {
		t.Run(tc.startExpr, func(t *testing.T) {
			testFunc(t, tc)
		})
	}
}

// KPATH
func TestKpath(t *testing.T) {
	testFunc := func(t *testing.T, tc TestCase) {
		df, _, err := dfa.BuildDfa(tc.startExpr)
		if err != nil {
			t.Fatalf("failed to build dfa: %v", err)
		}
		resultExpr, err := dfa.BuildRegexFromDFA(df)
		if err != nil {
			t.Fatalf("failed to build regex: %v", err)
		}
		otherDfa, _, err := dfa.BuildDfa(resultExpr)
		if err != nil {
			t.Fatalf("failed to build dfa: %v", err)
		}
		if !dfa.AreEquivalent(df, otherDfa) {
			t.Fatalf("dfa are not equivalent")
		}
	}

	t.Run("simple", func(t *testing.T) {
		runTests(t, SingleCases, testFunc)
	})

	t.Run("multiple", func(t *testing.T) {
		runTests(t, MultipleCases, testFunc)
	})
}


// REVERSE
func TestReverse(t *testing.T) {
	testFunc := func(t *testing.T, tc TestCase) {
		df, _, err := dfa.BuildDfa(tc.startExpr)
		if err != nil {
			t.Fatalf("failed to build dfa: %v", err)
		}
		reversed := df.Reverse()
		if err != nil {
			t.Fatalf("failed to build regex: %v", err)
		}
		result := reversed.Reverse()
		if err != nil {
			t.Fatalf("failed to build dfa: %v", err)
		}
		if dfa.AreEquivalent(df, result) {
			return
		}
		t.Fatalf("dfa are not equivalent")
	}

	t.Run("simple", func(t *testing.T) {
		runTests(t, SingleCases, testFunc)
	})

	t.Run("multiple", func(t *testing.T) {
		runTests(t, MultipleCases, testFunc)
	})
}


// INVERT
func TestInvert(t *testing.T) {
	testFunc := func(t *testing.T, tc TestCase) {
		df, _, err := dfa.BuildDfa(tc.startExpr)
		if err != nil {
			t.Fatalf("failed to build dfa: %v", err)
		}
		inverted := df.Invert()
		if err != nil {
			t.Fatalf("failed to build regex: %v", err)
		}
		result := inverted.Invert()
		if err != nil {
			t.Fatalf("failed to build dfa: %v", err)
		}
		if dfa.AreEquivalent(df, result) {
			return
		}
		t.Fatalf("dfa are not equivalent")
	}

	t.Run("simple", func(t *testing.T) {
		runTests(t, SingleCases, testFunc)
	})

	t.Run("multiple", func(t *testing.T) {
		runTests(t, MultipleCases, testFunc)
	})
}



func TestDifference(t *testing.T) {
	// Тестовые случаи для разности автоматов
	differenceCases := []struct {
		name     string
		exprA    string
		exprB    string
		expected string // ожидаемое регулярное выражение для разности
		testStrings []string // строки для проверки
		expectedMatch []bool // должна ли строка приниматься разностью
	}{
		{
			name:     "A = a*, B = a* -> empty",
			exprA:    "a...",
			exprB:    "a...",
			expected: "",
			testStrings: []string{"", "a", "aa", "aaa", "b"},
			expectedMatch: []bool{false, false, false, false, false},
		},
		{
			name:     "A = a..., B = b... -> a...",
			exprA:    "a...",
			exprB:    "b...",
			expected: "aa...",
			testStrings: []string{"", "a", "aa", "b", "bb", "ab"},
			expectedMatch: []bool{false, true, true, false, false, false},
		},
		{
			name:     "A = a|b, B = a -> b",
			exprA:    "a|b",
			exprB:    "a",
			expected: "b",
			testStrings: []string{"a", "b", "c", "ab", ""},
			expectedMatch: []bool{false, true, false, false, false},
		},
		{
			name:     "A = ab|a, B = a -> ab",
			exprA:    "ab|a",
			exprB:    "a",
			expected: "ab", // ab не начинается с a? Нет, ab не принимается B, так что разность = ab
			testStrings: []string{"a", "ab", "b", "aba"},
			expectedMatch: []bool{false, true, false, false},
		},
		{
			name:     "A = a{3}, B = a{2} -> aaa",
			exprA:    "a{3}",
			exprB:    "a{2}",
			expected: "a{3}",
			testStrings: []string{"", "a", "aa", "aaa", "aaaa"},
			expectedMatch: []bool{false, false, false, true, false},
		},
		{
			name:     "A = a?b, B = b -> ab",
			exprA:    "a?b",
			exprB:    "b",
			expected: "ab",
			testStrings: []string{"b", "ab", "a", "bb"},
			expectedMatch: []bool{false, true, false, false},
		},
		{
			name:     "A = (a{3}|b{3}), B = a... -> b{3}",
			exprA:    "(a{3}|b{3})",
			exprB:    "a...",
			expected: "b{3}",
			testStrings: []string{"", "a", "bbb", "aa", "ab", "bb", "b"},
			expectedMatch: []bool{false, false, true, false, false, false, false},
		},
		{
			name:     "A = a...b..., B = a... -> b...",
			exprA:    "a...b...",
			exprB:    "a...",
			expected: "a...bb...",
			testStrings: []string{"", "a", "b", "ab", "aab", "abb", "ba"},
			expectedMatch: []bool{false, false, true, true, true, true, false},
		},
		{
			name:     "A = (abc)..., B = abc -> (abc)...",
			exprA:    "(abc)...",
			exprB:    "abc",
			expected: "abcabc(abc)...|",
			testStrings: []string{"", "abc", "abcabc", "ab", "abcabcabc"},
			expectedMatch: []bool{true, false, true, false, true},
		},
		{
			name:     "A = a...b?, B = a... -> a...b",
			exprA:    "a...b?",
			exprB:    "a...",
			expected: "a...b",
			testStrings: []string{"", "a", "b", "ab", "aab", "abb", "aaab"},
			expectedMatch: []bool{false, false, true, true, true, false, true},
		},
		{
			name:     "A = a|b|c, B = a|b -> c",
			exprA:    "a|b|c",
			exprB:    "a|b",
			expected: "c",
			testStrings: []string{"a", "b", "c", "d", "ab"},
			expectedMatch: []bool{false, false, true, false, false},
		},
		{
			name:     "A = (a...|b...)c, B = a...c -> (b)...c",
			exprA:    "(a...|b...)c",
			exprB:    "a...c",
			expected: "bb...c",
			testStrings: []string{"c", "ac", "bc", "aac", "bbbbc", ""},
			expectedMatch: []bool{false, false, true, false, true, false},
		},
	}

	accepts := func(d *dfa.Dfa, s string) bool {
		current := d.StartState
		for i := 0; i < len(s); i++ {
			ch := s[i]
			if next, ok := current.Transitions[ch]; ok {
				current = next
			} else {
				current = d.ErrorState
			}
		}
		return current.IsAcceptable
	}

	for _, tc := range differenceCases {
		t.Run(tc.name, func(t *testing.T) {
			dfaA, _, err := dfa.BuildDfa(tc.exprA)
			if err != nil {
				t.Fatalf("failed to build first dfa for '%s': %v", tc.exprA, err)
			}
			dfaB, _, err := dfa.BuildDfa(tc.exprB)
			if err != nil {
				t.Fatalf("failed to build second dfa for '%s': %v", tc.exprB, err)
			}
			diff := dfa.Difference(dfaA, dfaB)
			if diff == nil {
				t.Fatalf("Difference returned nil")
			}

			for i, testStr := range tc.testStrings {
				result := accepts(diff, testStr)
				if result != tc.expectedMatch[i] {
					t.Errorf("For string '%s': expected %v, got %v",
						testStr, tc.expectedMatch[i], result)
				}
			}
			if tc.expected != "" {
				expectedDfa, _, err := dfa.BuildDfa(tc.expected)
				if err != nil {
					t.Fatalf("failed to build expected dfa for '%s': %v", tc.expected, err)
				}

				if !dfa.AreEquivalent(diff, expectedDfa) {
					t.Errorf("Difference result is not equivalent to expected regex '%s'", tc.expected)
				}
			}
		})
	}
}