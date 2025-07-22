from lexer_code import tokenize
from parser_code import to_postfix, postfix_to_ast
from nfa_builder import build_nfa
from nfa_simulator import simulate_nfa

def run_regex_engine(regex: str, input_str: str):
    print(f"\n🔍 Input Regex: {regex}")
    print(f"🔢 Input String: {input_str}")

    # Step 1: Tokenize
    tokens = tokenize(regex)
    print("🧩 Tokens:", tokens)

    # Step 2: Postfix conversion
    postfix = to_postfix(tokens)
    print("📤 Postfix:", postfix)

    # Step 3: AST from Postfix
    ast = postfix_to_ast(postfix)
    print("🌳 AST built.")

    # Step 4: Build ε-NFA from AST
    nfa = build_nfa(ast)
    print("🏗️  NFA constructed.")

    # Step 5: Simulate the NFA
    result = simulate_nfa(nfa, input_str)
    print("✅ Match!" if result else "❌ No match.")

if __name__ == "__main__":
    # Sample input
    regex = input("Enter regex: ")
    string = input("Enter input string: ")
    run_regex_engine(regex, string)
