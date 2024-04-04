//
// Created by vivekdagar on 4/4/24.
//
// test_TokenList.cpp

#include <cassert>
#include "../Lex/include/TokenList.h"

class TokenListTester {
public:
    static void test() {
        testKeywordSet();
        testPreprocessorDirectiveSet();
        testTokTypeHelperPrintFunction();
    }

private:
    static void testKeywordSet() {
        assert(ctokens::keywords.find("int") != ctokens::keywords.end());
        assert(ctokens::keywords.find("if") != ctokens::keywords.end());
        assert(ctokens::keywords.find("while") != ctokens::keywords.end());
        assert(ctokens::keywords.find("return") != ctokens::keywords.end());
        assert(ctokens::keywords.find("class") == ctokens::keywords.end()); // Not a keyword
    }

    static void testPreprocessorDirectiveSet() {
        assert(ctokens::preprocessorDirectives.find("#include") != ctokens::preprocessorDirectives.end());
        assert(ctokens::preprocessorDirectives.find("#define") != ctokens::preprocessorDirectives.end());
        assert(ctokens::preprocessorDirectives.find("#ifdef") != ctokens::preprocessorDirectives.end());
        assert(ctokens::preprocessorDirectives.find("#pragma") != ctokens::preprocessorDirectives.end());
        // assert(ctokens::preprocessorDirectives.find("#warning") == ctokens::preprocessorDirectives.end()); // Not a preprocessor directive
    }

    static void testTokTypeHelperPrintFunction() {
        // Test common token types
        assert(ctokens::TokTypeHelper::print(ctokens::TokType::KEYWORD) == "KEYWORD");
        assert(ctokens::TokTypeHelper::print(ctokens::TokType::IDENTIFIER) == "IDENTIFIER");

        // Test numeric constants
        assert(ctokens::TokTypeHelper::print(ctokens::TokType::INT_CONSTANT) == "INT_CONSTANT");
        assert(ctokens::TokTypeHelper::print(ctokens::TokType::FLOAT_CONSTANT) == "FLOAT_CONSTANT");

        // Test operators
        assert(ctokens::TokTypeHelper::print(ctokens::TokType::ARITHMETIC_OPERATOR) == "ARITHMETIC_OPERATOR");
        assert(ctokens::TokTypeHelper::print(ctokens::TokType::RELATIONAL_OPERATOR) == "RELATIONAL_OPERATOR");

        // Test special cases
        assert(ctokens::TokTypeHelper::print(ctokens::TokType::INVALID_TOK) == "INVALID_TOK");
        assert(ctokens::TokTypeHelper::print(ctokens::TokType::STRING) == "STRING");
        assert(ctokens::TokTypeHelper::print(static_cast<ctokens::TokType>(100)) == "UNKNOWN"); // Unknown type
    }
};