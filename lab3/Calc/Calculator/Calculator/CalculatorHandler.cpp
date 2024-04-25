﻿#include "CalculatorHandler.h" 
#include <algorithm>
#include <sstream>

CalculatorHandler::CalculatorHandler(Calculator& calc)
	: m_calc(calc)
{
}

void CalculatorHandler::Handle(std::istream& in, std::ostream& out)
{
    std::string comand;
    while (getline(std::cin, comand))
    {
        if (!CommandHandler(comand, out))
        {
            out << "Unknown command" << std::endl;
        }
    }
}

bool CalculatorHandler::CommandHandler(const string& line, std::ostream& out)
{
    if (line.empty())
    {
        return false;
    }
    std::vector<std::string> action = SplitString(line);
    
    std::string command = action[0];

    if (!CheckCommandExists(command))
    { 
        return false;
    }

	if (command == "var")
	{
        if (action.size() != 2)
        {
            return false;
        }
        AddVar(action[1]);
	}
	else if (command =="let")
	{
        if (action.size() != 4)
        {
            return false;
        }
        AddLet(action[1], action[3]);
	}
    else if (command == "fn")
    {
        if ((action.size() != 4) && (action.size() != 6))
        {
            return false;
        }

        if (action.size() == 4)
        {
            AddFunctionUnar(action[1], action[3]);
        }
        if (action.size() == 6)
        {
            Operation operation = StringToOperation(action[4]);
            AddFunction(action[1], action[3], operation, action[5]);
        }
    }
	else if (command == "print")
	{
        if (action.size() == 2)
        {
            Print(action[1], out);
        }
	}
	else if (command == "printvars")
	{
        if (action.size() == 1)
        {
            PrintVars(out);
        }
	}
	else if (command == "printfns")
	{
        if (action.size() == 1)
        {
            PrintFunctions(out);
        }
	}
    else
    {
        return false;
    }
    return true;
}

bool CalculatorHandler::AddVar(const string& identificator)
{
    if (m_calc.AddVar(identificator))
    {
        std::cout << "Added a variable: " << identificator << std::endl;
        return true;
    }
    else
    {
        std::cout << "Cannot add a variable: " << identificator << std::endl;
        return false;
    }
}

bool CalculatorHandler::AddLet(const string& identificator, const string& identificator2)
{
    if (m_calc.AddLet(identificator, identificator2))
    {
        std::cout << "Added a let: " << identificator << " = " << identificator2 << std::endl;
        return true;
    }
    else
    {
        std::cout << "Cannot add a let: " << identificator << " = " << identificator2 << std::endl;
        return false;
    }
}

bool CalculatorHandler::AddFunction(const string& identificator1, const string& identificator2, Operation operation, const string& identificator3)
{
    if (m_calc.AddFunction(identificator1, identificator2, operation, identificator3))
    {
        std::cout << "Added a function: " << identificator1 << std::endl;
        return true;
    }
    else
    {
        std::cout << "Cannot add a function" << std::endl;
        return false;
    }
}

bool CalculatorHandler::AddFunctionUnar(const string& identificator1, const string& identificator2)
{
    if (m_calc.AddFunctionUnar(identificator1, identificator2))
    {
        std::cout << "Added a function: " << identificator1 << std::endl;
        return true;
    }
    else
    {
        std::cout << "Cannot add a function" << std::endl;
        return false;
    }
}

bool CalculatorHandler::Print(const string& identificator, std::ostream& out) const
{
    m_calc.EnumVariables([](const string& name, const double var, std::ostream& out)
        {
            out << name << " = " << var << std::endl;
        }, identificator, out);

    m_calc.EnumFunctions([](const string& name, const double func, std::ostream& out)
        {
            out << name << " = " << func << std::endl;
        }, identificator, out);
    return true;    
}

bool CalculatorHandler::PrintVars(std::ostream& out) const
{
    const string EMPTY_STR = "";
    m_calc.EnumVariables([](const string& name, const double varValue, std::ostream& out)
        {
            out << name << " = " << varValue << std::endl;
        }, EMPTY_STR, out);
    return true;
}

bool CalculatorHandler::PrintFunctions(std::ostream& out) const
{
    const string EMPTY_STR = "";
    m_calc.EnumFunctions([](const string& name, const double funcValue, std::ostream& out)
        {
            if (std::isnan(funcValue))
            {
                out << name << " undefined" << std::endl;
            }
            else
            {
                out << name << " = " << funcValue << std::endl;
            }
        }, EMPTY_STR, out);
    return true;
} 

Operation CalculatorHandler::StringToOperation(const string& operation_str)
{
    if (operation_str == "+")
        return Operation::ADDITION;
    else if (operation_str == "-")
        return Operation::SUBTRACTION;
    else if (operation_str == "*")
        return Operation::MULTIPLICATION;
    else if (operation_str == "/")
        return Operation::DIVISION;
    else {
        std::cout << "Invalid operation: " << operation_str << std::endl;
        return Operation::INVALID;
    }
}


std::vector<std::string> CalculatorHandler::SplitString(const std::string& input) const
{
    std::vector<std::string> result;
    std::istringstream iss(input);
    std::string token;

    while (iss >> token) {
        size_t pos = token.find('=');
        if (pos != std::string::npos) {
            if (!token.substr(0, pos).empty())
            {
                result.push_back(token.substr(0, pos));
            }
            result.push_back("=");
            if (!token.substr(pos + 1).empty())
            {
                result.push_back(token.substr(pos + 1));
            }
        }
        else 
        {
            result.push_back(token);
        }
    }
    return result;
}


bool CalculatorHandler::CheckCommandExists(const std::string& command) const
{
    if (std::find(COMMANDS.begin(), COMMANDS.end(), command) == COMMANDS.end())
    {
        return false;
    }
    return true;
}