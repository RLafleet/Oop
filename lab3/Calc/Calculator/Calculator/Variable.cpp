#include "Variable.h"

using std::string;

Variable::Variable(const std::string& name, double value)
	: m_name(name), m_value(value)
{
}

string Variable::GetName() const 
{ 
	return m_name; 
}

double Variable::GetValue() const 
{ 
	return m_value; 
}