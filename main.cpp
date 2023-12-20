#include "urldfa.h"
#include <iostream>

int main() {
    URLDFA urlDFA;

    std::cout << "Enter text (type 'end' on a new line to finish input):\n";

    std::string inputLine;
    do {
        std::getline(std::cin, inputLine);
        urlDFA.processInput(inputLine);
    } while (inputLine != "end");

    urlDFA.printURLs();

    return 0;
}




