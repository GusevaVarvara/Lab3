#include <iostream>
#include <string>
#include <unordered_map>

class FiniteAutomaton {
private:
    std::unordered_map<char, int> transitions;
    std::string substring;

public:
    FiniteAutomaton(const std::string& substring) : substring(substring) {
        int currentState = 0;

        for (char ch : substring) {
            transitions[ch] = currentState++;
        }
    }

    void processInput(const std::string& input) {
        int currentState = 0;
        bool substringFound = false;

        for (char ch : input) {
            auto it = transitions.find(ch);

            if (it != transitions.end()) {
                currentState = it->second + 1;
            }
            else {
                currentState = 0;
            }

            if (currentState == substring.length()) {
                std::cout << "All characters in the substring are contained in the string.\n" << std::endl;
                substringFound = true;
                break;
            }
        }

        if (!substringFound) {
            std::cout << "Not all characters in a substring are contained in the string.\n" << std::endl;
        }
    }
};

int main() {
    std::cout << "Sample: \n";

    std::string substring1 = "abc";
    std::string inputString1 = "ababc";

    FiniteAutomaton automaton1(substring1);

    std::cout << "\nSubstring to search: " << substring1 << std::endl;
    std::cout << "Input string: " << inputString1 << std::endl;

    automaton1.processInput(inputString1);

    std::string inputString, substring;
    std::cout << "Enter the input string: ";
    std::getline(std::cin, inputString);
    std::cout << "Enter the substring: ";
    std::cin >> substring;

    FiniteAutomaton automaton(substring);

    automaton.processInput(inputString);

    return 0;
}




