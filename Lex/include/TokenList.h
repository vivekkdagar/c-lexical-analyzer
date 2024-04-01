//
// Created by vivekdagar on 3/30/24.
//

#ifndef UNTITLED1_TOKENLIST_H
#define UNTITLED1_TOKENLIST_H

#include <vector>
#include <string>
namespace ctokens {

    extern std::vector<std::string> keywords;  // Done

    // Operators
    extern std::vector<std::string> arithOperators;     // Done
    extern std::vector<std::string> relaOperators; // Done
    extern std::vector<std::string> assignmentOperators; // Done
    extern std::vector<std::string> logicalOperators; // Done
    extern std::vector<std::string> bitwiseOperators; // Done
    extern std::vector<std::string> brackets; // Done
    extern std::vector<std::string> otherOperators;
    extern std::vector<char> whitespaces;
    extern std::vector<std::string> specialSymbols;

    extern std::vector<std::string> preprocessorDirectives;  // Done

    enum class TokType {
        KEYWORD,
        IDENTIFIER,
        END_OF_FILE,
        WHITESPACE,
        PREPROCESSOR_DIRECTIVE,
        ARITHMETIC_OPERATOR,
        RELATIONAL_OPERATOR,
        SPECIAL_SYMBOL,
        LOGICAL_OPERATOR,
        BITWISE_OPERATOR,
        ASSIGNMENT_OPERATOR,
        OTHER_OPERATOR,
        FLOAT_CONSTANT,
        INT_CONSTANT,
        INVALID_TOK,
        BRACKET
    };

    class TokTypeHelper {
    public:
        static std::string print(TokType obj);
    };

} // ctokens

#endif //UNTITLED1_TOKENLIST_H
