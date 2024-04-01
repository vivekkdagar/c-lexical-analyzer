//
// Created by vivekdagar on 3/30/24.
//

#include <string>
#include "../include/TokenList.h"

namespace ctokens {
    // Done
    std::vector<std::string> keywords = { "auto", "break", "case", "char", "const", "continue", "default",
                                          "do", "double", "else", "enum", "extern", "float", "for", "goto",
                                          "if", "inline", "int", "long", "register", "restrict", "return", "short",
                                          "signed", "sizeof", "static", "struct", "switch", "typedef", "union",
                                          "unsigned", "void", "volatile", "while" ,"sizeof"};

    // Operators
    std::vector<std::string> arithOperators = {"+", "-", "*", "/", "%", "++", "--"};
    std::vector<std::string> relaOperators = {"==", "!=", ">", "<", "<=", ">="};
    std::vector<std::string> assignmentOperators = {"=", "+=", "-=", "*=", "/=", "%=", "&=", "|=", "^=", "<<=", ">>="};
    std::vector<std::string> bitwiseOperators = {"&", "|", "^", "~", "<<", ">>"};

    std::vector<std::string> brackets = {"(", ")", "{", "}", "[", "]"};     // Done

    std::vector<char> whitespaces = {' ', '\t', '\n', '\r', '\f', '\v'};

    std::vector<std::string> preprocessorDirectives = {"#define", "#include", "#ifdef", "#ifndef", "#endif",
                                                       "#if", "#else", "#elif", "#pragma", "#error",
                                                       "#warning", "#line", "#undef"};      // Done

    std::vector<std::string> otherOperators = {"?", ":", "&", "*", ".", "->"};
    std::vector<std::string> specialSymbols = {";", ",", "'", "\"", "#", "...", "//", "/*", "*/"};
    // Vector of logical operators
    std::vector<std::string> logicalOperators = {"&&", "||", "!"};

    std::string TokTypeHelper::print(TokType obj) {
        if(obj == TokType::KEYWORD) {
            return "KEYWORD";
        } else if(obj == TokType::IDENTIFIER) {
            return "IDENTIFIER";
        } else if(obj == TokType::PREPROCESSOR_DIRECTIVE) {
            return "PREPROCESSOR_DIRECTIVE";
        } else if(obj == TokType::BRACKET) {
            return "BRACKET";
        } else if(obj == TokType::INT_CONSTANT) {
            return "INT_CONSTANT";
        } else if(obj == TokType::FLOAT_CONSTANT) {
            return "FLOAT_CONSTANT";
        } else if(obj == TokType::ARITHMETIC_OPERATOR)
            return "ARITHMETIC_OP";
        else if(obj == TokType::RELATIONAL_OPERATOR)
            return "RELATIONAL_OP";
        else if(obj == TokType::ASSIGNMENT_OPERATOR)
            return "ASSIGNMENT_OP";
        else if(obj == TokType::BITWISE_OPERATOR)
            return "BITWISE_OP";
        else if(obj == TokType::LOGICAL_OPERATOR)
            return "LOGICAL_OP";
        else if(obj == TokType::SPECIAL_SYMBOL)
            return "SPECIAL_SYMBOL";
        else if(obj == TokType::OTHER_OPERATOR)
            return "OTHER_OPERATOR";
        else if(obj == TokType::INVALID_TOK)
            return "INVALID_TOK";
        return "END OF FILE";
    }
} // ctokens