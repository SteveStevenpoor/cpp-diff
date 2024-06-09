#include <Diff.h>
#include <gtest/gtest.h>
#include <iostream>


TEST(diff, TestingVal) {
    // exp = 10.1234
    Expression* exp = new Val(10);
    std::string exp_str = exp->to_string();
    EXPECT_EQ(exp_str, (std::string)"10");

    // d exp/ dx = 0
    Expression* diff_exp = exp->diff("x");
    exp_str = diff_exp->to_string();
    EXPECT_EQ(exp_str, (std::string)"0");

    delete(exp);
    delete(diff_exp);
}

TEST(diff, TestingVar) {
    // exp = x
    Expression* exp = new Var("x");
    std::string exp_str = exp->to_string();
    EXPECT_EQ(exp_str, (std::string)"x");

    // d exp/ dx = 1
    Expression* diff_exp1 = exp->diff("x");
    exp_str = diff_exp1->to_string();
    EXPECT_EQ(exp_str, (std::string)"1");

    // d exp/ dy = 0
    Expression* diff_exp2 = exp->diff("y");
    exp_str = diff_exp2->to_string();
    EXPECT_EQ(exp_str, (std::string)"0");

    delete(exp);
    delete(diff_exp1);
    delete(diff_exp2);
}

TEST(diff, TestingAdd) {
    Expression* exp = new Add(new Var("x"), new Var("y"));
    std::string exp_str = exp->to_string();
    EXPECT_EQ(exp_str, (std::string)"(x+y)");

    Expression* diff_exp1 = exp->diff("x");
    exp_str = diff_exp1->to_string();
    EXPECT_EQ(exp_str, (std::string)"(1+0)");

    Expression* diff_exp2 = exp->diff("y");
    exp_str = diff_exp2->to_string();
    EXPECT_EQ(exp_str, (std::string)"(0+1)");

    delete(exp);
    delete(diff_exp1);
    delete(diff_exp2);
}

TEST(diff, TestingSub) {
    Expression* exp = new Sub(new Var("x"), new Var("y"));
    std::string exp_str = exp->to_string();
    EXPECT_EQ(exp_str, (std::string)"(x-y)");

    Expression* diff_exp1 = exp->diff("x");
    exp_str = diff_exp1->to_string();
    EXPECT_EQ(exp_str, (std::string)"(1-0)");

    Expression* diff_exp2 = exp->diff("y");
    exp_str = diff_exp2->to_string();
    EXPECT_EQ(exp_str, (std::string)"(0-1)");

    delete(exp);
    delete(diff_exp1);
    delete(diff_exp2);
}

TEST(diff, TestingMul) {
    Expression* exp = new Add(new Var("x"), new Mul(new Val(10), new Var("y")));
    std::string exp_str = exp->to_string();
    EXPECT_EQ(exp_str, (std::string)"(x+(10*y))");

    Expression* diff_exp1 = exp->diff("x");
    exp_str = diff_exp1->to_string();
    EXPECT_EQ(exp_str, (std::string)"(1+((0*y)+(10*0)))");

    Expression* diff_exp2 = exp->diff("y");
    exp_str = diff_exp2->to_string();
    EXPECT_EQ(exp_str, (std::string)"(0+((0*y)+(10*1)))");

    delete(exp);
    delete(diff_exp1);
    delete(diff_exp2);
}

TEST(diff, TestingDiv) {
    Expression* exp = new Add(new Var("x"), new Div(new Val(10), new Var("y")));
    std::string exp_str = exp->to_string();
    EXPECT_EQ(exp_str, (std::string)"(x+(10/y))");

    Expression* diff_exp1 = exp->diff("x");
    exp_str = diff_exp1->to_string();
    EXPECT_EQ(exp_str, (std::string)"(1+(((0*y)-(0*10))/(y*y)))");

    Expression* diff_exp2 = exp->diff("y");
    exp_str = diff_exp2->to_string();
    EXPECT_EQ(exp_str, (std::string)"(0+(((0*y)-(1*10))/(y*y)))");

    delete(exp);
    delete(diff_exp1);
    delete(diff_exp2);
}

TEST(diff, TestingExp) {
    Expression* exp = new Add(new Var("x"), new Exp(new Mul(new Val(5), new Var("x"))));
    std::string exp_str = exp->to_string();
    EXPECT_EQ(exp_str, (std::string)"(x+e^(5*x))");

    Expression* diff_exp1 = exp->diff("x");
    exp_str = diff_exp1->to_string();
    EXPECT_EQ(exp_str, (std::string)"(1+(((0*x)+(5*1))*e^(5*x)))");

    Expression* diff_exp2 = exp->diff("y");
    exp_str = diff_exp2->to_string();
    EXPECT_EQ(exp_str, (std::string)"(0+(((0*x)+(5*0))*e^(5*x)))");

    delete(exp);
    delete(diff_exp1);
    delete(diff_exp2);
}

TEST(wrong, WrongTest) {
    EXPECT_EQ(0, 1);
}
