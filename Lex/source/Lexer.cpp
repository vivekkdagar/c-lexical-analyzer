//
// Created by vivekdagar on 4/2/24.
//

#include <utility>
#include <algorithm>
#include <sstream>

#include "../include/Lexer.h"

#include "../include/Preprocessor.h"

Lexer::Lexer(std::string input) : input(std::move(input)), pos(0) {}

void Lexer::skipSpc() {
    auto nonSpaceIter = std::find_if(input.begin() + pos, input.end(), [](char c) {
        return !std::isspace(static_cast<unsigned char>(c));
    });

    pos = nonSpaceIter - input.begin();
}

void Lexer::extractWord() {

    // Check for preprocessor directive
    if (pos < input.length() && input[pos] == '#') {
        preprocDirective();
        return;
    }

    // Check for regular word
    regularWord();
}

void Lexer::preprocDirective() {
    std::string word;
    this->pos++;

    while (pos < input.length() and (isalpha(this->input[pos]) and not isspace(input[pos]))) {
        word += input[pos];
        pos++;
    }

    word = "#" + word;

    using ctokens::preprocessorDirectives, ctokens::TokType;

    // Check if the extracted word is a Preprocessor Directive
    this->tokens.emplace_back(scan(preprocessorDirectives, word) ?
                              TokType::PREPROCESSOR_DIRECTIVE :
                              TokType::INVALID_TOK, word);
}

void Lexer::regularWord() {
    std::string word;

    // Check for regular word
    while (pos < input.length() and (isalpha(input[pos]) and not isspace(input[pos]))) {
        word += input[pos];
        pos++;
    }

    using ctokens::keywords, ctokens::TokType;

    // Check if the extracted word is a Preprocessor Directive
    this->tokens.emplace_back(scan(keywords, word) ?
                              TokType::KEYWORD :
                              TokType::IDENTIFIER, word);
}

bool Lexer::scan(std::unordered_set<std::string> list, const std::string &word) {
    return list.find(word) not_eq list.end();
}

[[maybe_unused]] bool Lexer::isArithOp(const char &ch) {
    switch (ch) {
        case '+':
        case '-':
        case '*':
        case '/':
        case '%':
            return true;
        default:
            return false;
    }
}

bool Lexer::isOtherOp(const char &ch) {
    switch (ch) {
        case '?':
        case ':':
        case '.':
            return true;
        default:
            return false;
    }
}

void Lexer::tokenize() {
    Preprocessor obj(this->input);
    obj.preprocess();
    this->input = obj.getCode();

    if (this->tokens.empty())
        this->advance();

    while (this->tokens.back().getType() not_eq ctokens::TokType::END_OF_FILE)
        this->advance();
}

void Lexer::advance() {
    this->skipSpc();

    if (pos >= input.length()) {
        tokens.emplace_back(ctokens::TokType::END_OF_FILE, "");
        return;
    }

    char currentChar = input[pos];
    char nextChar = (pos < input.length() - 1) ? input[pos + 1] : ' ';

    if (isdigit(currentChar)) {
        this->extractNum();
        return;
    }

    switch (currentChar) {
        case ';':
        case ',': {
            std::string obj = (currentChar == ';') ? ";" : ",";
            this->tokens.emplace_back(ctokens::TokType::SPECIAL_SYMBOL, obj);
            this->pos++;
        }
            break;
        case '\'': {
            this->makeChar();
        }
            break;
        case '\"': {
            this->makeStr();
        }
            break;
        case '=': {
            std::string op(1, currentChar);
            ctokens::TokType tokType = ctokens::TokType::ASSIGNMENT_OPERATOR;
            if (this->pos + 1 < this->input.length() and this->input[this->pos + 1] == '=') {
                tokType = ctokens::TokType::RELATIONAL_OPERATOR;
                op += '=';
                this->pos++;
            }
            this->pos++;
            this->tokens.emplace_back(tokType, op);
        }
            break;
        case '~':
        case '^':
        case '<':
        case '>': {
            std::string bitwise(1, currentChar);
            this->pos++;

            switch (this->input[this->pos]) {
                case '=': {
                    if (currentChar == '^') {
                        bitwise += this->input[this->pos++];
                        this->tokens.emplace_back(ctokens::TokType::ASSIGNMENT_OPERATOR, bitwise);
                    }

                    if (currentChar == '>' or currentChar == '<') {
                        bitwise += this->input[this->pos++];
                        this->tokens.emplace_back(ctokens::TokType::RELATIONAL_OPERATOR, bitwise);
                        return;
                    }
                }
                    break;

                case '>':
                case '<': {
                    if (currentChar == this->input[this->pos]) {
                        bitwise += this->input[this->pos++];

                        if (this->input[this->pos] == '=') {
                            bitwise += this->input[this->pos++];
                            this->tokens.emplace_back(ctokens::TokType::ASSIGNMENT_OPERATOR, bitwise);
                            return;
                        } else {
                            this->tokens.emplace_back(ctokens::TokType::BITWISE_OPERATOR, bitwise);
                            return;
                        }
                    }
                }
                    break;
            }

            switch (currentChar) {
                case '^':
                case '~': {
                    this->tokens.emplace_back(ctokens::TokType::BITWISE_OPERATOR, bitwise);
                    return;
                }
                    break;
                case '>':
                case '<': {
                    this->tokens.emplace_back(ctokens::TokType::RELATIONAL_OPERATOR, bitwise);
                    return;
                }
                    break;
            }
        }
            break;
        default: {
            if (isBracket(currentChar)) {
                this->tokens.emplace_back(ctokens::TokType::BRACKET, std::string("") + currentChar);
                this->pos++;
            } else if (currentChar == '#' and nextChar == ' ') {
                tokens.emplace_back(ctokens::TokType::SPECIAL_SYMBOL, std::string("#", 1));
                pos++;
            } else if (isalpha(currentChar) or currentChar == '#') {
                this->extractWord();
            } else if (isArithOp(currentChar)) {
                this->handleArithOp(currentChar);
            } else if (isOtherOp(currentChar)) {
                this->handleOtherOp(currentChar);
            } else if (currentChar == '&' || currentChar == '|' || currentChar == '!') {
                std::string logOp(1, currentChar);
                this->pos++;

                if (currentChar == '!') {
                    if (this->input[this->pos] == '=') {
                        logOp += this->input[this->pos++];
                        this->tokens.emplace_back(ctokens::TokType::RELATIONAL_OPERATOR, logOp);
                    } else {
                        this->tokens.emplace_back(ctokens::TokType::LOGICAL_OPERATOR, logOp);
                    }
                } else {
                    // Handle bitwise, logical, or assignment operators
                    logOp += this->input[this->pos++];
                    ctokens::TokType type;
                    if (logOp == "||" || logOp == "&&") {
                        type = ctokens::TokType::LOGICAL_OPERATOR;
                    } else if (logOp == "|=" || logOp == "&=") {
                        type = ctokens::TokType::ASSIGNMENT_OPERATOR;
                    } else {
                        type = ctokens::TokType::BITWISE_OPERATOR;
                        logOp.pop_back(); // Remove redundant character if present
                    }
                    this->tokens.emplace_back(type, logOp);
                }
            }

        }
    }
}

std::ostream &operator<<(std::ostream &os, const Lexer &lexer) {
    os << "Token Type\t| Lexeme\n";
    os << "---------------------------------\n";

    for (const auto &token: lexer.tokens)
        os << token;
    return os;
}

int Lexer::isFloat(const std::string &str) {
    std::istringstream iss(str);
    float f;
    iss >> std::noskipws >> f; // Try to read the float
    if (iss.eof() and not iss.fail())
        return std::count(str.begin(), str.end(), '.') == 1;
    return -1;
}

const std::vector<Token> &Lexer::getTokens() const {
    return tokens;
}

bool Lexer::isBracket(const char &currentChar) {
    switch (currentChar) {
        case '(':
        case ')':
        case '[':
        case ']':
        case '{':
        case '}':
            return true;
        default:
            return false;
    }
}

void Lexer::extractNum() {
    std::string constant;

    while (pos < input.length()  and
           (this->input[pos] not_eq ';' and this->input[pos] not_eq ',')) {
        if (isdigit(input[pos]) or input[pos] == '.') {
            constant += input[pos];
        } else {
            while (pos < input.length() && !isspace(input[pos]) && input[pos] != ';') {
                constant += input[pos];
                pos++;
            }
            tokens.emplace_back(ctokens::TokType::INVALID_TOK, constant);
            return;
        }
        pos++;
    }

    ctokens::TokType numType;

    switch (isFloat(constant)) {
        case -1:
            numType = ctokens::TokType::INVALID_TOK;
            break;
        case 0:
            numType = ctokens::TokType::INT_CONSTANT;
            break;
        default:
            numType = ctokens::TokType::FLOAT_CONSTANT;
            break;
    }

    if (numType == ctokens::TokType::INVALID_TOK) {
        tokens.emplace_back(ctokens::TokType::INVALID_TOK, constant);
        pos++;
        return;
    }

    tokens.emplace_back(numType, constant);
}

void Lexer::makeStr() {
    std::string obj = "\"";

    std::unordered_map<char, char> whitespaceMap = {
            {' ',  's'},
            {'\t', 't'},
            {'\n', 'n'},
            {'\r', 'r'},
            {'\f', 'f'},
            {'\v', 'v'}
    };

    if (pos + 1 < input.length()) {
        size_t endPos = input.find('"', pos + 1);
        if (endPos != std::string::npos) {
            std::string str = input.substr(pos + 1, endPos - pos - 1);
            for (char &c: str) {
                if (isspace(c))
                    c = whitespaceMap[c];
            }
            tokens.emplace_back(ctokens::TokType::STRING, str);
            pos = endPos + 1;
            return;
        }
    }

    obj.clear();
    while (pos < input.length() && (!isspace(input[pos]) || input[pos] != '\"')) {
        obj += input[pos];
        pos++;
    }
    tokens.emplace_back(ctokens::TokType::INVALID_TOK, obj);
    pos++;
}

void Lexer::makeChar() {
    std::string obj;
    obj += this->input[this->pos];

    // Map whitespace characters to their respective representations
    std::unordered_map<char, char> whitespaceMap = {
            {' ',  's'},
            {'\t', 't'},
            {'\n', 'n'},
            {'\r', 'r'},
            {'\f', 'f'},
            {'\v', 'v'}
    };

    if (this->pos + 1 < this->input.length()) {
        char character = this->input[this->pos + 1];

        // Check if it's a whitespace character
        if (whitespaceMap.find(character) != whitespaceMap.end()) {
            while (this->input[pos] != '\'' or isspace(input[pos])) {
                obj += this->input[pos];
                pos++;
            }
            if (this->input[pos] == '\'') {
                obj += this->input[pos];
                pos++;
            }
            this->tokens.emplace_back(ctokens::TokType::INVALID_TOK, obj);
        } else if (this->pos + 2 < this->input.length() && this->input[this->pos + 2] == '\'') {
            this->tokens.emplace_back(ctokens::TokType::CHAR_CONST, std::string(1, character));
            this->pos += 3;
        } else {
            this->pos++;
            while (pos < this->input.length() && (this->input[this->pos] != '\'')) {
                obj += this->input[this->pos];
                pos++;
            }
            if (pos < this->input.length() and this->input[this->pos] == '\'')
                obj += '\'';
            this->tokens.emplace_back(ctokens::TokType::INVALID_TOK, obj);
            this->pos++;
        }
    } else {
        this->tokens.emplace_back(ctokens::TokType::INVALID_TOK, "\'");
        this->pos++;
    }
}

void Lexer::handleArithOp(char i) {
    std::string str(1, i);
    ctokens::TokType type = ctokens::TokType::ARITHMETIC_OPERATOR;

    this->pos++;

    switch (i) {
        case '*': {
            if (this->input[this->pos] == '/') {
                str += this->input[this->pos++];
                type = ctokens::TokType::SPECIAL_SYMBOL;
            }
        }
            break;
        case '/': {
            if (this->input[this->pos] == '/' or this->input[this->pos] == '*') {
                str += this->input[this->pos++];
                type = ctokens::TokType::SPECIAL_SYMBOL;
            }
        }
            break;
    }

    switch (this->input[this->pos]) {
        case '=': {
            str += this->input[this->pos++];
            type = ctokens::TokType::ASSIGNMENT_OPERATOR;
        }
            break;

        case '+':
        case '-': {
            if ((str == "+" || str == "-")) {
                str += i;
                pos++;
            }
        }
            break;

        case '>': {
            str += this->input[this->pos++];
            type = (i == '-') ? ctokens::TokType::OTHER_OPERATOR : ctokens::TokType::INVALID_TOK;
        }
            break;
    }

    this->tokens.emplace_back(type, str);
}

void Lexer::handleOtherOp(char i) {
    std::string str(1, i);
    this->pos++;
    ctokens::TokType type = ctokens::TokType::OTHER_OPERATOR;

    if (this->input[this->pos++] == '.') {
        str += '.';
        if (this->input[this->pos] == '.') {
            str += '.';
            this->pos++;
        } else {
            type = ctokens::TokType::INVALID_TOK;
        }
    }
    this->tokens.emplace_back(type, str);
}


