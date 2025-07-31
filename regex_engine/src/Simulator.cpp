// src/Simulator.cpp

#include "Simulator.h"
#include <unordered_set>
#include <stack>
#include <iostream>

namespace { // Anonymous namespace for helper functions

const char EPSILON = ' ';

// Calculates the epsilon closure for a set of states
std::unordered_set<std::shared_ptr<State>> epsilon_closure(
    const std::unordered_set<std::shared_ptr<State>>& states) {
    
    std::unordered_set<std::shared_ptr<State>> closure = states;
    std::stack<std::shared_ptr<State>> stack;

    for (const auto& state : states) {
        stack.push(state);
    }

    while (!stack.empty()) {
        auto s = stack.top();
        stack.pop();

        if (s->transitions.count(EPSILON)) {
            for (const auto& next_state : s->transitions.at(EPSILON)) {
                if (closure.find(next_state) == closure.end()) {
                    closure.insert(next_state);
                    stack.push(next_state);
                }
            }
        }
    }
    return closure;
}

// Calculates the set of states reachable on a given symbol
std::unordered_set<std::shared_ptr<State>> move(
    const std::unordered_set<std::shared_ptr<State>>& states, char symbol) {
    
    std::unordered_set<std::shared_ptr<State>> next_states;
    for (const auto& state : states) {
        if (state->transitions.count(symbol)) {
            for (const auto& next : state->transitions.at(symbol)) {
                next_states.insert(next);
            }
        }
    }
    return next_states;
}

} // end anonymous namespace

// Main simulation function
bool simulate(const NFA& nfa, const std::string& input_str) {
    std::unordered_set<std::shared_ptr<State>> current_states = 
        epsilon_closure({nfa.start});

    for (char symbol : input_str) {
        auto moved_states = move(current_states, symbol);
        current_states = epsilon_closure(moved_states);
    }

    // Check if any of the final states is the accept state
    return current_states.count(nfa.accept) > 0;
}
