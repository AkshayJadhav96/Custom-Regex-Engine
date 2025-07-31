// include/Simulator.h

#pragma once

#include "NFA.h"
#include <string>

bool simulate(const NFA& nfa, const std::string& input_str);
