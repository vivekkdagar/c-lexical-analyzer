//
// Created by vivekdagar on 3/30/24.
//

#include <utility>
#include <iomanip>

#include "../include/Token.h"

Token::Token(ctokens::TokType type, std::string lexeme) : type(type), lexeme(std::move(lexeme)) {}

ctokens::TokType Token::getType() const {
    return type;
}

const std::string &Token::getLexeme() const {
    return lexeme;
}

std::ostream &operator<<(std::ostream &os, const Token &token) {
    os << std::setw(12) << std::left << ctokens::TokTypeHelper::print(token.getType())
    << "| " << token.getLexeme() << '\n';
    return os;
}
