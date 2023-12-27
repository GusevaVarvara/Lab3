#pragma once

#include <iostream>
#include <map>
#include <unordered_set>
#include <vector>

struct PairComparator {
    template <class T1, class T2>
    bool operator()(const std::pair<T1, T2>& lhs, const std::pair<T1, T2>& rhs) const {
        return lhs < rhs;
    }
};

template <typename State, typename Alphabet>
class FiniteAutomaton {
private:

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
