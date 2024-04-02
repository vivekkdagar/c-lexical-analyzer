//
// Created by vivekdagar on 3/30/24.
//

#ifndef UNTITLED1_TOKEN_H
#define UNTITLED1_TOKEN_H

#ifndef TOKEN_H
#define TOKEN_H

#include "TokenList.h"
#include <string>
#include <iostream>

class Token {
private:
    // Data members
    ctokens::TokType type;
    std::string lexeme;

public:
    // Constructor
    Token(ctokens::TokType type, std::string lexeme);

    // Accessors
    [[nodiscard]] ctokens::TokType getType() const;
    [[nodiscard]] const std::string &getLexeme() const;

    // Overloaded output operator
    friend std::ostream &operator<<(std::ostream &os, const Token &token);
};

#endif // TOKEN_H


#endif //UNTITLED1_TOKEN_H
