#pragma once
#include "Calculator.h"
#include "Operation.h"
#include <vector>
#include <string>
#include <map>

class CalculatorHandler
{
public:
    explicit CalculatorHandler(Calculator& calc);

    bool CommandHandler(const string& command);

private:
    const std::map<std::string, Operation> OPERATIONS_MAP = 
    {
            {"+", Operation::ADDITION},
            {"-", Operation::SUBTRACTION},
            {"*", Operation::MULTIPLICATION},
            {"/", Operation::DIVISION},
    };
    const std::vector<std::string> COMMANDS = {
            "var",
            "let",
            "fn",
            "print",
            "printfns",
            "printvars",
    };

    Calculator& m_calc;

    bool AddVar(const string& identificator);

    bool AddLet(const string& identificator, const string& identificator2);

    bool AddFunction(const string& identificator1, const string& identificator2, Operation operation, const string& identificator3);

    bool AddFunctionUnar(const string& identificator1, const string& identificator2);

    bool Print(const string& identificator) const;

    bool PrintVars() const;

    bool PrintFunctions() const;

    bool CheckCommandExists(const std::string& command) const;
    
    std::vector<std::string> SplitString(const std::string& input) const ;

    [[nodiscard]] Operation StringToOperation(const string& operation_str);
};