// include/AST.h

#pragma once // Prevents this header from being included multiple times

#include <memory>
#include <string>

struct RegexNode {
    std::string value; // e.g., '*', '|', or a literal character
    std::unique_ptr<RegexNode> left;
    std::unique_ptr<RegexNode> right;

    // Constructor to easily create a node
    RegexNode(std::string val) : value(val), left(nullptr), right(nullptr) {}
};
