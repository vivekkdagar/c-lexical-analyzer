//
// Created by vivekdagar on 4/2/24.
//

#include <sstream>
#include <algorithm>
#include "../include/Lex.h"

Lex::Lex(const string &input) : input(input), pos(0) {}

void Lex::skipSpace() {
    while (pos < input.length() and isspace(input[pos]))
        pos++;
}

void Lex::extractWord() {
    std::string word;

    // Check for preprocessor directive
    if (pos < input.length() && input[pos] == '#') {
        this->pos++;
        while (pos < input.length() and not isspace(input[pos])) {
            word += input[pos];
            pos++;
        }

        word = "#" + word;
        using ctokens::preprocessorDirectives, ctokens::TokType;

        for (const auto &directive: preprocessorDirectives)
            if (directive == word)
                this->processedOutput.emplace_back(TokType::PREPROCESSOR_DIRECTIVE, word);

        this->processedOutput.emplace_back(TokType::INVALID_TOK, word);
    }

    // Check for regular word
    while (pos < input.length() && (not isspace(input[pos]))) {
        word += input[pos];
        pos++;
    }

    using ctokens::keywords, ctokens::TokType;
    for (const auto &keyword: keywords)
        if (keyword == word){
            this->processedOutput.emplace_back(TokType::KEYWORD, word);
            return;
        }

    this->processedOutput.emplace_back(TokType::IDENTIFIER, word);
}

void Lex::advance() {
    this->skipSpace();

    if (this->pos >= this->input.length())
        this->processedOutput.emplace_back(ctokens::TokType::END_OF_FILE, "");

    char currentChar = input[pos];
    char nextChar = (pos < input.length() - 1) ? input[pos + 1] : ' ';

    if (isdigit(currentChar))
        this->extractNum();
    else if (isalpha(currentChar) or currentChar == '#')
        this->extractWord();
    else if (isBracket(currentChar)) {
        this->pos++;
        this->processedOutput.emplace_back(ctokens::TokType::BRACKET, std::string(currentChar, 1));
    } else if (isArithOp(currentChar)) {
        std::string arithOp(1, currentChar);
        this->pos++;

        if(this->input[this->pos] == '=') {
            arithOp += this->input[this->pos];
            this->pos++;
            this->processedOutput.emplace_back(ctokens::TokType::ASSIGNMENT_OPERATOR,arithOp);
        }
        if (arithOp == "+" || arithOp == "-") {
            if (this->input[this->pos] == currentChar) {
                // Compound operator found, such as "++" or "--"
                arithOp += currentChar;
                pos++;
            }
        }

        if(this->input[this->pos] == '>'){
            arithOp += this->input[this->pos++];
            this->processedOutput.emplace_back(ctokens::TokType::OTHER_OPERATOR, arithOp);
            return;
        }
        this->processedOutput.emplace_back(ctokens::TokType::ARITHMETIC_OPERATOR, arithOp);
    } else if(isOtherOp(currentChar)) {
        this->processedOutput.emplace_back(ctokens::TokType::OTHER_OPERATOR, std::string(1, currentChar));
        this->pos++;
    } else if(currentChar == '&' or currentChar == '|' or currentChar == '!') {
        std::string logOp(1, currentChar);
        if(currentChar == '!') {
            this->pos++;
            ctokens::TokType tokType = (this->input[this->pos] == '=') ? ctokens::TokType::RELATIONAL_OPERATOR
                                                                       : ctokens::TokType::LOGICAL_OPERATOR;
            logOp += this->input[this->pos];
            if(tokType == ctokens::TokType::LOGICAL_OPERATOR)
                logOp.pop_back();
            this->processedOutput.emplace_back(tokType, logOp);
        } else if(currentChar == '|') {
            this->pos++;
            logOp += this->input[this->pos];
            ctokens::TokType type;
            if(this->input[this->pos] == '=') {
                type = ctokens::TokType::ASSIGNMENT_OPERATOR;
                this->pos++;
            }
            else if(this->input[this->pos] == '|') {
                type = ctokens::TokType::LOGICAL_OPERATOR;
                this->pos++;
            }
            else{
                type = ctokens::TokType::BITWISE_OPERATOR;
                logOp.pop_back();
            }
            this->processedOutput.emplace_back(type, logOp);
        } else {
            this->pos++;
            logOp += this->input[this->pos];
            ctokens::TokType type;
            if (this->input[this->pos] == '=') {
                type = ctokens::TokType::ASSIGNMENT_OPERATOR;
                this->pos++;
            } else if (this->input[this->pos] == '&') {
                type = ctokens::TokType::LOGICAL_OPERATOR;
                this->pos++;
            } else {
                type = ctokens::TokType::BITWISE_OPERATOR;
                logOp.pop_back();
            }
            this->processedOutput.emplace_back(type, logOp);
        }
    } else if(currentChar == '~' or currentChar == '^' or currentChar == '<' or currentChar == '>') {
        std::string op(1, currentChar);
        this->pos++;

        if(this->input[this->pos] == '=' and currentChar == '^') {
            op += this->input[this->pos++];
            this->processedOutput.emplace_back(ctokens::TokType::ASSIGNMENT_OPERATOR, op);
        } else if((currentChar == this->input[this->pos] and (currentChar == '<' or currentChar == '>')))  {
            op += this->input[this->pos];
            this->pos++;
            if(this->input[this->pos] == '=') {
                op += this->input[this->pos++];
                this->processedOutput.emplace_back(ctokens::TokType::ASSIGNMENT_OPERATOR, op);
            } else {
                this->processedOutput.emplace_back(ctokens::TokType::BITWISE_OPERATOR, op);
            }
        } else if((currentChar == '>' or currentChar == '<') and this->input[this->pos] == '=') {
            op += this->input[this->pos++];
            this->processedOutput.emplace_back(ctokens::TokType::RELATIONAL_OPERATOR, op);
        } else if((currentChar not_eq '^' and currentChar not_eq '~')) {
            op += this->input[this->pos];
            this->processedOutput.emplace_back(ctokens::TokType::RELATIONAL_OPERATOR, op);
            this->pos++;
        }
    }
}

bool Lex::isBracket(const char &currentChar) {
    return (currentChar == '(' || currentChar == ')' ||
            currentChar == '[' || currentChar == ']' ||
            currentChar == '{' || currentChar == '}');
}

const vector<Token> &Lex::getProcessedOutput() const {
    return processedOutput;
}

void Lex::extractNum() {
    string constant;

    int decimalCount = 0; // Counter for decimal points

    while (pos < input.length() && not isspace(input[pos])) {
        if (input[pos] == '.') {
            decimalCount++; // Increment decimal point count
            if (decimalCount > 1) {
                this->processedOutput.emplace_back(ctokens::TokType::INVALID_TOK, constant);
                return;
            }
        }
        constant += input[pos];
        pos++;
    }

    ctokens::TokType numType = ctokens::TokType::INT_CONSTANT;
    if (isFloat(constant))
        numType = ctokens::TokType::FLOAT_CONSTANT;
    this->processedOutput.emplace_back(numType, constant);
}

std::ostream &operator<<(std::ostream &os, const Lex &lex) {
    for (const auto &i: lex.processedOutput) {
        os << ctokens::TokTypeHelper::print(i.getType())
           << " | " << i.getLexeme() << std::endl;
    }
    return os;
}

bool Lex::isFloat(const string &str) {
    std::istringstream iss(str);
    float f;
    iss >> std::noskipws >> f; // Try to read the float
    if (iss.eof() and not iss.fail())
        return std::count(str.begin(), str.end(), '.') == 1;
    return false;
}

bool Lex::isArithOp(const char &ch) {
    return ch == '+' or ch == '-' or ch == '*' or ch == '/' or ch == '%';
}

bool Lex::isOtherOp(const char &ch) {
    return ch == '?' or ch == ':' or ch == '.';
}
