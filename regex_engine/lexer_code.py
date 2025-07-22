def tokenize(regex: str) -> list:
    tokens = []
    prev = None

    for char in regex:
        if prev and (prev not in '(|' and char not in '|)*+?'):
            tokens.append('.')  # implicit concatenation
        tokens.append(char)
        prev = char

    return tokens

# print("Tokenization complete. Tokens:", tokenize("int(def)*ghi+"))
