from lexer_code import tokenize
from ast_code import RegexNode

precedence = {
    '|': 1,
    '.': 2,
    '*': 3,
    '+': 3,
    '?': 3
}


def to_postfix(tokens):
    output = []
    stack = []
    for token in tokens:
        if token == '(':
            stack.append(token)
        elif token == ')':
            while stack and stack[-1] != '(':
                output.append(stack.pop())
            stack.pop()
        elif token in precedence:
            while stack and stack[-1] in precedence and precedence[token] <= precedence[stack[-1]]:
                output.append(stack.pop())
            stack.append(token)
        else:
            output.append(token)
        # print(stack, output)  # Debugging line to trace stack and output
    while stack:
        output.append(stack.pop())
    return output


def postfix_to_ast(postfix):
    stack = []
    for token in postfix:
        if token in {'*', '+', '?'}:
            node = stack.pop()
            stack.append(RegexNode(token, left=node))
        elif token in {'.', '|'}:
            right = stack.pop()
            left = stack.pop()
            stack.append(RegexNode(token, left, right))
        else:
            stack.append(RegexNode(token))
    return stack[0] if stack else None

def parse_regex(regex):
    tokens = tokenize(regex)
    print("Tokenization complete. Tokens:", tokens)
    postfix = to_postfix(tokens)
    print("Postfix conversion complete. Postfix:", postfix)
    ast = postfix_to_ast(postfix)
    return ast

# print(parse_regex("a(a+b)*b"))
