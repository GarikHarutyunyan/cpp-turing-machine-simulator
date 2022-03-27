#include <string>
#include <iostream>
#include "TuringMachine.h"

int main() {
    std::string input, output;
    std::string plusConfig = "Plus.txt";

    try {
        TuringMachine adder(plusConfig);
        input = "1111*11111"; 
        output = adder.run(input);// 3+4
        std::cout<<"3+4"<< std::endl;
        std::cout << input << "  =  " << output << std::endl << std::endl;

        input = "111111111*111111"; // 8+5
        std::cout << "8+5" << std::endl;
        output = adder.run(input);
        std::cout << input << "  =  " << output << std::endl << std::endl;

        input = "111*11111111111"; // 2+10
        std::cout << "2+10" << std::endl;
        output = adder.run(input);
        std::cout << input << "  =  " << output << std::endl << std::endl;

        input = "11*11111"; // 1+4
        output = adder.run(input);
        std::cout << "1+4" << std::endl;
        std::cout << input << "  =  " << output << std::endl << std::endl;

        input = "1*111"; // 0+2
        output = adder.run(input);
        std::cout << "0+2" << std::endl;
        std::cout << input << "  =  " << output << std::endl << std::endl;

        input = "1*1"; // 0+0
        output = adder.run(input);
        std::cout << "0+0" << std::endl;
        std::cout << input << "  =  " << output << std::endl << std::endl;

        //In debug mode for demostration
        input = "111111111*111111"; // 8+5
        bool debugMode = true;
        std::cout << "8+5 :: DEBUGGING" << std::endl;
        output = adder.run(input, debugMode);
        std::cout << input << "  =  " << output << std::endl << std::endl;

    }
    catch (std::invalid_argument& err) {
        std::cerr << err.what() << std::endl;
    }

    return 0;
}