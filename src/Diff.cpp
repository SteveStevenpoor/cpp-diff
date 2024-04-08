#include "Diff.h"

// Val
Val::Val(double val) : val_(val) {}

Expression* Val::diff(std::string var) {
    return new Val(0);
}

Expression* Val::clone() {
    return new Val(val_);
}

std::string Val::to_string() const {
    std::stringstream ss;
    ss << std::fixed << std::setprecision(0) << val_;
    std::string str = ss.str();
    return str;
}
// Val

// Var
Var::Var(std::string name) : name_(name) {}

Expression* Var::diff(std::string var) {
    if (var == name_) {
        return new Val(1);
    }

    return new Val(0);
}

Expression* Var::clone() {
    return new Var(name_);
}

std::string Var::to_string() const {
    return name_;
}
// Var

// Binary
Binary::Binary(Expression* left, Expression* right) : left_(left), right_(right) {}

Binary::~Binary() {
    if (left_) delete(left_);
    if (right_) delete(right_);
}
// Binary

// Add
Add::Add(Expression* left, Expression* right) : Binary(left, right) {};

Expression* Add::diff(std::string var) {
    return new Add(left_->diff(var), right_->diff(var));
}

Expression* Add::clone() {
    return new Add(left_->clone(), right_->clone());
}

std::string Add::to_string() const {
    return ("(" + left_->to_string() + "+" + right_->to_string() + ")");
}
// Add

// Sub
Sub::Sub(Expression* left, Expression* right) : Binary(left, right) {};

Expression* Sub::diff(std::string var) {
    return new Sub(left_->diff(var), right_->diff(var));
}

Expression* Sub::clone() {
    return new Sub(left_->clone(), right_->clone());
}

std::string Sub::to_string() const {
    return ("(" + left_->to_string() + "-" + right_->to_string() + ")");
}
// Sub

// Mul
Mul::Mul(Expression* left, Expression* right) : Binary(left, right) {};

Expression* Mul::clone() {
    return new Mul(left_->clone(), right_->clone());
}

Expression* Mul::diff(std::string var) {
    return new Add(new Mul(left_->diff(var), right_->clone()), new Mul(left_->clone(), right_->diff(var)));
}

std::string Mul::to_string() const {
    return ("(" + left_->to_string() + "*" + right_->to_string() + ")");
}
// Mul

// Div
Div::Div(Expression* left, Expression* right) : Binary(left, right) {};

Expression* Div::clone() {
    return new Div(left_->clone(), right_->clone());
}

Expression* Div::diff(std::string var) {
    return new Div(new Sub(new Mul(left_->diff(var), right_->clone()),
     new Mul(right_->diff(var), left_->clone())),new Mul(right_->clone(), right_->clone()));
}

std::string Div::to_string() const {
    return ("(" + left_->to_string() + "/" + right_->to_string() + ")");
}
// Div

// Unary
Unary::Unary(Expression* arg) : arg_(arg) {}

Unary::~Unary() {
    if (arg_) delete(arg_);
}
// Unary

// Exp
Exp::Exp(Expression* arg) : Unary(arg) {};

Expression* Exp::clone() {
    return new Exp(arg_->clone());
}

Expression* Exp::diff(std::string var) {
    return new Mul(arg_->diff(var), new Exp(arg_->clone()));
}

std::string Exp::to_string() const {
    return ((std::string)"e" + "^" + arg_->to_string());
}
// Exp