//
// Created by vivekdagar on 3/30/24.
//

#include "../include/Token.h"

Token::Token(ctokens::TokType type, const string &lexeme) : type(type), lexeme(lexeme) {}

ctokens::TokType Token::getType() const {
    return type;
}

const string &Token::getLexeme() const {
    return lexeme;
}

std::ostream &operator<<(std::ostream &os, const Token &token) {
    os << " lexeme: " << token.lexeme;
    return os;
}
