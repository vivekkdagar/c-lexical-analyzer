cmake_minimum_required(VERSION 3.27)
project(untitled1)

set(CMAKE_CXX_STANDARD 17)

add_executable(untitled1 main.cpp
        Lex/source/TokenList.cpp
        Lex/include/TokenList.h
        Lex/source/Token.cpp
        Lex/include/Token.h
        Lex/source/Lexer.cpp
        Lex/include/Lexer.h)
