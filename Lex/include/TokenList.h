//
// Created by vivekdagar on 3/30/24.
//

#ifndef UNTITLED1_TOKENLIST_H
#define UNTITLED1_TOKENLIST_H
#include <string>
#include <unordered_set>
#include <unordered_map>

namespace ctokens {

    // External sets of keywords and preprocessor directives
    extern std::unordered_set<std::string> keywords;
    extern std::unordered_set<std::string> preprocessorDirectives;

    // Enumeration for token types
    enum class TokType {
        KEYWORD,
        IDENTIFIER,
        END_OF_FILE,
        PREPROCESSOR_DIRECTIVE,
        ARITHMETIC_OPERATOR,
        RELATIONAL_OPERATOR,
        SPECIAL_SYMBOL,
        LOGICAL_OPERATOR,
        BITWISE_OPERATOR,
        ASSIGNMENT_OPERATOR,
        CHAR_CONST,
        STRING,
        OTHER_OPERATOR,
        FLOAT_CONSTANT,
        INT_CONSTANT,
        INVALID_TOK,
        BRACKET
    };

    // Helper class for printing token types
    class TokTypeHelper {
    public:
        static std::string print(TokType obj);
    };

} // namespace ctokens

#endif //UNTITLED1_TOKENLIST_H
