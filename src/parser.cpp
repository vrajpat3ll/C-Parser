#define __LEXER_IMPLEMENTATION__
#include "../include/lexer.hpp"
#define __PARSER_IMPLEMENTATION__
#include "../include/parser.hpp"

#include <bits/stdc++.h>
using namespace std;

int main(int argc, char *argv[])
{
    string filepath = "C:/CODING/CODE/Projects/C-Parser/tests/testSwitch.cpp";

    if (argc == 1)
    {
        cout << "Give the path of the file to tokenize the contents: ";
        // getline(cin, filepath);
    }
    else
    {
        filepath = argv[1];
    }
    cout<<"\n\n";
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
    while (getline(file, line)) {content += line + '\n';}
    content += ' ';
    file.close();

    cout << "file contents:\n";
    cout << "---------------------------------------------\n";
    cout << content << endl;
    cout << "---------------------------------------------\n";

    // tokenise the contents
    Lexer *lexer = new Lexer(content);
    auto tokens = tokenise(lexer);

    cout << "\n\nPrinting tokens along with the type of token:\n\n";
    for (auto &token : tokens)
    {
        cout << setw(40) << left << tokenTypeName(token.type) << ": " << token.text << endl;
    }

    Parser *parser = new Parser(tokens);
    parser->parseSwitchStatement();
    // parser.printTree();

    return 0;
}