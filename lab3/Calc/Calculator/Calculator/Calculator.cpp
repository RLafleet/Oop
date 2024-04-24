#include <iostream>
#include "Operation.h" 
#include "Calculator.h"
#include <sstream>

using std::string;
using std::map;
using std::string;
using std::unique_ptr;

bool Calculator::ValidIdentificator(const string& identificator) const
{
    if (std::find(COMMANDS.begin(), COMMANDS.end(), identificator) != COMMANDS.end())
    {
        return false;
    }

    char ch = identificator[0];
    if ((ch >= '0' && ch <= '9'))
    {
        return false;
    }
    
    return true;
}

bool Calculator::IsIdentificatorExists(const string& identificator) const
{
    if (m_funcs.find(identificator) != m_funcs.end())
    {
        std::cout << "Function with that identificator '" << identificator << "' already exists" << std::endl;
        return false;
    }

    if (m_vars.find(identificator) != m_vars.end())
    {
        std::cout << "Variable with that identificator '" << identificator << "' already exists" << std::endl;
        return false;
    }

    return true;
}

bool Calculator::AddVar(const string& identificator)
{
    if (!ValidIdentificator(identificator) || 
        !IsIdentificatorExists(identificator))
    {
        return false;
    }
    
    unique_ptr<Variable> new_var(new Variable(identificator, NAN));
    m_vars[identificator] = std::move(new_var);

    return true;
}

bool Calculator::AddLet(const string& identificator, const string& identificator2)
{
    if (!ValidIdentificator(identificator))
    {
        return false;
    }

    if (m_funcs.find(identificator) != m_funcs.end()) {
        std::cout << "Function with that identificator '" << identificator << "' already exists" << std::endl;
        return false;
    }

    double value = GetVariableValue(identificator2);
    unique_ptr<Variable> new_var(new Variable(identificator, value));
    m_vars[identificator] = std::move(new_var);

    return true;
}

bool Calculator::AddFunction(const string& identificator1, const string& identificator2, Operation operation, const string& identificator3)
{
    if (!ValidIdentificator(identificator1) || 
        !ValidIdentificator(identificator2) || 
        !ValidIdentificator(identificator3) || 
        !IsIdentificatorExists(identificator1))
    {
        return false;
    }
    
    unique_ptr<Function> new_fn(new Function(identificator1, identificator2, operation, identificator3));
    m_funcs[identificator1] = std::move(new_fn);

    return true;
}

bool Calculator::AddFunctionUnar(const string& identificator1, const string& identificator2)
{
    if (!ValidIdentificator(identificator1) ||
        !IsIdentificatorExists(identificator1))
    {
        std::cout << "false";
        return false;
    }

    unique_ptr<Function> new_fn(new Function(identificator1, identificator2));
    m_funcs[identificator1] = std::move(new_fn);

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

double Calculator::GetVariableValue(const string& str) const
{
    double value;
    
    try 
    {
        value = std::stod(str);
    }
    catch (...) 
    {
        value = NAN;
    }
    
    if (std::isnan(value))
    {
        auto it = m_vars.find(str);
        if (it != m_vars.end())
        {
            value = it->second->GetValue();
        }
    }

    if (std::isnan(value))
    {
        auto it = m_funcs.find(str);
        if (it != m_funcs.end())
        {
            value = CalculateFunctionValue(*it->second);
        }
    }

    return value;
}

double Calculator::GetFunctionValue(const string& str) const
{
    std::string currentExpr = str;

    while (true) {
        auto it = m_funcs.find(currentExpr);
        if (it != m_funcs.end()) {
            std::stringstream ss(it->second->GetVar1());
            double value;
            if (ss >> value) {
                return value;
            }
            else {
                currentExpr = it->second->GetVar1();
            }
        }
        else {
            break; 
        }
    }

    return NAN;
}



double Calculator::CalculateFunctionValue(const Function& func) const
{
    string temp = func.GetVar1();
    double value = GetVariableValue(temp);
    double variableValue = (std::isnan(value)) ? GetFunctionValue(temp) : value;

    Operation operation;
    if (func.GetOperation() != Operation::INVALID)
    {
        temp = func.GetVar2();
        operation = func.GetOperation();
        double tempValue = GetVariableValue(temp);
        variableValue = CalculateOperation(variableValue, operation, tempValue);
    }
    return variableValue;
}

void Calculator::EnumFunctions(Callback callback, const string& identificator1, std::ostream& out) const
{
    string temp;

    if (!identificator1.empty())
    {
        for (const auto& pair : m_funcs)
        {
            const string& name = pair.first;
            const Function& func = *pair.second;
            if (name == identificator1)
            {
                callback(name, CalculateFunctionValue(func), out);
            }
        }
        return;
    }
    for (const auto& pair : m_funcs)
    {
        const string& name = pair.first;
        const Function& func = *pair.second;
        callback(name, CalculateFunctionValue(func), out);
    }
}

void Calculator::EnumVariables(Callback callback, const string& identificator1, std::ostream& out) const
{
    if (!identificator1.empty())
    {
        for (const auto& pair : m_vars)
        {
            const string& name = pair.first;
            const Variable& var = *pair.second;
            if (name == identificator1)
            {
                callback(name, var.GetValue(), out);
            }
        }
        return;
    }
    for (const auto& pair : m_vars)
    {
        const string& name = pair.first;
        const Variable& var = *pair.second;

        callback(name, var.GetValue(), out);
    }
}