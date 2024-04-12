#include <iostream>
#include "Operation.h" 
#include "Calculator.h"

#include <sstream>

using std::string;
using std::map;
using std::string;

bool Calculator::AddVar(const string& identificator) 
{
    if (m_vars.find(identificator) != m_vars.end()) 
    {
        std::cout << "Variable '" << identificator << "' already exists." << std::endl;
        return false;
    }
    Variable new_var(identificator, NAN);
    m_vars[identificator] = new_var;

    std::cout << "Added variable '" << identificator << "'." << std::endl;
    return true;
}

bool Calculator::AddLet(const string& identificator, double value)
{
    Variable new_var(identificator, value);
    m_vars[identificator] = new_var;

    std::cout << "Added constant '" << identificator << "' with value " << value << "." << std::endl;
    return true;
}

bool Calculator::AddFunction(const string& identificator1, const string& identificator2, Operation operation, const string& identificator3)
{
    if (m_funcs.find(identificator1) != m_funcs.end()) {
        std::cout << "Function '" << identificator1 << "' already exists." << std::endl;
        return false;
    }
    /*
    if (m_vars.find(identificator2) == m_vars.end() || m_vars.find(identificator3) == m_vars.end()) {
        std::cout << "One or both operands for function '" << identificator1 << "' are undefined." << std::endl;
        return false;
    }
    */
    
    Function new_fn(identificator1, identificator2, operation, identificator3);
    m_funcs[identificator1] = new_fn;

    std::cout << "Added function '" << identificator1 << "'." << std::endl;
    return true;
}

bool Calculator::AddFunctionUnar(const string& identificator1, const string& identificator2)
{
    Function new_fn(identificator1, identificator2);
    m_funcs[identificator1] = new_fn;

    std::cout << "Added constant '" << identificator1 << "' with unar identificator " << identificator2 << "." << std::endl;
    return true;
}

double CalculateOperation(double variableValue, Operation operation, double tempValue)
{
    double result = variableValue;
    if (operation == Operation::ADDITION)
    {
        result += tempValue;
    }
    else if (operation == Operation::DIVISION)
    {
        result /= tempValue;
    }
    else if (operation == Operation::MULTIPLICATION)
    {
        result *= tempValue;

    }
    else if (operation == Operation::SUBTRACTION)
    {
        result -= tempValue;
    }
    return result;
}

double Calculator::CalculateFunctionValue(const Function& func) const
{
    double variableValue = NAN;
    string temp = func.GetVar1();
    Operation operation;
    auto it = m_vars.find(temp);
    if (it != m_vars.end()) 
    {
        variableValue = it->second.GetValue();
        if (func.GetOperation() != Operation::INVALID)
        {
            temp = func.GetVar2();
            operation = func.GetOperation();
            it = m_vars.find(temp);
            if (it != m_vars.end())
            {
                double tempValue = it->second.GetValue();
                variableValue = CalculateOperation(variableValue, operation, tempValue);
            }
        }
    }
    return variableValue;
}

void Calculator::EnumFunctions(Callback callback, const string& identificator1) const
{
    string temp;

    if (!identificator1.empty())
    {
        for (const auto& pair : m_funcs)
        {
            const string& name = pair.first;
            const Function& func = pair.second;
            if (name == identificator1)
            {
                callback(name, CalculateFunctionValue(func));
            }
        }
        return;
    }
    for (const auto& pair : m_funcs)
    {
        const string& name = pair.first;
        const Function& func = pair.second;
        callback(name, CalculateFunctionValue(func));
    }
}

void Calculator::EnumVariables(Callback callback, const string& identificator1) const
{
    if (!identificator1.empty())
    {
        for (const auto& pair : m_vars)
        {
            const string& name = pair.first;
            const Variable& var = pair.second;
            if (name == identificator1)
            {
                callback(name, var.GetValue());
            }
        }
        return;
    }
    for (const auto& pair : m_vars)
    {
        const string& name = pair.first;
        const Variable& var = pair.second;
        callback(name, var.GetValue());
    }
}