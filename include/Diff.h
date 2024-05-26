#ifndef DIFF_H
#define DIFF_H

#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>
#include <memory>

class Expression
{
public:
    virtual Expression* diff(std::string var) = 0;
    virtual Expression* clone() = 0;
    virtual std::string to_string() const = 0;
    virtual ~Expression() = default;
};

class Val : public Expression {
    double val_;
public:
    Val(double val);
    Expression* diff(std::string var);
    Expression* clone();
    std::string to_string() const;
};

class Var : public Expression {
    std::string name_;
public:
    Var(std::string name);
    Expression* diff(std::string var);
    Expression* clone();
    std::string to_string() const;
};

class Binary : public Expression {
protected:
    Expression* left_;
    Expression* right_;
public:
    Binary(Expression* left, Expression* right);
    std::string to_string() const;
    virtual std::string get_op() const = 0;
    ~Binary();
};

class Add : public Binary {
public:
    Add(Expression* left, Expression* right);
    Expression* diff(std::string var);
    Expression* clone();
    std::string get_op() const override;
};

class Sub : public Binary {
public:
    Sub(Expression* left, Expression* right);
    Expression* diff(std::string var);
    Expression* clone();
    std::string get_op() const override;
};

class Mul : public Binary {
public:
    Mul(Expression* left, Expression* right);
    Expression* diff(std::string var);
    Expression* clone();
    std::string get_op() const override;
};

class Div : public Binary {
public:
    Div(Expression* left, Expression* right);
    Expression* diff(std::string var);
    Expression* clone();
    std::string get_op() const override;
};

class Unary : public Expression {
protected:
    Expression* arg_;
public:
    Unary(Expression* arg);
    // std::to_string() const;
    // Expression* clone();
    ~Unary();
};

class Exp : public Unary {
public:
    Exp(Expression* arg);
    Expression* diff(std::string var);
    Expression* clone();
    std::string to_string() const;
};

#endif // DIFF_H
