# CMakeLists.txt

# Set the minimum required version of CMake
cmake_minimum_required(VERSION 3.10)

# Set the project name and specify C++
project(RegexEngine VERSION 1.0 LANGUAGES CXX)

# Set the C++ standard to C++17 (good for smart pointers)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add an executable target named "regex_engine"
# It will be built from the source files listed here
add_executable(regex_engine src/main.cpp src/Parser.cpp src/NfaBuilder.cpp src/Simulator.cpp)

# Tell the compiler where to find header files (.h)
target_include_directories(regex_engine PUBLIC include)
