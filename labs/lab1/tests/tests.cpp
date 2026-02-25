#include <algorithm>
#include <fstream>
#include <gtest/gtest.h>
#include <memory>

#include "regex_version.hpp"

class parser_test : public ::testing::Test {
    public:
        static std::unique_ptr<regex_version> regex_parser_;
};
class parser_valid_test : public parser_test, public ::testing::WithParamInterface<std::string>{};
class parser_invalid_test : public parser_test, public ::testing::WithParamInterface<std::string>{};

std::unique_ptr<regex_version> parser_test::regex_parser_ = std::make_unique<regex_version>();

TEST_P(parser_valid_test, valid_strings) {
    std::string valid_input = GetParam();
    regex_parser_->terminal_parser(valid_input);
    EXPECT_TRUE(regex_parser_->get_parser_state());
}

TEST_P(parser_invalid_test, invalid_strings) {
    std::string invalid_input = GetParam();
    regex_parser_->terminal_parser(invalid_input);
    EXPECT_FALSE(regex_parser_->get_parser_state());
}

void check_attributes_correction(std::vector<std::string>& array_1, std::vector<std::string>& array_2) {
    EXPECT_EQ(array_1.size(), array_2.size());
    for (size_t i = 0; i < array_1.size(); i++)
        EXPECT_EQ(array_1[i], array_2[i]);

}

TEST_F(parser_test, combination_test) {
    regex_parser_->terminal_parser("create exp1 (a1, a2, a3, a4)");
    EXPECT_TRUE(regex_parser_->get_parser_state());
    regex_parser_->terminal_parser("create exp2 (b1, b2, b3, b4)");
    EXPECT_TRUE(regex_parser_->get_parser_state());
    regex_parser_->terminal_parser("create exp3 (a, b, c, d)");
    EXPECT_TRUE(regex_parser_->get_parser_state());
    regex_parser_->terminal_parser("create exp4 (a, b, c, d)");
    EXPECT_TRUE(regex_parser_->get_parser_state());
    regex_parser_->terminal_parser("create exp5 (a, ert)");
    EXPECT_TRUE(regex_parser_->get_parser_state());
    regex_parser_->terminal_parser("create exp6 (abc, a)");
    EXPECT_TRUE(regex_parser_->get_parser_state());
    regex_parser_->terminal_parser("create exp7 (abs)");
    EXPECT_TRUE(regex_parser_->get_parser_state());
    regex_parser_->terminal_parser("create exp8 (abc)");
    EXPECT_TRUE(regex_parser_->get_parser_state());


    regex_parser_->terminal_parser("create exp1_2 as exp1 join exp2");
    EXPECT_TRUE(regex_parser_->get_parser_state());
    regex_parser_->terminal_parser("create exp3_4 as exp3 join exp4");
    EXPECT_TRUE(regex_parser_->get_parser_state());
    regex_parser_->terminal_parser("create exp5_6 as exp5 join exp6");
    EXPECT_TRUE(regex_parser_->get_parser_state());
    regex_parser_->terminal_parser("create exp7_8 as exp7 join exp8");
    EXPECT_TRUE(regex_parser_->get_parser_state());
    regex_parser_->terminal_parser("create exp1_2_copy as exp1 join exp2");
    EXPECT_TRUE(regex_parser_->get_parser_state());
    regex_parser_->terminal_parser("create exp3_4 as exp3 join exp4");
    EXPECT_FALSE(regex_parser_->get_parser_state());

    std::vector<std::string> exp_attributes_1_2 = {"a1", "a2", "a3", "a4", "b1", "b2", "b3", "b4"};
    std::vector<std::string> exp_attributes_3_4 = {"a.exp3", "b.exp3", "c.exp3", "d.exp3", "a.exp4", "b.exp4", "c.exp4", "d.exp4"};
    std::vector<std::string> exp_attributes_5_6 = {"a.exp5", "ert", "abc", "a.exp6"};
    std::vector<std::string> exp_attributes_7_8 = {"abs", "abc"};

    std::vector<std::string> real_attributes_1_2 = regex_parser_->get_parser_info().find("exp1_2")->second;
    std::vector<std::string> real_attributes_3_4 = regex_parser_->get_parser_info().find("exp3_4")->second;
    std::vector<std::string> real_attributes_5_6 = regex_parser_->get_parser_info().find("exp5_6")->second;
    std::vector<std::string> real_attributes_7_8 = regex_parser_->get_parser_info().find("exp7_8")->second;
    std::vector<std::string> real_attributes_1_2_copy = regex_parser_->get_parser_info().find("exp1_2_copy")->second;


    check_attributes_correction(real_attributes_1_2, exp_attributes_1_2);
    check_attributes_correction(real_attributes_3_4, exp_attributes_3_4);
    check_attributes_correction(real_attributes_5_6, exp_attributes_5_6);
    check_attributes_correction(real_attributes_7_8, exp_attributes_7_8);
    check_attributes_correction(real_attributes_1_2_copy, exp_attributes_1_2);






}

TEST_F(parser_test, wrong_combinations) {
    std::vector<std::string> wrong_lines = {
        "creat exp33 as exp7 join exp8",
        "createe exp123 as lalalolo join exp1",
        "create exp1_2 as exp1 join exp2",
        "create exp123 ase exp1 join exp2",
        "create exp33 as expwefwefw join exp2",
        "create exp123 as exp1 join? exp2",
        "create exp123 as exp1 join wefwefwfewfew",
        "create exp123 as exp1 join exp2 _",
        "create exp123 as exp1 join exp1"
    };
    for (auto& line : wrong_lines) {
        regex_parser_->terminal_parser(line);
        EXPECT_FALSE(regex_parser_->get_parser_state());
    }

}


INSTANTIATE_TEST_SUITE_P(
    valid_strings,
    parser_valid_test,
    ::testing::Values(
        "create deracel (wfed, d, werf, g)",
        "create abs123 (a,a1,a2,a3,b4b)",
        "create n (a, d1, t, d2, wf, r2, f2, f2, a, b, c, d, e_, q, t, e)",
        "create n_o_1 (a)",
        "create hallo         (a,b,                   r,d,        q)",
        "create              tutut (a,b,c,sd,      e,   q,  t_)",
        "create                       totot                   (a,            e,               t,          q)",
        "create __ (__, ___, _____)",
        "      create     a     (r,    tr)",
        "create abc(a)"
    )
);

INSTANTIATE_TEST_SUITE_P(
    invalid_strings,
    parser_invalid_test,
    ::testing::Values(
        "lev (1,2,3)",
        "createe __ (fwew)",
        "create 1wfefw (a)",
        "create wfe? (a)",
        "create we@ (a)",
        "create wew- (a)",
        "create wdqwwe+ (a)",
        "create aefwe= (a)",
        "create fe~ (a),"
        "create wfe`wfew (a)",
        "create ef* (a)",
        "create wde! (a)",
        "create wfe# (fwfe)",
        "create ewf$ (a)",
        "create ,, (a)",
        "create somth (ef1,)",
        "create wfe% (A)",
        "create ewf; (a)",
        "create erg: (a)",
        "create wef^ (a)",
        "create wef& (a)",
        "create wef( (a)",
        "create ewfw) (a)",
        "create afew\" (a)",
        "create abs| (a)",
        "create a/efw (a)",
        "create abs[ (a)",
        "create [a (a)",
        "create ollolo (     a,       r,      q,      t,)",
        "create r_r (a,b,c,d,e,a,e,)",
        "create [ (a)",
        "create a] (a)",
        "create pwew{ (a)",
        "create wefw} (a)",
        "create wfef { (a)",
        "createabs (a)",
        "create abs (1a)",
        "create abs (a\"e)",
        "create abs (a, b, c`)",
        "create abs (a~f)",
        "create abs (a!)",
        "create abs (a@)",
        "create ans (a\")",
        "create ",
        "create as (\")",
        "create wf wef, a, f",
        "create bas (a#)",
        "create bas (a№)",
        "create ewf (wf;)",
        "create ewrf (ar$)",
        "create ewf )ewqfw(",
        "create wef (wef%)",
        "create ewfe (ewf^)",
        "create efwf (aerwf:)",
        "create wef (wef?)",
        "create gerg (wef&)",
        "create ewfew (wfe*)",
        "create ewf ()",
        "create ewf (    )",
        "create wefr (ewf()",
        "create wef (wef))",
        "create wer ((()))",
        "create wef (wqdq-)",
        "create gre (wefwf=)",
        "create erwf (wfwferw+)",
        "create wefw (adwed|)",
        "create reg (wef/)",
        "create wefw (wefw)_",
        "create wef (wef)wfe",
        "create wefew> (weef)",
        "create wefw< (wefw)",
        "create wefew (wdf>)",
        "create ewfe (wef<ewf)",
        "create ewf (wfe, a, bv, e, q, ewf>)",
        "create wer (wef  wfew   ewf)",
        "create wert (we.   ewf, ewf)",
        "create wer (ew, fewef, ewfew.  efwewew)",
        "create exp1 (a1, a2, a3, a4)",
        "create exp2 (b1, b2, b3, b4)",
        "create exp3 (a, b, c, d)",
        "create exp4 (a, b, c, d)",
        "create exp5 (a, ert)",
        "create exp6 (abc, a)",
        "create exp7 (abs)",
        "create exp8 (abc)",
        "create exp9 ()"
    )
);


TEST_F(parser_test, file_parsing) {
    auto file_parser = std::make_unique<regex_version>();
    EXPECT_THROW(file_parser->file_parser("fwfew"), std::runtime_error);
    file_parser->file_parser("../init_file.txt");
    std::vector<std::pair<std::string, std::vector<std::string>>> correct_expressions = {
        {"deracel", {"wfed", "d", "werf", "g"}},
        {"abs123", {"a", "a1", "a2", "a3", "b4b"}},
        {"n", {"a", "d1", "t", "d2", "wf", "r2", "f2", "f2", "a", "b", "c", "d", "e_", "q", "t", "e"}},
        {"n_o_1", {"a"}},
        {"hallo", {"a", "b","r", "d","q"}},
        {"tutut", {"a", "b", "c", "sd", "e", "q", "t_"}},
        {"totot", {"a", "e", "t", "q"}},
        {"__", {"__", "___", "_____"}},
        {"a", {"r", "tr"}},
        {"abc", {"a"}},
        {"exp1", {"a1", "a2", "a3", "a4"}},
        {"exp2", {"b1", "b2", "b3", "b4"}},
        {"exp3", {"a", "b", "c", "d"}},
        {"exp4", {"a", "b", "c", "d"}},
        {"exp5", {"a", "ert"}},
        {"exp6", {"abc", "a"}},
        {"exp7", {"abs"}},
        {"exp8", {"abc"}},
        {"exp1_2", {"a1", "a2", "a3", "a4", "b1", "b2", "b3", "b4"}},
        {"exp3_4", {"a.exp3", "b.exp3", "c.exp3", "d.exp3", "a.exp4", "b.exp4", "c.exp4", "d.exp4"}},
        {"exp5_6", {"a.exp5", "ert", "abc", "a.exp6"}},
        {"exp7_8", {"abs", "abc"}},
        {"exp1_2_copy", {"a1", "a2", "a3", "a4", "b1", "b2", "b3", "b4"}},
        {"exp4_3", {"a.exp4", "b.exp4", "c.exp4", "d.exp4", "a.exp3", "b.exp3", "c.exp3", "d.exp3"}}
    };
    EXPECT_EQ(file_parser->get_parser_info().size(), correct_expressions.size());
    for (size_t i = 0; i < correct_expressions.size(); i++) {
        auto iter = file_parser->get_parser_info().find(correct_expressions[i].first);
        EXPECT_NE(iter, file_parser->get_parser_info().end());
        auto attributes = iter->second;
        check_attributes_correction(correct_expressions[i].second, attributes);
    }
}

