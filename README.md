# Custom Regular Expression Engine in C++

A from-scratch implementation of a regular expression engine based on Thompson's Construction algorithm, which converts a regex pattern into a Nondeterministic Finite Automaton (NFA).

This repository contains two versions of the engine:
1.  **C++ Implementation**: A performance-oriented version with manual memory management using modern C++ features.
2.  **Python Implementation**: The original prototype, demonstrating the core logic in a high-level language.

---

## Features

The engine supports the following core regex operators:
-   **Concatenation**: `ab`
-   **Union (OR)**: `a|b`
-   **Kleene Star**: `a*` (zero or more)
-   **Kleene Plus**: `a+` (one or more)
-   **Optional**: `a?` (zero or one)
-   **Grouping**: `()` for precedence

---

## How It Works

The engine follows the classic compiler theory pipeline to process regex patterns:

1.  **Tokenization**: The input regex string is scanned and converted into a sequence of tokens. Implicit concatenation operators (`.`) are inserted where needed (e.g., `ab` becomes `a.b`).

2.  **Infix to Postfix Conversion**: The token stream is converted from standard infix notation to postfix (Reverse Polish Notation) using the **Shunting-yard algorithm**. This makes it easier to build the syntax tree.

3.  **AST Construction**: A postfix expression is used to build an Abstract Syntax Tree (AST), which represents the structure of the regular expression.

4.  **NFA Construction**: The AST is traversed recursively to build an equivalent Nondeterministic Finite Automaton (NFA) using **Thompson's Construction** algorithm. Each node in the AST corresponds to a specific NFA fragment.

5.  **Simulation**: The generated NFA is simulated against an input string. It processes the string one character at a time, keeping track of all possible current states, to determine if the string is accepted by the automaton.

---

## Project Structure
```
.
├── regex_engine/          # C++ Implementation
│   ├── src/
│   ├── include/
│   └── CMakeLists.txt
├── regex_engine_python/   # Python Implementation
│   └── ...
└── README.md
```


---

## How to Build and Run (C++)

### Prerequisites
- A C++17 compliant compiler (g++, Clang, etc.)
- CMake (version 3.10 or higher)

### Build Steps
From the root directory of the project:
```bash
# 1. Create a build directory delete the one you cloned from this github
mkdir build
cd build

# 2. Configure the project with CMake
cmake ..

# 3. Compile the project
cmake --build .
```

### Run

```bash
# From inside the build/ directory
./regex_engine
```

The program will then prompt you to enter a regex pattern and a test string.

## How to Run (Python)

```bash
# Navigate to the Python project directory
cd regex_engine_python

# Run the main script
python main.py
```


