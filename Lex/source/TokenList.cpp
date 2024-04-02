//
// Created by vivekdagar on 3/30/24.
//

#include <string>
#include "../include/TokenList.h"

namespace ctokens {

    // Textual Data
    std::unordered_set<std::string> keywords = {"auto", "break", "case", "char",
                                                "const", "continue", "default",
                                                "do", "double", "else", "enum",
                                                "extern", "float", "for", "goto",
                                                "if", "inline", "int", "long",
                                                "register", "restrict", "return",
                                                "short", "signed", "sizeof",
                                                "static", "struct", "switch",
                                                "typedef", "union", "unsigned",
                                                "void", "volatile", "while",
                                                "sizeof"};

    std::unordered_set<std::string> preprocessorDirectives = {"#define", "#include", "#ifdef",
                                                              "#ifndef", "#endif", "#if",
                                                              "#else", "#elif", "#pragma", "#error",
                                                              "#warning", "#line", "#undef"};

    std::string TokTypeHelper::print(TokType obj) {
        switch (obj) {
            case TokType::KEYWORD:
                return "KEYWORD";
            case TokType::IDENTIFIER:
                return "IDENTIFIER";
            case TokType::PREPROCESSOR_DIRECTIVE:
                return "PREPROCESSOR_DIRECTIVE";
            case TokType::BRACKET:
                return "BRACKET";
            case TokType::INT_CONSTANT:
                return "INT_CONSTANT";
            case TokType::FLOAT_CONSTANT:
                return "FLOAT_CONSTANT";
            case TokType::ARITHMETIC_OPERATOR:
                return "ARITHMETIC_OP";
            case TokType::RELATIONAL_OPERATOR:
                return "RELATIONAL_OP";
            case TokType::ASSIGNMENT_OPERATOR:
                return "ASSIGNMENT_OP";
            case TokType::BITWISE_OPERATOR:
                return "BITWISE_OP";
            case TokType::LOGICAL_OPERATOR:
                return "LOGICAL_OP";
            case TokType::SPECIAL_SYMBOL:
                return "SPECIAL_SYMBOL";
            case TokType::OTHER_OPERATOR:
                return "OTHER_OPERATOR";
            case TokType::INVALID_TOK:
                return "INVALID_TOK";
            case TokType::CHAR_CONST:
                return "CHAR_CONST";
            case TokType::STRING:
                return "STRING";
            case TokType::END_OF_FILE:
                return "END OF FILE";
            default:
                return "UNKNOWN"; // Handle unknown token types
        }
    }
} // ctokens