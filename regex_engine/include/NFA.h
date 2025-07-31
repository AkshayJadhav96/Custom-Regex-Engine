// include/NFA.h

#pragma once

#include <memory>
#include <unordered_map>
#include <vector>

struct State {
    // A map from an input symbol to a list of possible next states.
    // The key ' ' (space) can represent an epsilon (ε) transition.
    std::unordered_map<char, std::vector<std::shared_ptr<State>>> transitions;
};

struct NFA {
    std::shared_ptr<State> start;
    std::shared_ptr<State> accept;
};
