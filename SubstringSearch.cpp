#include "SubstringSearch.h"

SubstringSearch::SubstringSearch(const std::string& substring)
    : automaton({ 0, 1 }, {}, {}, { static_cast<int>(substring.length()) }, 0) {
    for (size_t i = 0; i < substring.length(); ++i) {
        automaton.processInput(substring[i]);
        automaton.updateTransitions({ static_cast<int>(i), substring[i] }, i + 1);
    }
}

bool SubstringSearch::searchSubstring(const std::string& input) {
    automaton.reset();

    for (char ch : input) {
        automaton.processInput(ch);
        if (automaton.isAcceptingState()) {
            std::cout << "The substring is found!" << std::endl;
            return true;
        }
    }

    std::cout << "The substring is not found." << std::endl;
    return false;
}