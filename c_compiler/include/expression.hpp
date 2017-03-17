#ifndef EXPRESSION_HPP
#define EXPRESSION_HPP

#include "bindings.hpp"
#include "node.hpp"
#include "type.hpp"

#include <cstdint>
#include <memory>
#include <string>

class Expression;

typedef std::shared_ptr<Expression> ExpressionPtr;


class Expression : public Node
{
private:
    ExpressionPtr next_expression_;
    
public:
    virtual VariableStackBindings printAsm(VariableStackBindings bindings, unsigned& label_count) const = 0;
    
    virtual void print() const;
    virtual void printXml() const;
    virtual void countArguments(unsigned& argument_count) const;
    
    virtual int postfixStackPosition(VariableStackBindings bindings) const;
    virtual void setPostfixExpression(Expression* postfix_expression);

    virtual std::string id() const;

    void linkExpression(Expression* next_expression);
    ExpressionPtr nextExpression() const;
};


class OperationExpression : public Expression
{
protected:
    ExpressionPtr lhs_;
    ExpressionPtr rhs_;
public:
    OperationExpression(Expression* lhs, Expression* rhs);

    virtual VariableStackBindings printAsm(VariableStackBindings bindings, unsigned& label_count) const = 0;
};


class PostfixExpression : public Expression
{
public:
    PostfixExpression();

    virtual VariableStackBindings printAsm(VariableStackBindings bindings, unsigned& label_count) const;
};


class PostfixArrayElement : public Expression
{
public:
    PostfixArrayElement();

    virtual VariableStackBindings printAsm(VariableStackBindings bindings, unsigned& label_count) const;
};


class PostfixFunctionCall : public Expression
{
private:
    ExpressionPtr postfix_expression_;
    ExpressionPtr argument_expression_list_;
    
public:
    PostfixFunctionCall(Expression* argument_expression_list = nullptr);

    virtual VariableStackBindings printAsm(VariableStackBindings bindings, unsigned& label_count) const;
    virtual void countArguments(unsigned& argument_count) const;
    
    void setPostfixExpression(Expression* postfix_expression);
};


class UnaryExpression : public Expression
{
public:
    UnaryExpression();

    virtual VariableStackBindings printAsm(VariableStackBindings bindings, unsigned& label_count) const;
};


class CastExpression : public Expression
{
private:
    TypePtr type_;
    ExpressionPtr expression_;

public:
    CastExpression(Type* type, Expression* expression);

    virtual VariableStackBindings printAsm(VariableStackBindings bindings, unsigned& label_count) const;
};


class AdditiveExpression : public OperationExpression
{
private:
    std::string operator_;

public:
    AdditiveExpression(Expression* lhs, const std::string& _operator, Expression* rhs);

    virtual VariableStackBindings printAsm(VariableStackBindings bindings, unsigned& label_count) const;
};


class MultiplicativeExpression : public OperationExpression
{
private:
    std::string operator_;

public:
    MultiplicativeExpression(Expression* lhs, const std::string& _operator, Expression* rhs);

    virtual VariableStackBindings printAsm(VariableStackBindings bindings, unsigned& label_count) const;
};


class ShiftExpression : public OperationExpression
{
public:
    ShiftExpression(Expression* lhs, Expression* rhs);

    virtual VariableStackBindings printAsm(VariableStackBindings bindings, unsigned& label_count) const;
};


class RelationalExpression : public OperationExpression
{
public:
    RelationalExpression(Expression* lhs, Expression* rhs);

    virtual VariableStackBindings printAsm(VariableStackBindings bindings, unsigned& label_count) const;
};


class EqualityExpression : public OperationExpression
{
private:
    std::string operator_;
public:
    EqualityExpression(Expression* lhs, const std::string& _operator, Expression* rhs);

    virtual VariableStackBindings printAsm(VariableStackBindings bindings, unsigned& label_count) const;
};


class AndExpression : public OperationExpression
{
public:
    AndExpression(Expression* lhs, Expression* rhs);

    virtual VariableStackBindings printAsm(VariableStackBindings bindings, unsigned& label_count) const;
};


class ExclusiveOrExpression : public OperationExpression
{
public:
    ExclusiveOrExpression(Expression* lhs, Expression* rhs);

    virtual VariableStackBindings printAsm(VariableStackBindings bindings, unsigned& label_count) const;
};


class InclusiveOrExpression : public OperationExpression
{
public:
    InclusiveOrExpression(Expression* lhs, Expression* rhs);

    virtual VariableStackBindings printAsm(VariableStackBindings bindings, unsigned& label_count) const;
};


class LogicalAndExpression : public OperationExpression
{
public:
    LogicalAndExpression(Expression* lhs, Expression* rhs);

    virtual VariableStackBindings printAsm(VariableStackBindings bindings, unsigned& label_count) const;
};


class LogicalOrExpression : public OperationExpression
{
public:
    LogicalOrExpression(Expression* lhs, Expression* rhs);

    virtual VariableStackBindings printAsm(VariableStackBindings bindings, unsigned& label_count) const;
};


class ConditionalExpression : public Expression
{
private:
    ExpressionPtr logical_or_;
    ExpressionPtr expression_;
    ExpressionPtr conditional_expression_;

public:
    ConditionalExpression(Expression* logical_or, Expression* expression,
			  Expression* conditional_expression);
    
    virtual VariableStackBindings printAsm(VariableStackBindings bindings, unsigned& label_count) const;
};


class AssignmentExpression : public OperationExpression
{
public:
    AssignmentExpression(Expression* lhs, Expression* rhs);

    virtual VariableStackBindings printAsm(VariableStackBindings bindings, unsigned& label_count) const;
};


class Identifier : public Expression
{
private:
    std::string id_;
public:
    Identifier(const std::string& id);

    virtual VariableStackBindings printAsm(VariableStackBindings bindings, unsigned& label_count) const;
    virtual int postfixStackPosition(VariableStackBindings bindings) const;
    virtual std::string id() const;
};


class Constant : public Expression
{
private:
    int32_t constant_;
public:
    Constant(const int32_t& constant);

    virtual VariableStackBindings printAsm(VariableStackBindings bindings, unsigned& label_count) const;
};


#endif
