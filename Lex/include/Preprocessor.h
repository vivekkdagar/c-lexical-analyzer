//
// Created by vivekdagar on 19/04/24.
//

#ifndef PREPROCESSOR_H
#define PREPROCESSOR_H
#include <string>
#include <utility>


class Preprocessor
{
    std::string code;

public:
    explicit Preprocessor(std::string code)
        : code(std::move(code))
    {
    }

    void preprocess();

    [[nodiscard]] std::string getCode() const
    {
        return code;
    }

private:
    void comments();

    void directives();

    void whitespace();
};


#endif //PREPROCESSOR_H
