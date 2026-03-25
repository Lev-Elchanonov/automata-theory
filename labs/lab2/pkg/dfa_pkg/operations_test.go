package dfa_test

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
		startExpr: "(((a?b?)...)?|(acb)...)?|((a?)?){2})",
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
