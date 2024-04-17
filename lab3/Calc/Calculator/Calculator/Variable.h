#pragma once
#include <string>
#include <map>

using std::string;
using std::map;

class Variable
{
public:
    Variable() = default;
    explicit Variable(const std::string& name, double value);
    string GetName() const;
    double GetValue() const;

private:
    string m_name;
    double m_value;
};