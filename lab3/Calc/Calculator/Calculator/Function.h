#pragma once
#include <string>
#include <map>
#include "Operation.h"

using std::string;
using std::map;

class Function 
{
public:
    Function() = default;
    explicit Function(const std::string& name, const std::string& var1, const Operation operation = Operation::INVALID, const string& var2 = "");
    string GetName() const;
    string GetVar1() const;
    Operation GetOperation() const;
    string GetVar2() const;

private:
    string m_name;
    string m_var1;
    string m_var2;
    Operation m_operation;
};