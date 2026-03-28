package test

import (
	regex "lab2/pkg/string_opers_pkg"
	"testing"
)


type SearchTestCase struct {
	testName string
	pattern  string
	text     string
	expected string
	start    int
	end      int
}


type SearchAllTestCase struct {
	testName string
	pattern  string
	text     string
	expected []string
}

type AcceptsTestCase struct {
	testName string
	pattern  string
	text     string
	expected bool
}


// ПРОСТЫЕ ПАТТЕРНЫ
var basicSearchTests = []SearchTestCase{
	{"single_char", "a", "abc", "a", 0, 1},
	{"single_char_middle", "b", "abc", "b", 1, 2},
	{"single_char_end", "c", "abc", "c", 2, 3},
	{"single_char_not_found", "d", "abc", "", -1, -1},
	{"single_char_multiple_times", "d", "abcdddaaad", "d", 3, 4},

	{"word", "hello", "hello world", "hello", 0, 5},
	{"word_middle", "world", "hello world_my_friend", "world", 6, 11},
	{"word_end", "world", "hello world!", "world", 6, 11},
	{"word_not_found", "xyz", "hello world", "", -1, -1},
	{"word_multiple_times", "world", "hello world world hellloooo world", "world", 6, 11},

	{"repeat_char", "aa", "aaa", "aa", 0, 2},
	{"repeat_char_middle", "aa", "baab", "aa", 1, 3},
	{"repeat_char_overlap", "aaa", "aaaa", "aaa", 0, 3},

	{"concat", "ab", "abc", "ab", 0, 2},
	{"concat_middle", "bc", "abc", "bc", 1, 3},
	{"concat_long", "abc", "abcabc", "abc", 0, 3},
	{"concat_long", "abc", "derezhable", "", -1, -1},
}

var basicSearchAllTests = []SearchAllTestCase{
	{"single_char_all", "a", "a b a", []string{"a", "a"}},
	{"single_char_all_consecutive", "a", "aaa", []string{"a", "a", "a"}},
	{"word_all", "a", "a b a c a", []string{"a", "a", "a"}},
	{"two_chars_all", "ab", "abc ab ab abcb acbcbcbfdbae", []string{"ab", "ab", "ab", "ab"}},
	{"no_matches", "xyz", "hello world", []string{}},
}

var basicAcceptsTests = []AcceptsTestCase{
	{"single_char", "a", "a", true},
	{"single_char_wrong", "a", "b", false},
	{"single_char_longer", "a", "aa", false},
	{"word", "hello", "hello", true},
	{"word_longer", "hello", "hello!", false},
	{"empty", "a", "", false},
	{"empty_pattern", "", "", true},
}




// КЛИНИ
var closureSearchTests = []SearchTestCase{
	{"star_empty", "a...", "", "", -1, -1},
	{"star_one", "a...", "a", "a", 0, 1},
	{"star_many", "a...", "aaa", "aaa", 0, 3},
	{"star_in_middle", "a...", "baab", "aa", 1, 3},
	{"star_with_other", "a...b...", "caaababaaaaab", "aaab", 1, 5},
	{"star_greedy", "a...", "aaa", "aaa", 0, 3},

	{"star_after_char", "ab...", "abbb", "abbb", 0, 4},
	{"star_before_char", "a...b", "aaab", "aaab", 0, 4},
	{"star_in_concat", "a...b...c", "aaabbc", "aaabbc", 0, 6},
	{"star_in_concat_wrong", "a...b...c", "aaabbd", "", -1, -1},
}

var closureSearchAllTests = []SearchAllTestCase{
	{"star_all", "a...", "a aa aaa b ccc bb a", []string{"a", "aa", "aaa", "a"}},
	{"star_overlap", "a...", "aaaaaaaaaaaaaaaaaaaaa", []string{"aaaaaaaaaaaaaaaaaaaaa"}},
	{"star_with_delimiters", "a...", "a b a", []string{"a", "a"}},
}

var closureAcceptsTests = []AcceptsTestCase{
	{"star_empty_string", "a...", "", true},  // замыкание принимает пустую строку
	{"star_one", "a...", "a", true},
	{"star_many", "a...", "aaa", true},
	{"star_wrong", "a...", "b", false},
	{"star_with_b", "a...", "aab", false},
}


// ОПЦИОНАЛЬНАЯ
var optionalSearchTests = []SearchTestCase{
	{"optional_present", "a?b", "ab", "ab", 0, 2},
	{"optional_absent", "a?b", "b", "b", 0, 1},
	{"optional_at_start", "a?b", "b ab ab b", "b", 0, 1},
	{"optional_middle", "a?b?c", "ac c", "ac", 0, 2},
	{"optional_both", "a?b?c", "c", "c", 0, 1},
	{"optional_long", "a?b?c?d", "abd abcd", "abd", 0, 3},
}

var optionalSearchAllTests = []SearchAllTestCase{
	{"optional_all", "a?b", "ab b ab ac bc", []string{"ab", "b", "ab", "b"}},
	{"optional_nested", "a?b?c", "c ac bc abc zwefd", []string{"c", "ac", "bc", "abc"}},
}

var optionalAcceptsTests = []AcceptsTestCase{
	{"optional_present", "a?b", "ab", true},
	{"optional_absent", "a?b", "b", true},
	{"optional_both_absent", "a?b?c", "c", true},
	{"optional_wrong", "a?b", "a", false},
	{"optional_extra", "a?b", "abb", false},
}



// UNION
var unionSearchTests = []SearchTestCase{
	{"union_first", "a|b", "abc", "a", 0, 1},
	{"union_second", "a|b", "bac", "b", 0, 1},
	{"union_long", "ab|cd", "abcd", "ab", 0, 2},
	{"union_three", "a|b|c", "cab", "c", 0, 1},
	{"union_complex", "(ab)|(cd)", "cdab", "cd", 0, 2},
	{"union_complex", "y|((ab)|(cd))|z", "cdab z", "cd", 0, 2},
}

var unionSearchAllTests = []SearchAllTestCase{
	{"union_all", "a|b", "a b a acb", []string{"a", "b", "a", "a", "b"}},
	{"union_overlap", "a|aa", "aaa", []string{"aa", "a"}}, // самое длинное
	{"union_multiple", "ab|bc|cd", "gjdjfdmabcdwqwegfw", []string{"ab", "cd"}},
}

var unionAcceptsTests = []AcceptsTestCase{
	{"union_first", "a|b", "a", true},
	{"union_second", "a|b", "b", true},
	{"union_wrong", "a|b", "c", false},
	{"union_long", "ab|cd", "ab", true},
	{"union_long_second", "ab|cd", "cd", true},
}



// ПОВТОРЕНИЕ
var repeatSearchTests = []SearchTestCase{
	{"repeat_2", "a{2}", "aab", "aa", 0, 2},
	{"repeat_2_middle", "a{2}", "baab", "aa", 1, 3},
	{"repeat_3", "a{3}", "aaab", "aaa", 0, 3},
	{"repeat_3_long", "a{3}", "aaaa", "aaa", 0, 3},
	{"repeat_zero", "a{0}", "aaaaa", "", -1, -1},
	{"repeat_concat", "a{2}b{2}", "aab aabb", "aabb", 4, 8},
	{"repeat_inside", "(ab){2}", "abab abab", "abab", 0, 4},
}

var repeatSearchAllTests = []SearchAllTestCase{
	{"repeat_all", "a{2}", "aa aaa aa", []string{"aa", "aa", "aa"}},
	{"repeat_overlap", "a{2}", "aaaaa", []string{"aa", "aa"}},
	{"repeat_group", "(ab){2}", "abab abab", []string{"abab", "abab"}},
}

var repeatAcceptsTests = []AcceptsTestCase{
	{"repeat_2", "a{2}", "aa", true},
	{"repeat_2_long", "a{2}", "aaa", false},
	{"repeat_2_short", "a{2}", "a", false},
	{"repeat_zero", "a{0}", "", true},
	{"repeat_concat", "a{2}b{2}", "aabb", true},
	{"repeat_group", "(ab){2}", "abab", true},
	{"repeat_group", "(ab){3}", "abab", false},
}



// ВСЯКИЕ ИНТЕРЕСНЫЕ СЛУЧАИ
var edgeSearchTests = []SearchTestCase{
	{"empty_string", "", "", "", -1, -1},
	{"empty_pattern", "", "abc", "", -1, -1},
	{"long_string", "a", "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa", "a", 0, 1},
	{"pattern_longer_than_text", "abc", "ab", "", -1, -1},
	{"pattern_at_boundary", "a", "a", "a", 0, 1},
	{"pattern_at_end", "c", "abc", "c", 2, 3},
}

var edgeSearchAllTests = []SearchAllTestCase{
	{"empty_string", "a", "", []string{}},
	{"long_string", "a...", "aaaaaaaa aa", []string{"aaaaaaaa", "aa"}},
	{"no_overlap", "aa", "aaaaa", []string{"aa", "aa"}},
}

var edgeAcceptsTests = []AcceptsTestCase{
	{"empty_string", "a...", "", true},
	{"empty_pattern", "", "abc", false},
	{"long_string", "a...", "aaaaaaaa", true},
}




// УСЛОЖЕННЫЕ ПАТТЕРНЫ
var complexSearchTests = []SearchTestCase{
	{"star_union", "(a|b)...", "abc", "ab", 0, 2},
	{"union_star", "a...|b...", "aaa", "aaa", 0, 3},


	{"repeat_optional", "a{2}?b", "aab", "aab", 0, 3},
	{"optional_repeat", "a?{2}b", "ab", "ab", 0, 2},
	{"repeat_optional_2", "a{2}?b", "ab", "b", 1, 2},


	{"nested_star", "((a...)...)", "aaaa", "aaaa", 0, 4},
	{"nested_optional", "(a?)...", "aaa", "aaa", 0, 3},


	{"complex_concat", "a...b...c", "aaabbbbc", "aaabbbbc", 0, 8},
	{"complex_union", "(ab)|(cd)|(ef)", "cdef", "cd", 0, 2},


	{"deep_parens", "((a|b)...)", "ababa", "ababa", 0, 5},
	{"deep_nested", "((a...)...)...", "aaaa", "aaaa", 0, 4},

	{"difficult_test_1", "(a...)?((c...)?|(d{3})...)", "ba", "a", 1, 2},
	{"difficult_test_2", "(a...)?((c...)?|(d{3})...)", "b", "", -1, -1},
	{"difficult_test_3", "(a...)?((c...)?|(d{3})...)", "ccc", "ccc", 0, 3},
	{"difficult_test_4", "(a...)?((c...)?|(d{3})...)", "addddddc", "adddddd", 0, 7},

}

var complexSearchAllTests = []SearchAllTestCase{
	{"complex_union_all", "(ab)|(cd)", "ab cd ab", []string{"ab", "cd", "ab"}},
	{"complex_star_all", "(a|b)...", "a b ab", []string{"a", "b", "ab"}},
	{"nested_star_all", "(a...)...", "a aa aaa", []string{"a", "aa", "aaa"}},

	{"difficult_test", "(a...)?((c...)?|(d{3})...)", "ba ccc aaacfccdddddd", []string{"a", "ccc", "aaac", "cc", "dddddd"}},
}

var complexAcceptsTests = []AcceptsTestCase{
	{"complex_star", "(a|b)...", "ababa", true},
	{"complex_nested", "(a...)...", "aaaa", true},
	{"complex_union", "ab|cd|ef", "cd", true},
	{"complex_wrong", "a...b...c", "aabbcс", false},

	{"difficult_test_1", "(a...)?((c...)?|(d{3})...)", "aaaaaaccccccccf", false},
	{"difficult_test_2", "(a...)?((c...)?|(d{3})...)", "aaaaaaacccccccccc", true},
	{"difficult_test_3", "(a...)?((c...)?|(d{3})...)", "ddddddddd", true},
	{"difficult_test_3", "(a...)?((c...)?|(d{3})...)", "dd", false},
}



// ПРОВЕРКА ЖАДНОСТИ АЛГОРИТМОВ
var greedySearchTests = []SearchTestCase{
	{"greedy_star", "a...", "aaa", "aaa", 0, 3},
	{"greedy_star_with_suffix", "a...b", "aaab", "aaab", 0, 4},
	{"greedy_union", "a|aa|b", "aaa", "aa", 0, 2},
	{"greedy_optional", "a?aa", "aaa", "aaa", 0, 3},
	{"greedy_repeat", "a{0}|a{4}|a{2}|a{3}", "aaaaaaaaaaaa", "aaaa", 0, 4},
}

var greedySearchAllTests = []SearchAllTestCase{
	{"greedy_all", "a...", "a aa aaa", []string{"a", "aa", "aaa"}},
	{"greedy_union_all_1", "a|aa", "aaa", []string{"aa", "a"}},
	{"greedy_union_all_2", "a|aa", "aaaa", []string{"aa", "aa"}},
	{"greedy_union_all_3", "a|aa", "aaaaa", []string{"aa", "aa", "a"}},
}



// ЦИФРЫ + БУКВЫ
var alphabetSearchTests = []SearchTestCase{
	{"digits", "1|2|3|4", "abc123", "1", 3, 4},
	{"letters", "a|b|c|d", "123abc", "a", 3, 4},
	{"mixed", "a|b|c", "xyzabc", "a", 3, 4},
	{"special_chars", "%%%", "hello%world", "%", 5, 6},
}


// ЭКРАНИРОВАНИЕ
var percentAcceptStates = []AcceptsTestCase{
	{"union", "1%|%234", "1|234",  true},
	{"klini", "a%.%%.%%.%bc", "a...bc", true},
	{"figured_and_circled", "%(%abc%{%3%}%-%)%", "(abc{3}-)", true},
	{"special_chars", "%%%", "%", true},
}

func runSearchTests(t *testing.T, tests []SearchTestCase) {
	for _, tt := range tests {
		t.Run(tt.testName, func(t *testing.T) {

			result, _ := regex.Search(tt.pattern, tt.text)

			if tt.expected == "" {
				if result != nil {
					t.Errorf("expected no match, got '%s' at [%d:%d]", result.Text, result.Start, result.End)
				}
				return
			}

			if result == nil {
				t.Fatalf("expected match '%s', got nil", tt.expected)
			}

			if result.Text != tt.expected {
				t.Errorf("expected text '%s', got '%s'", tt.expected, result.Text)
			}
			if result.Start != tt.start {
				t.Errorf("expected start %d, got %d", tt.start, result.Start)
			}
			if result.End != tt.end {
				t.Errorf("expected end %d, got %d", tt.end, result.End)
			}
		})
	}
}

func runSearchAllTests(t *testing.T, tests []SearchAllTestCase) {
	for _, tt := range tests {
		t.Run(tt.testName, func(t *testing.T) {
			iter, _:= regex.SearchAll(tt.pattern, tt.text)
			results := make([]string, 0)
			for iter.Next() {
				results = append(results, iter.Value().Text)
			}

			if len(results) != len(tt.expected) {
				t.Errorf("expected %d matches, got %d", len(tt.expected), len(results))
			}

			iterOther, _:= regex.SearchAll(tt.pattern, tt.text)
			for i, exp := range tt.expected {
				if i >= len(results) {
					break
				}
				iterOther.Next()
				if results[i] != iter.Index(i).Text || iterOther.Current().Text != results[i] {
					t.Errorf("match %d: expected '%s', got '%s'", i, exp, results[i])
				}
			}
		})
	}
}

func runAcceptsTests(t *testing.T, tests []AcceptsTestCase) {
	for _, tt := range tests {
		t.Run(tt.testName, func(t *testing.T) {
			result := regex.Accepts(tt.pattern, tt.text)
			if result != tt.expected {
				t.Errorf("accepts('%s') = %v, expected %v", tt.text, result, tt.expected)
			}
		})
	}
}




func TestDFASearch(t *testing.T) {
	t.Run("basic", func(t *testing.T) {
		runSearchTests(t, basicSearchTests)
	})
	t.Run("closure", func(t *testing.T) {
		runSearchTests(t, closureSearchTests)
	})
	t.Run("optional", func(t *testing.T) {
		runSearchTests(t, optionalSearchTests)
	})
	t.Run("union", func(t *testing.T) {
		runSearchTests(t, unionSearchTests)
	})
	t.Run("repeat", func(t *testing.T) {
		runSearchTests(t, repeatSearchTests)
	})
	t.Run("edge", func(t *testing.T) {
		runSearchTests(t, edgeSearchTests)
	})
	t.Run("complex", func(t *testing.T) {
		runSearchTests(t, complexSearchTests)
	})
	t.Run("greedy", func(t *testing.T) {
		runSearchTests(t, greedySearchTests)
	})
	t.Run("alphabet", func(t *testing.T) {
		runSearchTests(t, alphabetSearchTests)
	})
}

func TestDFASearchAll(t *testing.T) {
	t.Run("basic", func(t *testing.T) {
		runSearchAllTests(t, basicSearchAllTests)
	})
	t.Run("closure", func(t *testing.T) {
		runSearchAllTests(t, closureSearchAllTests)
	})
	t.Run("optional", func(t *testing.T) {
		runSearchAllTests(t, optionalSearchAllTests)
	})
	t.Run("union", func(t *testing.T) {
		runSearchAllTests(t, unionSearchAllTests)
	})
	t.Run("repeat", func(t *testing.T) {
		runSearchAllTests(t, repeatSearchAllTests)
	})
	t.Run("edge", func(t *testing.T) {
		runSearchAllTests(t, edgeSearchAllTests)
	})
	t.Run("complex", func(t *testing.T) {
		runSearchAllTests(t, complexSearchAllTests)
	})
	t.Run("greedy", func(t *testing.T) {
		runSearchAllTests(t, greedySearchAllTests)
	})
}

func TestDFAAccepts(t *testing.T) {
	t.Run("basic", func(t *testing.T) {
		runAcceptsTests(t, basicAcceptsTests)
	})
	t.Run("closure", func(t *testing.T) {
		runAcceptsTests(t, closureAcceptsTests)
	})
	t.Run("optional", func(t *testing.T) {
		runAcceptsTests(t, optionalAcceptsTests)
	})
	t.Run("union", func(t *testing.T) {
		runAcceptsTests(t, unionAcceptsTests)
	})
	t.Run("repeat", func(t *testing.T) {
		runAcceptsTests(t, repeatAcceptsTests)
	})
	t.Run("edge", func(t *testing.T) {
		runAcceptsTests(t, edgeAcceptsTests)
	})
	t.Run("complex", func(t *testing.T) {
		runAcceptsTests(t, complexAcceptsTests)
	})
	t.Run("percent", func(t *testing.T) {
		runAcceptsTests(t, percentAcceptStates)
	})
}