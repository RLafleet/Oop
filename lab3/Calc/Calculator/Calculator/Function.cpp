#include "Function.h"
#include <sstream>

using std::string;

Function::Function(const std::string& name, const std::string& var1, const Operation operation, const string& var2)
	: m_name(name), m_var1(var1), m_operation(operation), m_var2(var2)
{
}

string Function::GetName() const
{
	return m_name;
}

string Function::GetVar1() const
{
	return m_var1;
}

Operation Function::GetOperation() const
{
	return m_operation;
}

string Function::GetVar2() const
{
	return m_var2;
}