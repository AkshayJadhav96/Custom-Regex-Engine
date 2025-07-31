// src/main.cpp

#include "Parser.h"
#include "NfaBuilder.h"
#include "Simulator.h"
#include <iostream>
#include <string>

int main() {
    std::string regex_pattern;
    std::string test_string;

    std::cout << "Enter regex pattern: ";
    std::getline(std::cin, regex_pattern);

    std::cout << "Enter test string: ";
    std::getline(std::cin, test_string);

    try {
        // 1. Parse the regex string into an AST
        Parser parser;
        std::unique_ptr<RegexNode> ast = parser.parse(regex_pattern);

        // 2. Build an NFA from the AST
        std::unique_ptr<NFA> nfa = build_nfa_from_ast(ast.get());

        // 3. Simulate the NFA with the test string
        bool is_match = simulate(*nfa, test_string);

        // 4. Report the result
        if (is_match) {
            std::cout << "\n✅ Match!" << std::endl;
        } else {
            std::cout << "\n❌ No match." << std::endl;
        }

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
