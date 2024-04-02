//
// Created by vivekdagar on 4/2/24.
//

#ifndef UNTITLED1_LEXER_H
#define UNTITLED1_LEXER_H

#include <vector>
#include <ostream>
#include "Token.h"

class Lexer {
public:
    // Constructors
    explicit Lexer(std::string input);

    // Performing lexical analysis
    void tokenize();

    // Accessors
    const std::vector<Token> &getTokens() const;

    // Overloaded output operator
    friend std::ostream &operator<<(std::ostream &os, const Lexer &lexer);

private:
    // Data members
    std::string input;
    size_t pos;
    std::vector<Token> tokens;

private:
    // Private utility functions
    static bool scan(std::unordered_set<std::string> list, const std::string &word);
    static int isFloat(const std::string &str);
    static bool isArithOp(const char &ch);
    static bool isOtherOp(const char &ch);
    static bool isBracket(const char &currentChar);

    // Lexical analysis methods
    void preprocDirective();
    void regularWord();
    void makeStr();
    void makeChar();
    void advance();
    void skipSpc();
    void extractWord();
    void extractNum();
    void handleArithOp(char i);
    void handleOtherOp(char i);
};


#endif //UNTITLED1_LEXER_H
