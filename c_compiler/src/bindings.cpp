#include "bindings.hpp"

#include <iostream>


// VariableStackBindings definition

VariableStackBindings::VariableStackBindings()
    : stack_counter_(4), expression_stack_(-4)
{}

void VariableStackBindings::insertBinding(std::string id, TypePtr type, int stack_position)
{
    DeclarationData decl_data;
    decl_data.type = type;
    decl_data.stack_position = stack_position;

    bindings_.insert(std::pair<std::string, DeclarationData>(id, decl_data));
}

void VariableStackBindings::increaseStackPosition()
{
    stack_counter_ += 4;
}

void VariableStackBindings::resetExpressionStack()
{
    expression_stack_ = -4;
}

void VariableStackBindings::nextExpressionStackPosition()
{
    expression_stack_ -= 4;
}

int VariableStackBindings::currentStackPosition() const
{
    return stack_counter_;
}

int VariableStackBindings::stackPosition(const std::string &id) const
{
    auto binding = bindings_.find(id);

    if(binding != bindings_.end())
	return (*binding).second.stack_position;

    else return 0;
}

int VariableStackBindings::currentExpressionStackPosition() const
{
    return expression_stack_;
}

bool VariableStackBindings::bindingExists(const std::string &id) const
{
    auto binding = bindings_.find(id);

    if(binding == bindings_.end())
	return false;

    else
	return true;
}