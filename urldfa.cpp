#include "urldfa.h"
#include <iostream>

URLDFA::URLDFA() : currentState(State::Start) {}

void URLDFA::processInput(const std::string& input) {
    for (char ch : input) {
        switch (currentState) {

        case State::Start:
            if (isalpha(ch)) {
                transition(State::Scheme);
                currentURL += ch;
            }
            break;


        case State::Scheme:
            if (isalpha(ch) || isdigit(ch) || ch == '.' || ch == '-' || ch == '+') {
                currentURL += ch;
            }
            else if (ch == ':') {
                transition(State::Colon);
                currentURL += ch;
            }
            else if (ch == ' ' || ch == '\n' || ch == '\t') {
                currentURL.clear();
                currentState = State::Start;
            }
            else {
                currentURL.clear();
                currentState = State::Start;
            }
            break;


        case State::Colon:
            if (ch == '/') {
                transition(State::Slash1);
                currentURL += ch;
            }
            else if (ch == ' ' || ch == '\n' || ch == '\t') {
                currentURL.clear();
                currentState = State::Start;
            }
            else {
                currentURL.clear();
                currentState = State::Start;
            }
            break;


        case State::Slash1:
            if (ch == '/') {
                transition(State::Slash2);
                currentURL += ch;
            }
            else if (ch == ' ' || ch == '\n' || ch == '\t') {
                currentURL.clear();
                currentState = State::Start;
            }
            else {
                currentURL.clear();
                currentState = State::Start;
            }
            break;


        case State::Slash2:
            if (isalpha(ch)) {
                transition(State::Authority);
                currentURL += ch;
            }
            else if (ch == ' ' || ch == '\n' || ch == '\t') {
                currentURL.clear();
                currentState = State::Start;
            }
            else {
                currentURL.clear();
                currentState = State::Start;
            }
            break;


        case State::Authority:
            if (isalnum(ch) || isdigit(ch) || ch == '.' || ch == '-' || ch == '_' || ch == '@' || ch == '=') {
                currentURL += ch;
            }
            else if (ch == ':') {
                transition(State::Port);
                currentURL += ch;
            }
            else if (ch == '/') {
                transition(State::Path);
                currentURL += ch;
            }
            else if (ch == '?') {
                transition(State::Query);
                currentURL += ch;
            }
            else if (ch == '#') {
                transition(State::Fragment);
                currentURL += ch;
            }
            else if (ch == ' ' || ch == '\n' || ch == '\t') {
                currentURL.clear();
                currentState = State::Start;
            }
            else {
                currentURL.clear();
                currentState = State::Start;
            }
            break;


        case State::Port:
            if (isdigit(ch)) {
                currentURL += ch;
            }
            else if (ch == '/') {
                transition(State::Path);
                currentURL += ch;
            }
            else if (ch == '?') {
                transition(State::Query);
                currentURL += ch;
            }
            else if (ch == '#') {
                transition(State::Fragment);
                currentURL += ch;
            }
            else if (ch == ' ' || ch == '\n' || ch == '\t') {
                currentURL.clear();
                currentState = State::Start;
            }
            else {
                currentURL.clear();
                currentState = State::Start;
            }
            break;


        case State::Path:
            if (isalnum(ch) || isdigit(ch) || ch == ':' || ch == '@' || ch == '-' || ch == '/' || ch == '=') {
                currentURL += ch;
            }
            else if (ch == '?') {
                transition(State::Query);
                currentURL += ch;
            }
            else if (ch == '#') {
                transition(State::Fragment);
                currentURL += ch;
            }
            else if (ch == ' ' || ch == '\n' || ch == '\t') {
                currentURL.clear();
                currentState = State::Start;
            }
            else {
                currentURL.clear();
                currentState = State::Start;
            }
            break;


        case State::Query:
            if (isalnum(ch) || isdigit(ch) || ch == ':' || ch == '@' || ch == '/' || ch == '?' || ch == '=') {
                currentURL += ch;
            }
            else if (ch == '#') {
                transition(State::Fragment);
                currentURL += ch;
            }
            else if (ch == ' ' || ch == '\n' || ch == '\t') {
                currentURL.clear();
                currentState = State::Start;
            }
            else {
                currentURL.clear();
                currentState = State::Start;
            }
            break;


        case State::Fragment:
            if (ch == ' ' || ch == '\n' || ch == '\t') {
                transition(State::Start);
            }
            else {
                currentURL += ch;
            }
            break;


        default:
            break;
        }
    }
    transition(State::Start);
}

void URLDFA::printURLs() {
    if (!URLs.empty()) {
        std::cout << "Found URLs:\n";
        for (const auto& url : URLs) {
            std::cout << url << '\n';
        }
    }
    else {
        std::cout << "No URLs found.\n";
    }
}

void URLDFA::transition(State nextState) {
    currentState = nextState;

    if (currentState == State::Start) {
        if (!currentURL.empty() && currentURL != "end") {
            URLs.push_back(currentURL);
            currentURL.clear();
        }
    }
}
