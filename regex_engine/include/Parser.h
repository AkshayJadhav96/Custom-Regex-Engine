// include/Parser.h

#pragma once

#include "AST.h"
#include <string>
#include <vector>

class Parser {
public:
    // The main public method to parse a regex string into an AST
    std::unique_ptr<RegexNode> parse(const std::string& regex);

private:
    // Helper methods for the parsing pipeline
    std::vector<char> tokenize(const std::string& regex);
    std::vector<char> to_postfix(const std::vector<char>& tokens);
    std::unique_ptr<RegexNode> postfix_to_ast(const std::vector<char>& postfix);

    // Helper for operator precedence
    int precedence(char op);
};
