#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <string>
#include <iostream>
#include <map>
#include "Operation.h"
#include "Function.h"
#include "Variable.h"

typedef void (*Callback) (const std::string& substrOne, const double substrTwo);

class Calculator 
{
public:
    bool AddVar(const std::string& identificator);

    bool AddLet(const std::string& identificator, const string& identificator2);

    bool AddFunction(const std::string& identificator1, const std::string& identificator2, Operation operation, const std::string& identificator3);

    bool AddFunctionUnar(const std::string& identificator1, const std::string& value);

    void EnumVariables(Callback callback, const std::string& identificator1) const;
    
    double GetVariableValue(const string& str) const;

    double GetFunctionValue(const string& str) const;

    void EnumFunctions(Callback callback, const std::string& identificator1) const;

private:
    std::map<std::string, Variable> m_vars = {};
    std::map<std::string, Function> m_funcs = {};

    double CalculateFunctionValue(const Function& func) const;
};

#endif // CALCULATOR_H