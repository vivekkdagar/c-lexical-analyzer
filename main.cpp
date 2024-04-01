#include <iostream>
#include <sstream>
#include <algorithm>
#include "Lex/include/Lex.h"
#include "Lex/include/TokenList.h"

using namespace std;

int main() {
    Lex h("<a 2.0");
    h.advance();
    h.advance();
    cout << h;
    return 0;
}