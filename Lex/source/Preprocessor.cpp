//
// Created by vivekdagar on 19/04/24.
//

#include "../include/Preprocessor.h"
#include "../include/TokenList.h"

void Preprocessor::preprocess()
{
    this->comments();
    this->directives();
    this->whitespace();
}

void Preprocessor::comments()
{
    size_t pos = 0;
    while ((pos = code.find("//", pos)) != std::string::npos)
    {
        size_t end = code.find('\n', pos);
        if (end == std::string::npos)
        {
            code.erase(pos);
        }
        else
        {
            code.erase(pos, end - pos);
        }
    }

    pos = 0;
    while ((pos = code.find("/*", pos)) != std::string::npos)
    {
        size_t end = code.find("*/", pos);
        if (end == std::string::npos)
        {
            // If "*/" not found, delete until end of string
            code.erase(pos);
            break;
        }
        else
        {
            // Delete characters between "/*" and "*/", including "/*" and "*/"
            code.erase(pos, end - pos + 2); // +2 to include the length of "*/"
        }
    }
}

void Preprocessor::directives()
{
    for (const auto& directive : ctokens::preprocessorDirectives) {
        size_t pos = 0;
        while ((pos = code.find(directive, pos)) != std::string::npos) {
            size_t end = code.find('\n', pos);
            if (end == std::string::npos) {
                code.erase(pos);
                break;
            } else {
                code.erase(pos, end - pos);
            }
        }
    }
}

void Preprocessor::whitespace()
{
    // Find the first non-whitespace character from the beginning
    const size_t start = code.find_first_not_of(" \t\n\r\f\v");
    if (start == std::string::npos) // If the string is all whitespace
        return;

    // Find the last non-whitespace character from the end
    const size_t end = code.find_last_not_of(" \t\n\r\f\v");

    code = code.substr(start, end - start + 1);
}
