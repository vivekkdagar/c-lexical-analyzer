#include <iostream>
#include <algorithm>
#include "Lex/include/Lexer.h"

using namespace std;

int main() {
    string input = R"(
    #include "stdio.h"
    int main() {
        if(age > 12) {
            return 2;
        }   else{
        return 0;
    }
    )";

    cout << "Code is:" << input << endl;
    Lexer h(input);
    h.tokenize();
    cout << h;
}
