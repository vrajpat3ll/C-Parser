#include <bits/stdc++.h>
#define __LEXER_IMPLEMENTATION__
#include "../include/lexer.hpp"
#define __PARSER_IMPLEMENTATION__
#include "../include/parser.hpp"

using namespace std;

// change this to anything other than 1
// to disable printing the file contents
#define PRINT_FILE_CONTENTS 1

int main(int argc, char *argv[]) {
    string filepath = "./tests/testSwitch.cpp";

    if (argc == 1) {
        cout << "Give the path of the file to tokenize the contents: ";
        getline(cin, filepath);
    } else {
        filepath = argv[1];
    }
    cout << "\n\n";
    ifstream file(filepath);
    // Error handling
    if (!file.is_open()) {
        cerr << "File could not be opened!" << endl;
        return -1;
    }
    if (!file.good()) {
        cerr << "File is not good!" << endl;
        return 1;
    }
    string content = "";
    string line = "";
    while (getline(file, line)) {
        content += line + '\n';
    }
    content += ' ';
    file.close();

#if (PRINT_FILE_CONTENTS == 1)
    cout << "file contents:\n";
    cout << "----------------------------------------------+\n";
    cout << "\e[35m" + content + "\e[0m" << endl;
#endif
    cout << "----------------------------------------------+\n\n";

    // tokenise the contents
    Lexer *lexer = new Lexer(content);
    auto tokens = tokenise(lexer);

    cout << "+---------------------------------------------+\n";
    cout << "|          \e[32mTokenised successfully!\e[0m            |" << endl;
    cout << "+---------------------------------------------+\n";

    cout << "\n\nPrinting tokens along with the type of token:\n\n";
    for (auto &token : tokens) {
        cout << setw(40) << left << tokenTypeName(token.type) << ": " << token.text << endl;
    }
    cout << endl
         << endl;
    Parser *parser = new Parser(tokens);
    parser->parseSwitchStatement();

    cout << "+---------------------------------------------+\n";
    cout << "|              \e[32mParsed completely!\e[0m             |" << endl;
    cout << "+---------------------------------------------+\n";

    cout << endl
        //  << "Printing the level order of parse tree" << endl
         << endl;
    // parser->printTree();

    return 0;
}