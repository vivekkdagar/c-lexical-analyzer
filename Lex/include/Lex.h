//
// Created by vivekdagar on 4/2/24.
//

#ifndef UNTITLED1_LEX_H
#define UNTITLED1_LEX_H

#include <string>
#include <ostream>
#include "Token.h"

class Lex {
    vector<Token> processedOutput;
    std::string input;
public:
    explicit Lex(const string &input);

    void skipSpace();

    // Word related data
    void extractWord();

    // Numbers
    void extractNum();
    static bool isFloat(const string &str);

    // Advance to the next token
    void advance();

    // Bracket
    static bool isBracket(const char &currentChar);

    // Operators
    static bool isArithOp(const char &ch);
    static bool isOtherOp(const char &ch);

    friend std::ostream &operator<<(std::ostream &os, const Lex &lex);
    const vector<Token> &getProcessedOutput() const;
private:
    size_t pos;
};


#endif //UNTITLED1_LEX_H
