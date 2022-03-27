#ifndef TURINGMACHINE_H
#define TURINGMACHINE_H

#include <string>
#include <vector>
#include <map>

class TuringMachine {
public:
	TuringMachine(std::string);
	std::string run(std::string, bool = false);

private:
	std::string inputAlphabet, activeState;
	// Using < as move left key, < - move right, H - Halt, X - Error
	std::string allowedActions = "<>HX";
	std::vector <std::string> states;
	std::map<std::pair<std::string, char>, std::tuple<char,char,std::string>> functionResults;

};
#endif // TURINGMACHINE_H