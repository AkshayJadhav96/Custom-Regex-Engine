// src/Parser.cpp

#include "Parser.h"
#include <stdexcept>
#include <stack>

// Main orchestrator method
std::unique_ptr<RegexNode> Parser::parse(const std::string& regex) {
    if (regex.empty()) {
        return nullptr;
    }
    auto tokens = tokenize(regex);
    auto postfix = to_postfix(tokens);
    return postfix_to_ast(postfix);
}

// Tokenizer with implicit concatenation
std::vector<char> Parser::tokenize(const std::string& regex) {
    std::vector<char> tokens;
    for (size_t i = 0; i < regex.length(); ++i) {
        char token = regex[i];
        
        // Add implicit concatenation '.' where needed
        if (i > 0) {
            char prev = regex[i-1];
            if ((isalnum(prev) || prev == ')' || prev == '*' || prev == '+' || prev == '?') && 
                (isalnum(token) || token == '(')) {
                tokens.push_back('.');
            }
        }
        tokens.push_back(token);
    }
    return tokens;
}

// Helper function to get operator precedence
int Parser::precedence(char op) {
    switch (op) {
        case '|': return 1;
        case '.': return 2; // Concatenation
        case '*': return 3; // Kleene Star
        case '+': return 3; // Kleene Plus
        case '?': return 3; // Optional
    }
    return 0; // For non-operators
}

// Converts infix token stream to postfix using Shunting-yard
std::vector<char> Parser::to_postfix(const std::vector<char>& tokens) {
    std::vector<char> output;
    std::stack<char> op_stack;

    for (char token : tokens) {
        if (isalnum(token)) {
            output.push_back(token);
        } else if (token == '(') {
            op_stack.push(token);
        } else if (token == ')') {
            while (!op_stack.empty() && op_stack.top() != '(') {
                output.push_back(op_stack.top());
                op_stack.pop();
            }
            op_stack.pop(); // Pop '('
        } else { // Operator
            while (!op_stack.empty() && op_stack.top() != '(' && 
                   precedence(op_stack.top()) >= precedence(token)) {
                output.push_back(op_stack.top());
                op_stack.pop();
            }
            op_stack.push(token);
        }
    }

    // Pop remaining operators from stack to output
    while (!op_stack.empty()) {
        output.push_back(op_stack.top());
        op_stack.pop();
    }

    return output;
}

// Builds an AST from a postfix expression
std::unique_ptr<RegexNode> Parser::postfix_to_ast(const std::vector<char>& postfix) {
    if (postfix.empty()) {
        return nullptr;
    }

    std::stack<std::unique_ptr<RegexNode>> node_stack;

    for (char token : postfix) {
        if (isalnum(token)) {
            // For a literal, create a leaf node and push it onto the stack
            node_stack.push(std::make_unique<RegexNode>(std::string(1, token)));
        } else {
            // For an operator, create a new node
            auto node = std::make_unique<RegexNode>(std::string(1, token));

            if (token == '*' || token == '+' || token == '?') {
                // Unary operators: pop one operand
                if (node_stack.empty()) throw std::runtime_error("Invalid regex expression");
                node->left = std::move(node_stack.top());
                node_stack.pop();
            } else {
                // Binary operators ('.', '|'): pop two operands
                if (node_stack.size() < 2) throw std::runtime_error("Invalid regex expression");
                node->right = std::move(node_stack.top());
                node_stack.pop();
                node->left = std::move(node_stack.top());
                node_stack.pop();
            }
            node_stack.push(std::move(node));
        }
    }

    if (node_stack.size() != 1) {
        throw std::runtime_error("Malformed regex expression");
    }

    // The last node on the stack is the root of the AST
    return std::move(node_stack.top());
}
