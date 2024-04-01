//
// Created by vivekdagar on 3/30/24.
//

#ifndef UNTITLED1_TOKEN_H
#define UNTITLED1_TOKEN_H

#include "TokenList.h"
#include <vector>
#include <string>
#include <iostream>
using std::vector, std::string, std::cerr;

class Token {
    ctokens::TokType type;
    string lexeme;
public:
    Token(ctokens::TokType type, const string &lexeme);

    ctokens::TokType getType() const;

    const string &getLexeme() const;

    friend std::ostream &operator<<(std::ostream &os, const Token &token);
};


#endif //UNTITLED1_TOKEN_H
