#pragma once
#include <vector>

enum class Operation {
    ADDITION,
    SUBTRACTION,
    MULTIPLICATION,
    DIVISION,
    INVALID
};

const std::vector<std::string> COMMANDS = {
    "var",
    "let",
    "fn",
    "print",
    "printfns",
    "printvars",
};