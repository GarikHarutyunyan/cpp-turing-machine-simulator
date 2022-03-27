#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include "TuringMachine.h"

TuringMachine::TuringMachine(std::string fileName) {
    std::string content;
    std::pair<std::string, char> key;
    std::tuple<char, char, std::string> value;
    std::ifstream configFile;
    configFile.open(fileName);
    int n = 0;

    // Reading file line by line
    while (getline(configFile, content)) {
        if (content.length() == 0) continue;

        // Check if input alphabet is not set yet
        if (this->inputAlphabet.length() == 0) {
            while (content.length()) {
                // Get the substring from start till ','
                std::string current = content.substr(0, content.find(","));

                if (current.length() == 1) {
                    this->inputAlphabet += current;
                    // Remove first 2 letters(first one is already added to input alphabet, second symbol is ',')
                    content.erase(0, 2);
                }
                else {
                    throw std::invalid_argument("Input Alphabet's element must contain only one symbol.");
                }
            }
        }
        // Check if states are not set yet
        else  if (this->states.size() == 0) {
            while (content.length()) {
                // Get the substring from start till ','
                std::string current = content.substr(0, content.find(","));
                this->states.push_back(current);
                content.erase(0, current.length() + 1);
            }
        }
        else {
            for (int i = 0; content.length(); i++) {
                // Get the substring from start till '|'
                std::string valueString = content.substr(0, content.find("|"));

                // Validation
                char outChar = valueString[0];
                char movement = valueString[2];
                std::string nextState = valueString.substr(valueString.find_last_of(",") + 1, valueString.length() - 1);
                bool isOutCharValid = this->inputAlphabet.find(outChar) < this->inputAlphabet.length();
                bool isMovementValid = this->allowedActions.find(movement) < this->allowedActions.length();
                bool isStateValid = distance(this->states.begin(), find(this->states.begin(), this->states.end(), nextState)) < this->states.size();
                
                if (!isOutCharValid) {
                    throw std::invalid_argument("Output Alphabet does not include the current character: " + outChar);
                }
                if (!isMovementValid) {
                    throw std::invalid_argument("Movement is not allowed : " + outChar);
                }
                if (!isStateValid) {
                    throw std::invalid_argument("Current state does not exist: " + nextState);
                }

                // Create key for map
                std::string state = this->states[n];
                char inputChar = this->inputAlphabet[i];
                key = std::make_pair(state, inputChar);

                // Create value for map
                value = std::make_tuple(outChar, movement, nextState);

                this->functionResults.insert({ key, value });
                content.erase(0, valueString.length() + 1); // +1 for removing "|" character
            }
            n++;
        }
    }

    configFile.close();
}

std::string TuringMachine::run(std::string input, bool debugMode) {
    char outChar, movement;
    std::string nextState;
    std::pair<std::string, char> key;
    std::tuple<char, char, std::string> functionResult;
    bool isRunning = true;

    this->activeState = this->states[0];
    int i = 0;

    while (isRunning) {
        std::string inputSymbol(1, input[i]);
        
        //Debugging
        if (debugMode) {
            std::cout << input << "     " <<this->activeState<< std::endl;
            std::cout << std::string(i, ' ') <<'^'<< std::string(input.length()-i, ' ')<<std::endl;
        }
        
        // For understanding out of range values as empty char 
        if (input[i] == '\0') {
            input[i] = ' ';
        }

        // Check if Input alphabet includes the current character
        if (this->inputAlphabet.find(input[i]) < this->inputAlphabet.length()) {
            key = std::make_pair(this->activeState, input[i]);
            functionResult = this->functionResults[key];
            // Get the substring from start till ','
            outChar = std::get<0>(functionResult);
            movement = std::get<1>(functionResult);
            nextState = std::get<2>(functionResult);

            input[i] = outChar;
            // Move the head of machine
            switch (movement) {
                case 'H': {
                    isRunning = false;
                    break;
                }
                case 'X': {
                    throw std::invalid_argument("Turing Machine Error");
                    break;
                }
                case '<': {
                    i--;
                    // For moving left from start position 
                    if (i < 0) {
                        i = 0;
                        input.insert(0, " ");
                    }
                    break;
                }
                case '>': {
                    i++;
                    break;
                }
            }
            this->activeState = nextState;
        }
        else {
            throw std::invalid_argument("Input Alphabet does not include the current character: " + inputSymbol);
        }
    }

    return input;
}