#define LEXER_IMPLEMENTATION_
#include "../include/lexer.hpp"

#include <bits/stdc++.h>
using namespace std;

int main(int argc, char *argv[])
{
    string filepath = "C:/CODING/CODE/Projects/CParser/tests/testSwitch.cpp";

    if (argc == 1)
    {
        cout << "Give the path of the file to tokenize the contents!\n\n";
        // getline(cin, filepath);
    }
    else
    {
        filepath = argv[1];
    }

    ifstream file(filepath);
    string content = "";
    string line = "";
    while (getline(file, line))
    {
        // cout << "line: " << line << "\n\n";
        content += line + ' ';
    }
    file.close();

    cout << "file contents:\n";
    cout << "---------------------------------------------\n";
    cout << content << endl;

    Lexer *lexer = new Lexer(content);
    auto tokens = tokenise(lexer);
    cout << "---------------------------------------------";
    cout << "\n\nPrinting tokens along with the type of token:\n\n";
    for (auto &token : tokens)
    {
        cout << tokenTypeName(token.type) << ": " << token.text << endl;
    }

    return 0;
}