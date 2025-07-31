from nfa_core import State, NFA
from nfa_simulator import simulate_nfa

# Create states
s0 = State()
s1 = State()

# Add transition on 'a'
s0.add_transition('a', s1)

# Define the NFA
nfa = NFA(start=s0, accept=s1)

# Test strings
test_cases = ["", "a", "aa", "b", "ab"]

for test in test_cases:
    result = simulate_nfa(nfa, test)
    print(f"Input: '{test}' → {'Accepted' if result else 'Rejected'}")
