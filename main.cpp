#include <iostream>
#include <map>
#include <unordered_set>
#include <vector>

template <typename State, typename Alphabet>
class FiniteAutomaton {
private:
private:
    struct PairComparator {
        template <class T1, class T2>
        bool operator()(const std::pair<T1, T2>& lhs, const std::pair<T1, T2>& rhs) const {
            return lhs < rhs;
        }
    };

    std::map<std::pair<State, Alphabet>, State, PairComparator> transitions;
    std::unordered_set<State> acceptingStates;
    State currentState;

public:
    FiniteAutomaton(const std::vector<State>& states,
        const std::vector<Alphabet>& alphabet,
        const std::map<std::pair<State, Alphabet>, State, PairComparator>& transitions,
        const std::unordered_set<State>& acceptingStates,
        const State& initialState)
        : transitions(transitions), acceptingStates(acceptingStates), currentState(initialState) {}

    void processInput(const Alphabet& input) {
        auto it = transitions.find({ currentState, input });
        if (it != transitions.end()) {
            currentState = it->second;
        }
        else {
            currentState = 0;
        }
    }

    void updateTransitions(const std::pair<State, Alphabet>& key, const State& value) {
        transitions[key] = value;
    }

    bool isAcceptingState() const {
        return acceptingStates.find(currentState) != acceptingStates.end();
    }

    void reset() {
        currentState = 0; 
    }
};

class SubstringSearch {
private:
    FiniteAutomaton<int, char> automaton;

public:
    SubstringSearch(const std::string& substring)
        : automaton({ 0, 1 }, {}, {}, { static_cast<int>(substring.length()) }, 0) {
        for (size_t i = 0; i < substring.length(); ++i) {
            automaton.processInput(substring[i]);
            automaton.updateTransitions({ static_cast<int>(i), substring[i] }, i + 1);
        }
    }

    bool searchSubstring(const std::string& input) {
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
};

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





