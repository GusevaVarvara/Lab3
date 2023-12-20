#pragma once

#include <string>
#include <vector>

class URLDFA {
public:
    URLDFA();
    void processInput(const std::string& input);
    void printURLs();

private:
    enum class State {
        Start,
        Scheme,
        Colon,
        Slash1,
        Slash2,
        Authority,
        Port,
        Path,
        Query,
        Fragment
    };

    State currentState;
    std::string currentURL;
    std::vector<std::string> URLs;

    void transition(State nextState);
};

