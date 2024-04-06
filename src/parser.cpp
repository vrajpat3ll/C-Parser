#define LEXER_IMPLEMENTATION_
#include "../include/lexer.hpp"

#include <bits/stdc++.h>
using namespace std;

int main(int argc, char *argv[])
{
    string filepath = "./tests/testSwitch.cpp";

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
    // Error handling
    if (!file.is_open())
    {
        cerr << "File could not be opened!" << endl;
        return -1;
    }
    if (!file.good())
    {
        cerr << "File is not good!" << endl;
        return 1;
    }
    string content = "";
    string line = "";
    while (getline(file, line))
    {
        content += line + ' '; // cout << "line: " << line << "\n\n";
    }
    file.close();

    cout << "file contents:\n";
    cout << "---------------------------------------------\n";
    cout << content << endl;
    cout << "---------------------------------------------";

    Lexer *lexer = new Lexer(content);
    auto tokens = tokenise(lexer);

    cout << "\n\nPrinting tokens along with the type of token:\n\n";
    for (auto &token : tokens)
    {
        cout << tokenTypeName(token.type) << ": " << token.text << endl;
    }

    return 0;
}