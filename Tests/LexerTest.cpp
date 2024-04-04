#include <iostream>
#include <sstream>
#include <cassert>
#include "../Lex/include/Lexer.h"
using ctokens::TokType;

// Helper function to compare two vectors of tokens
bool compareTokenVectors(const std::vector<Token>& expected, const std::vector<Token>& actual) {
    if (expected.size() != actual.size())
        return false;

    for (size_t i = 0; i < expected.size(); ++i) {
        if (expected[i].getType() != actual[i].getType() || expected[i].getLexeme() != actual[i].getLexeme())
            return false;
    }

    return true;
}

// Test case for basic tokenization
void testBasicTokenization() {
    std::string input = "int main() { return 0; }";
    std::vector<Token> expectedTokens = {
            {TokType::KEYWORD, "int"},
            {TokType::IDENTIFIER, "main"},
            {TokType::BRACKET, "("},
            {TokType::BRACKET, ")"},
            {TokType::BRACKET, "{"},
            {TokType::KEYWORD, "return"},
            {TokType::INT_CONSTANT, "0"},
            {TokType::SPECIAL_SYMBOL, ";"},
            {TokType::BRACKET, "}"},
            {TokType::END_OF_FILE, ""}
    };

    Lexer lexer(input);
    lexer.tokenize();
    std::vector<Token> actualTokens = lexer.getTokens();

    assert(compareTokenVectors(expectedTokens, actualTokens));
    std::cout << "Test case for basic tokenization passed!" << std::endl;
}

// Test case for tokenization with preprocessor directive
void testPreprocessorDirectiveTokenization() {
    std::string input = "#include \"string.h\"";
    std::vector<Token> expectedTokens = {
            {TokType::PREPROCESSOR_DIRECTIVE, "#include"},
            {TokType::STRING, "string.h"},
            {TokType::END_OF_FILE, ""}
    };

    Lexer lexer(input);
    lexer.tokenize();
    std::vector<Token> actualTokens = lexer.getTokens();
    assert(compareTokenVectors(expectedTokens, actualTokens));
    std::cout << "Test case for tokenization with preprocessor directive passed!" << std::endl;
}

// Test case for tokenization with arithmetic operators
void testArithmeticOperatorTokenization() {
    std::string input = "x = y + 5 * z;";
    std::vector<Token> expectedTokens = {
            {TokType::IDENTIFIER, "x"},
            {TokType::ASSIGNMENT_OPERATOR, "="},
            {TokType::IDENTIFIER, "y"},
            {TokType::ARITHMETIC_OPERATOR, "+"},
            {TokType::INT_CONSTANT, "5"},
            {TokType::ARITHMETIC_OPERATOR, "*"},
            {TokType::IDENTIFIER, "z"},
            {TokType::SPECIAL_SYMBOL, ";"},
            {TokType::END_OF_FILE, ""}
    };

    Lexer lexer(input);
    lexer.tokenize();
    std::vector<Token> actualTokens = lexer.getTokens();

    assert(compareTokenVectors(expectedTokens, actualTokens));
    std::cout << "Test case for tokenization with arithmetic operators passed!" << std::endl;
}

// Test case for tokenization with relational operators
void testRelationalOperatorTokenization() {
    std::string input = "if (x > y) { return true; }";
    std::vector<Token> expectedTokens = {
            {TokType::KEYWORD, "if"},
            {TokType::BRACKET, "("},
            {TokType::IDENTIFIER, "x"},
            {TokType::RELATIONAL_OPERATOR, ">"},
            {TokType::IDENTIFIER, "y"},
            {TokType::BRACKET, ")"},
            {TokType::BRACKET, "{"},
            {TokType::KEYWORD, "return"},
            {TokType::KEYWORD, "true"},
            {TokType::SPECIAL_SYMBOL, ";"},
            {TokType::BRACKET, "}"},
            {TokType::END_OF_FILE, ""}
    };

    Lexer lexer(input);
    lexer.tokenize();
    std::vector<Token> actualTokens = lexer.getTokens();
    assert(compareTokenVectors(expectedTokens, actualTokens));
    std::cout << "Test case for tokenization with relational operators passed!" << std::endl;
}

// Test case for tokenization with invalid characters
void testInvalidCharacterTokenization() {
    std::string input = "int x = @;";
    std::vector<Token> expectedTokens = {
            {TokType::KEYWORD, "int"},
            {TokType::IDENTIFIER, "x"},
            {TokType::ASSIGNMENT_OPERATOR, "="},
            {TokType::INVALID_TOK, "@"},
            {TokType::SPECIAL_SYMBOL, ";"},
            {TokType::END_OF_FILE, ""}
    };

    Lexer lexer(input);
    lexer.tokenize();
    std::vector<Token> actualTokens = lexer.getTokens();

    assert(compareTokenVectors(expectedTokens, actualTokens));
    std::cout << "Test case for tokenization with invalid characters passed!" << std::endl;
}