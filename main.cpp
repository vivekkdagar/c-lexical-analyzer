#include <iostream>
#include <algorithm>
#include "Lex/include/Lexer.h"
#include "Lex/include/Preprocessor.h"

using namespace std;

int main()
{
    string input = R"(
        #include <iostream>

        int main() {
            int x = 1.2;
            return 1.23.232;
            return 1;
        }
    )";

    Lexer h(input);
    h.tokenize();
    for(auto a : h.getTokens())
    {
        cout << a;
    }

}
