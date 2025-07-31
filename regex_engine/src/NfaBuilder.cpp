// src/NfaBuilder.cpp

#include "NfaBuilder.h"
#include <stdexcept>

// Recursively builds an NFA from an AST node
std::unique_ptr<NFA> build_nfa_from_ast(const RegexNode* node) {
    if (!node) {
        return nullptr;
    }

    // A space ' ' represents an epsilon transition
    const char EPSILON = ' ';

    // Case 1: Literal Character
    if (node->left == nullptr && node->right == nullptr) {
        auto nfa = std::make_unique<NFA>();
        nfa->start = std::make_shared<State>();
        nfa->accept = std::make_shared<State>();
        nfa->start->transitions[node->value[0]].push_back(nfa->accept);
        return nfa;
    }

    // Case 2: Concatenation '.'
    if (node->value == ".") {
        auto left_nfa = build_nfa_from_ast(node->left.get());
        auto right_nfa = build_nfa_from_ast(node->right.get());
        
        // Connect left's accept state to right's start state
        left_nfa->accept->transitions[EPSILON].push_back(right_nfa->start);
        
        auto nfa = std::make_unique<NFA>();
        nfa->start = left_nfa->start;
        nfa->accept = right_nfa->accept;
        return nfa;
    }

    // Case 3: Union '|'
    if (node->value == "|") {
        auto nfa = std::make_unique<NFA>();
        nfa->start = std::make_shared<State>();
        nfa->accept = std::make_shared<State>();
        
        auto left_nfa = build_nfa_from_ast(node->left.get());
        auto right_nfa = build_nfa_from_ast(node->right.get());

        nfa->start->transitions[EPSILON].push_back(left_nfa->start);
        nfa->start->transitions[EPSILON].push_back(right_nfa->start);

        left_nfa->accept->transitions[EPSILON].push_back(nfa->accept);
        right_nfa->accept->transitions[EPSILON].push_back(nfa->accept);
        
        return nfa;
    }

    // Case 4: Kleene Star '*'
    if (node->value == "*") {
        auto nfa = std::make_unique<NFA>();
        nfa->start = std::make_shared<State>();
        nfa->accept = std::make_shared<State>();

        auto sub_nfa = build_nfa_from_ast(node->left.get());

        nfa->start->transitions[EPSILON].push_back(sub_nfa->start);
        nfa->start->transitions[EPSILON].push_back(nfa->accept);

        sub_nfa->accept->transitions[EPSILON].push_back(sub_nfa->start);
        sub_nfa->accept->transitions[EPSILON].push_back(nfa->accept);
        
        return nfa;
    }
    
     // Case 5: Kleene Plus '+' (one or more)
    if (node->value == "+") {
        auto nfa = std::make_unique<NFA>();
        nfa->start = std::make_shared<State>();
        nfa->accept = std::make_shared<State>();

        auto sub_nfa = build_nfa_from_ast(node->left.get());

        nfa->start->transitions[EPSILON].push_back(sub_nfa->start); // Must enter sub-NFA

        sub_nfa->accept->transitions[EPSILON].push_back(sub_nfa->start); // Loop for more occurrences
        sub_nfa->accept->transitions[EPSILON].push_back(nfa->accept);   // Exit
        
        return nfa;
    }

    // Case 6: Optional '?' (zero or one)
    if (node->value == "?") {
        auto nfa = std::make_unique<NFA>();
        nfa->start = std::make_shared<State>();
        nfa->accept = std::make_shared<State>();

        auto sub_nfa = build_nfa_from_ast(node->left.get());

        nfa->start->transitions[EPSILON].push_back(sub_nfa->start); // Path for one occurrence
        nfa->start->transitions[EPSILON].push_back(nfa->accept);   // Path for zero occurrences

        sub_nfa->accept->transitions[EPSILON].push_back(nfa->accept); // Exit from one occurrence
        
        return nfa;
    }

    throw std::runtime_error("Unknown AST node value: " + node->value);
}
