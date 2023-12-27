#pragma once
#include "FiniteAutomaton.h"

class SubstringSearch {
private:
    FiniteAutomaton<int, char> automaton;

public:
    SubstringSearch(const std::string& substring);

    bool searchSubstring(const std::string& input);
};

