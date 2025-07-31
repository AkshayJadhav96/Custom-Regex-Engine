// include/NfaBuilder.h

#pragma once

#include "AST.h"
#include "NFA.h"
#include <memory>

// Main function to build an NFA from an AST
std::unique_ptr<NFA> build_nfa_from_ast(const RegexNode* node);