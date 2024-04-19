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
    void Handle(std::istream& in, std::ostream& out);

private:
    bool CommandHandler(const string& command, std::ostream& out);
    
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

    bool Print(const string& identificator, std::ostream& out) const;

    bool PrintVars(std::ostream& out) const;

    bool PrintFunctions(std::ostream& out) const;

    bool CheckCommandExists(const std::string& command) const;
    
    std::vector<std::string> SplitString(const std::string& input) const ;

    [[nodiscard]] Operation StringToOperation(const string& operation_str);
};