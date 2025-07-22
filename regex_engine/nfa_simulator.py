from typing import Set
from nfa_core import State, NFA

def epsilon_closure(states: Set[State]) -> Set[State]:
    ep_closure = set(states)
    stack = list(states)
    while stack:
        state = stack.pop()
        for next_state in state.transitions.get('ε', []):
            if next_state not in ep_closure:
                ep_closure.add(next_state)
                stack.append(next_state)
    return ep_closure


def move(states: Set[State], symbol: str) -> Set[State]:
    next_states = set()
    for state in states:
        if symbol in state.transitions:
            next_states.update(state.transitions[symbol])
    return next_states


def simulate_nfa(nfa: NFA, input_str: str) -> bool:
    current_states = epsilon_closure({nfa.start})
    for symbol in input_str:
        next_states = move(current_states, symbol)
        current_states = epsilon_closure(next_states)
        if not current_states:
            return False
    return nfa.accept in current_states
    # return any(state in nfa.accept_states for state in current_states)
