#include <string>
#include <iostream>
#include "TuringMachine.h"
#include "Utils.h"

int main() {
    int value1, value2;
    bool debugMode = true;
    std::string input, output;
    std::string plusConfig = "Plus.txt";
    std::string multiplicationConfig = "Multiplication.txt";
    std::string divisionConfig = "Division.txt";

    try {
        TuringMachine adder(plusConfig);

        //In debug mode for demostration
        value1 = 5;
        value2 = 5;

        input = Utils::to_unary(value1) + "*" + Utils::to_unary(value2);
        std::cout << value1 << "+" << value2 <<std::endl;
        output = adder.run(input);
        output = Utils::remove_spaces(output);
        std::cout << input << " = " << output << std::endl;
        std::cout << value1 << "+" << value2 << " = " << Utils::to_int(output) << std::endl << std::endl;


        TuringMachine multiplier(multiplicationConfig);

        value1 = 27;
        value2 = 15;

        input = Utils::to_unary(value1) + "*" + Utils::to_unary(value2);
        std::cout << value1<<"x"<<value2 << std::endl;
        output = multiplier.run(input);
        output = Utils::remove_spaces(output);
        std::cout << input << " = " << output << std::endl;
        std::cout << value1 << "x" << value2 << " = " << Utils::to_int(output) << std::endl << std::endl;


        TuringMachine divider(divisionConfig);

        value1 = 15;
        value2 = 7;

        input = Utils::to_unary(value1) + "*" + Utils::to_unary(value2);
        std::cout << value1 << "x" << value2 << std::endl;
        output = divider.run(input);
        output = Utils::remove_spaces(output);
        std::cout << input << " = " << output << std::endl;
        std::cout << value1 << "/" << value2 << " = " << Utils::to_int(output) << std::endl << std::endl;

    }
    catch (std::invalid_argument& err) {
        std::cerr << err.what() << std::endl;
        return 1;
    }

    return 0;
}