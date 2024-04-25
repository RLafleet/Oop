#define CATCH_CONFIG_MAIN
#include "../../../../Catch2/catch.hpp"

#include <sstream>
#include "../Calculator/Calculator.h"
#include "../Calculator/CalculatorHandler.h"

TEST_CASE("Invalid identifier error") {
    Calculator calculator;
    CalculatorHandler calculatorCommandParser = CalculatorHandler(calculator);
    std::string var = "0reererr";
    std::string var2 = "";
    std::string var3 = "5";
    std::string var4 = "0";
    std::string var5 = "6";

    std::istringstream mockInput("var " + var + "\n"
        + "var " + var2 + "\n"
        + "var " + var3 + "\n"
        + "var " + var4 + "\n"
        + "var " + var5 + "\n"
    );
    std::streambuf* origCin = std::cin.rdbuf(mockInput.rdbuf());

    std::ostringstream mockOutput;
    std::streambuf* oldCout = std::cout.rdbuf(mockOutput.rdbuf());

    calculatorCommandParser.Handle(mockInput, mockOutput);

    std::cin.rdbuf(origCin);
    std::cout.rdbuf(oldCout);

    std::string expectedOutput =
        "Cannot add a variable: " + var + "\n"
        "Unknown command" + "\n"
        "Cannot add a variable: " + var3 + "\n"
        "Cannot add a variable: " + var4 + "\n"
        "Cannot add a variable: " + var5 + "\n";
    std::cout << mockOutput.str() << std::endl;
    REQUIRE(mockOutput.str() == expectedOutput);
}

TEST_CASE("Init nan var success") {
    Calculator calculator;
    CalculatorHandler calculatorCommandParser = CalculatorHandler(calculator);
    std::string var = "x";
    std::string expectedValue = "nan";

    std::istringstream mockInput("var " + var + "\nprintvars\n");
    std::streambuf* origCin = std::cin.rdbuf(mockInput.rdbuf());

    std::ostringstream mockOutput;
    std::streambuf* oldCout = std::cout.rdbuf(mockOutput.rdbuf());

    calculatorCommandParser.Handle(mockInput, mockOutput)   ;

    std::cin.rdbuf(origCin);
    std::cout.rdbuf(oldCout);

    std::string expectedOutput = 
        "Added a variable: " + var + "\n"
        + var + " = " + expectedValue + "\n";
    REQUIRE(mockOutput.str() == expectedOutput);
}


TEST_CASE("Init nan var already exist func error") {
    Calculator calculator;
    CalculatorHandler calculatorCommandParser = CalculatorHandler(calculator);

    std::string var = "x";
    std::string func = "y";
    std::string var2 = "y";

    std::istringstream mockInput("var " + var + "\n" + "fn " + func + " = " + var + "\n" + "var " + var2 + "\n");
    std::streambuf* origCin = std::cin.rdbuf(mockInput.rdbuf());

    std::ostringstream mockOutput;
    std::streambuf* oldCout = std::cout.rdbuf(mockOutput.rdbuf());

    calculatorCommandParser.Handle(mockInput, mockOutput);

    std::string expectedOutput = 
        "Added a variable: " + var + "\n"
        "Added a function: " + func + "\n"
        "Function with that identificator '" + var2 + "' already exists\n"
        "Cannot add a variable: " + var2 + "\n";

    REQUIRE(mockOutput.str() == expectedOutput);

    std::cin.rdbuf(origCin);
    std::cout.rdbuf(oldCout);
}

TEST_CASE("Init nan var already exist var error") {
    Calculator calculator;
    CalculatorHandler calculatorCommandParser = CalculatorHandler(calculator);

    std::string var = "x";
    std::string var1 = "y";
    std::string var2 = "y";

    std::istringstream mockInput("var " + var + "\n" + "var " + var1 + "\n" + "var " + var2 + "\n");
    std::streambuf* origCin = std::cin.rdbuf(mockInput.rdbuf());

    std::ostringstream mockOutput;
    std::streambuf* oldCout = std::cout.rdbuf(mockOutput.rdbuf());

    calculatorCommandParser.Handle(mockInput, mockOutput);

    std::string expectedOutput =
        "Added a variable: " + var + "\n"
        "Added a variable: " + var1 + "\n"
        "Variable with that identificator '" + var2 + "' already exists\n"
        "Cannot add a variable: " + var2 + "\n";

    REQUIRE(mockOutput.str() == expectedOutput);

    std::cin.rdbuf(origCin);
    std::cout.rdbuf(oldCout);
}

TEST_CASE("Init let success") {
    Calculator calculator;
    CalculatorHandler calculatorCommandParser = CalculatorHandler(calculator);
    std::string let = "x";
    std::string value = "1.2";
    std::string expectedValue = "1.2";

    std::istringstream mockInput("let " + let + " = " + value + "\nprintvars\n");
    std::streambuf* origCin = std::cin.rdbuf(mockInput.rdbuf());

    std::ostringstream mockOutput;
    std::streambuf* oldCout = std::cout.rdbuf(mockOutput.rdbuf());

    calculatorCommandParser.Handle(mockInput, mockOutput);

    std::cin.rdbuf(origCin);
    std::cout.rdbuf(oldCout);

    std::string expectedOutput =
        "Added a let: " + let + " = " + expectedValue + "\n"
        "x = " + expectedValue + "\n";

    REQUIRE(mockOutput.str() == expectedOutput);
}

TEST_CASE("Let assign another let success") {
    Calculator calculator;
    CalculatorHandler calculatorCommandParser = CalculatorHandler(calculator);
    std::string let = "x";
    std::string value = "1.2";
    std::string expectedValue = "1.2";
    std::string let2 = "y";

    std::istringstream mockInput(
        "let " + let + " = " + value + "\n"
        + "let " + let2 + " = " + let + "\n"
        + "printvars\n"
    );
    std::streambuf* origCin = std::cin.rdbuf(mockInput.rdbuf());

    std::ostringstream mockOutput;
    std::streambuf* oldCout = std::cout.rdbuf(mockOutput.rdbuf());

    calculatorCommandParser.Handle(mockInput, mockOutput);

    std::cin.rdbuf(origCin);
    std::cout.rdbuf(oldCout);

    std::string expectedOutput =
        "Added a let: " + let + " = " + expectedValue + "\n"
        "Added a let: " + let2 + " = " + let + "\n"
        "x = " + expectedValue + "\n"
        "y = " + expectedValue + "\n";

    REQUIRE(mockOutput.str() == expectedOutput);
}

TEST_CASE("Let assign another inited let success") {
    Calculator calculator;
    CalculatorHandler calculatorCommandParser = CalculatorHandler(calculator);
    std::string let = "x";
    std::string value = "1.23465";
    std::string expectedValue = "1.23465";
    std::string let2 = "y";
    std::string value2 = "-2.3";

    std::istringstream mockInput(
        "let " + let + " = " + value + "\n"
        + "let " + let2 + " = " + value2 + "\n"
        + "let " + let2 + " = " + let + "\n"
        + "printvars\n"
    );
    std::streambuf* origCin = std::cin.rdbuf(mockInput.rdbuf());

    std::ostringstream mockOutput;
    std::streambuf* oldCout = std::cout.rdbuf(mockOutput.rdbuf());

    calculatorCommandParser.Handle(mockInput, mockOutput);

    std::cin.rdbuf(origCin);
    std::cout.rdbuf(oldCout);

    std::string expectedOutput =
        "Added a let: " + let + " = " + value + "\n"
        "Added a let: " + let2 + " = " + value2 + "\n"
        "Added a let: " + let2 + " = " + let + "\n"
        "x = " + expectedValue + "\n"
        "y = " + expectedValue + "\n";

    REQUIRE(mockOutput.str() == expectedOutput);
}

TEST_CASE("Let assign another inited func success") 
{
    Calculator calculator;
    CalculatorHandler calculatorCommandParser = CalculatorHandler(calculator);
    std::string let = "x";
    std::string let2 = "y";
    std::string let3 = "z";
    std::string value = "1";
    std::string value2 = "2";
    std::string func = "func";
    std::string expectedValue = "3";

    std::istringstream mockInput(
        "let " + let + " = " + value + "\n"
        + "let " + let2 + " = " + value2 + "\n"
        + "fn " + func + " = " + let + " + " + let2 + "\n"
        + "let " + let3 + " = " + func + "\n"
        + "print " + let3 + "\n"
    );
    std::streambuf* origCin = std::cin.rdbuf(mockInput.rdbuf());

    std::ostringstream mockOutput;
    std::streambuf* oldCout = std::cout.rdbuf(mockOutput.rdbuf());

    calculatorCommandParser.Handle(mockInput, mockOutput);

    std::cin.rdbuf(origCin);
    std::cout.rdbuf(oldCout);

    std::string expectedOutput =
        "Added a let: " + let + " = " + value + "\n"
        "Added a let: " + let2 + " = " + value2 + "\n"
        "Added a function: " + func + "\n"
        "Added a let: " + let3 + " = " + func + "\n"
        "z = " + expectedValue + "\n";

    REQUIRE(mockOutput.str() == expectedOutput);
}


TEST_CASE("Init func with nan var success") 
{
    Calculator calculator;
    CalculatorHandler calculatorCommandParser = CalculatorHandler(calculator);
    std::string var = "x";
    std::string func = "Xplus";
    std::string expectedValue = "undefined";

    std::istringstream mockInput(
        "var " + var + "\n"
        + "fn " + func + " = " + var + "\n"
        + "printfns"
    );
    std::streambuf* origCin = std::cin.rdbuf(mockInput.rdbuf());

    std::ostringstream mockOutput;
    std::streambuf* oldCout = std::cout.rdbuf(mockOutput.rdbuf());

    calculatorCommandParser.Handle(mockInput, mockOutput);

    std::cin.rdbuf(origCin);
    std::cout.rdbuf(oldCout);

    std::string expectedOutput =
        "Added a variable: " + var + "\n"
        "Added a function: " + func + "\n"
        "Xplus " + expectedValue + "\n";

    REQUIRE(mockOutput.str() == expectedOutput);
}

TEST_CASE("Init func with nan vars success") 
{
    Calculator calculator;
    CalculatorHandler calculatorCommandParser = CalculatorHandler(calculator);
    std::string var = "x";
    std::string var1 = "y";
    std::string func = "Xplus";
    std::string expectedValue = "undefined";

    std::istringstream mockInput(
        "var " + var + "\n"
        + "var " + var1 + "\n"
        + "fn " + func + " = " + var + " + " + var1 + "\n"
        + "printfns"
    );
    std::streambuf* origCin = std::cin.rdbuf(mockInput.rdbuf());

    std::ostringstream mockOutput;
    std::streambuf* oldCout = std::cout.rdbuf(mockOutput.rdbuf());

    calculatorCommandParser.Handle(mockInput, mockOutput);

    std::cin.rdbuf(origCin);
    std::cout.rdbuf(oldCout);

    std::string expectedOutput =
        "Added a variable: " + var + "\n"
        "Added a variable: " + var1 + "\n"
        "Added a function: " + func + "\n"
        "Xplus " + expectedValue + "\n";

    REQUIRE(mockOutput.str() == expectedOutput);
}

TEST_CASE("init func with nan func success") {
    Calculator calculator;
    CalculatorHandler calculatorCommandParser = CalculatorHandler(calculator);
    std::string var = "x";
    std::string var1 = "y";
    std::string func = "Xplus";
    std::string func1 = "Xplus1";
    std::string expectedValue = "undefined";

    std::istringstream mockInput(
        "var " + var + "\n"
        + "var " + var1 + "\n"
        + "fn " + func + " = " + var + " + " + var1 + "\n"
        + "fn " + func1 + " = " + func + "\n"
        + "printfns"
    );
    std::streambuf* origCin = std::cin.rdbuf(mockInput.rdbuf());

    std::ostringstream mockOutput;
    std::streambuf* oldCout = std::cout.rdbuf(mockOutput.rdbuf());

    calculatorCommandParser.Handle(mockInput, mockOutput);

    std::cin.rdbuf(origCin);
    std::cout.rdbuf(oldCout);

    std::string expectedOutput =
        "Added a variable: " + var + "\n"
        "Added a variable: " + var1 + "\n"
        "Added a function: " + func + "\n"
        "Added a function: " + func1 + "\n"
        "Xplus " + expectedValue + "\n"
        "Xplus1 " + expectedValue + "\n";

    REQUIRE(mockOutput.str() == expectedOutput);
}


TEST_CASE("Init func with let success") {
    Calculator calculator;
    CalculatorHandler calculatorCommandParser = CalculatorHandler(calculator);
    std::string let = "x";
    std::string func = "Xplus";
    std::string value = "1.23";

    std::istringstream mockInput(
        "let " + let + " = " + value + "\n"
        + "fn " + func + " = " + let + "\n"
        + "printfns"
    );
    std::streambuf* origCin = std::cin.rdbuf(mockInput.rdbuf());

    std::ostringstream mockOutput;
    std::streambuf* oldCout = std::cout.rdbuf(mockOutput.rdbuf());

    calculatorCommandParser.Handle(mockInput, mockOutput);

    std::cin.rdbuf(origCin);
    std::cout.rdbuf(oldCout);

    std::string expectedOutput =
        "Added a let: " + let + " = " + value + "\n"
        "Added a function: " + func + "\n"
        "Xplus = " + value + "\n";

    REQUIRE(mockOutput.str() == expectedOutput);
}

TEST_CASE("Test generated test program output") {

    // Сравнение полученного вывода с ожидаемым результатом
    std::ifstream mockInput("test_program.txt");
    std::ostringstream expectedOutput("test_output.txt");
    Calculator calculator;
    CalculatorHandler calculatorCommandParser = CalculatorHandler(calculator);
    std::streambuf* origCin = std::cin.rdbuf(mockInput.rdbuf());

    std::ostringstream mockOutput;
    std::streambuf* oldCout = std::cout.rdbuf(mockOutput.rdbuf());

    calculatorCommandParser.Handle(mockInput, mockOutput);
    std::cin.rdbuf(origCin);
    std::cout.rdbuf(oldCout);

    REQUIRE(mockOutput.str() == expectedOutput.str());
}
