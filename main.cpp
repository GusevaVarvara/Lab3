#include <iostream>
#include "FiniteAutomaton.h"
#include "SubstringSearch.h"

int main() {
    std::string substring, inputString;
    std::cout << "Enter the substring: ";
    std::cin >> substring;

    SubstringSearch substringSearch(substring);

    std::cout << "Enter the input string: ";
    std::cin >> inputString;

    substringSearch.searchSubstring(inputString);

    return 0;
}
