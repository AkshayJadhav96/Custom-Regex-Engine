from ast_code import RegexNode
from nfa_core import State, NFA

def build_nfa(node: RegexNode) -> NFA:
    if node is None:
        return None

    # Case 1: Literal character
    if node.value not in {'.', '|', '*', '+', '?'}:
        start = State()
        accept = State()
        start.add_transition(node.value, accept)
        return NFA(start, accept)

    # Case 2: Concatenation
    if node.value == '.':
        left_nfa = build_nfa(node.left)
        right_nfa = build_nfa(node.right)
        left_nfa.accept.add_transition('ε', right_nfa.start)
        return NFA(left_nfa.start, right_nfa.accept)

    # Case 3: Alternation (Union)
    if node.value == '|':
        start = State()
        accept = State()
        left_nfa = build_nfa(node.left)
        right_nfa = build_nfa(node.right)

        start.add_transition('ε', left_nfa.start)
        start.add_transition('ε', right_nfa.start)

        left_nfa.accept.add_transition('ε', accept)
        right_nfa.accept.add_transition('ε', accept)

        return NFA(start, accept)

    # Case 4: Kleene Star
    if node.value == '*':
        start = State()
        accept = State()
        sub_nfa = build_nfa(node.left)

        start.add_transition('ε', sub_nfa.start)
        start.add_transition('ε', accept)
        sub_nfa.accept.add_transition('ε', sub_nfa.start)
        sub_nfa.accept.add_transition('ε', accept)

        return NFA(start, accept)

    # Case 5: Plus
    if node.value == '+':
        start = State()
        accept = State()
        sub_nfa = build_nfa(node.left)

        start.add_transition('ε', sub_nfa.start)
        sub_nfa.accept.add_transition('ε', sub_nfa.start)
        sub_nfa.accept.add_transition('ε', accept)

        return NFA(start, accept)

    # Case 6: Optional
    if node.value == '?':
        start = State()
        accept = State()
        sub_nfa = build_nfa(node.left)

        start.add_transition('ε', sub_nfa.start)
        start.add_transition('ε', accept)
        sub_nfa.accept.add_transition('ε', accept)

        return NFA(start, accept)

    raise ValueError(f"Unknown node value: {node.value}")

