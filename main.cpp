#include <iostream>
#include <algorithm>
#include "Lex/include/Lexer.h"

using namespace std;

int main() {
    string input = R"(
    // Test
    #include "stdio.h"
    int main() {
        reurn 0;
    }
    )";

    cout << "Code is:" << input << endl;
    Lexer h(input);
    h.tokenize();
    cout << h;
}
