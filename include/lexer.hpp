#ifndef __C__LEXER_H__
#define __C__LEXER_H__

#include <iostream>
#include <vector>
using namespace std;
#define len(s) sizeof(s) / sizeof(s[0])

typedef enum
{
    TOKEN_EOF,               // End of File
    TOKEN_INVALID,           // Invalid token
    TOKEN_ID,                // Symbol / Identifier
    TOKEN_OPEN_PAREN,        // (
    TOKEN_CLOSE_PAREN,       // )
    TOKEN_OPEN_CURLY,        // {
    TOKEN_CLOSE_CURLY,       // }
    TOKEN_SEMICOLON,         // ;
    TOKEN_COLON,             // :
    TOKEN_EQUALS_ASSIGNMENT, // =
    TOKEN_KEYWORD,           // keywords
    TOKEN_SWITCH,            // switch
    TOKEN_CASE,              // case
    TOKEN_DEFAULT,           // default
    TOKEN_BREAK,             // break
    TOKEN_INT_LITERAL,       // Integer Literal
    TOKEN_STR_LITERAL,       // String Literal
    TOKEN_OPERATOR,          // Operator (covers +, - , * , / , % )
} TokenType;

typedef struct Token
{
    TokenType type;
    string text;
    Token()
    {
        type = TOKEN_INVALID;
        text = "";
    }
    Token(TokenType t, string s)
    {
        type = t;
        text = s;
    }
} Token;

typedef struct Lexer
{
    string content;
    unsigned int cursor;
    Lexer(const string &s)
    {
        cursor = 0;
        content = s;
    }
} Lexer;

bool isOperator(char c)
{
    switch (c)
    {
    case '+':
    case '-':
    case '*':
    case '/':
    case '!':
    case '%':
        return true;
    }
    return false;
}

vector<Token> literalTokens = {
    Token(TOKEN_OPEN_PAREN, "("),
    Token(TOKEN_CLOSE_PAREN, ")"),
    Token(TOKEN_OPEN_CURLY, "{"),
    Token(TOKEN_CLOSE_CURLY, "}"),
    Token(TOKEN_SEMICOLON, ";"),
    Token(TOKEN_COLON, ":"),
    Token(TOKEN_EQUALS_ASSIGNMENT, "="),
};

vector<string> keywords = {
    "break",
    "case",
    "char",
    "continue",
    "default",
    "double",
    "float",
    "int",
    "long",
    "return",
    "sizeof",
    "switch",
};

int keywords_size = keywords.size();

bool isalpha(char c) { return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'); }
const string tokenTypeName(const TokenType &type);
const Token stringToLiteralToken(const string &tokenName);
Token getNextToken(Lexer *lexer);
vector<Token> tokenise(Lexer *l);
// #endif
// #ifdef LEXER_IMPLEMENTATION_

/// @param type Token to get its name
/// @return name of the type of token passed (with some color)
const string tokenTypeName(const TokenType &type)
{
    switch (type)
    {
    case TOKEN_EOF:
        return "(\e[32mend of file\e[0m)";
    case TOKEN_INVALID:
        return "(\e[31minvalid token\e[0m)";
    case TOKEN_ID:
        return "(\e[37midentifier\e[0m)";
    case TOKEN_OPEN_PAREN:
        return "(\e[37mopen parenthesis\e[0m)";
    case TOKEN_CLOSE_PAREN:
        return "(\e[37mclose parenthesis\e[0m)";
    case TOKEN_OPEN_CURLY:
        return "(\e[37mopen curly brace\e[0m)";
    case TOKEN_CLOSE_CURLY:
        return "(\e[37mclose curly brace\e[0m)";
    case TOKEN_SEMICOLON:
        return "(\e[37msemicolon\e[0m)";
    case TOKEN_COLON:
        return "(\e[37mcolon\e[0m)";
    case TOKEN_EQUALS_ASSIGNMENT:
        return "(\e[37mequals\e[0m)";
    case TOKEN_KEYWORD:
        return "(\e[34mkeyword\e[0m)";
    case TOKEN_INT_LITERAL:
        return "(\e[37minteger literal\e[0m)";
    case TOKEN_STR_LITERAL:
        return "(\e[37mstring literal\e[0m)";
    case TOKEN_OPERATOR:
        return "(\e[37moperator\e[0m)";
    default:
        return "(\e[31mUnreachable TokenType Name\e[0m)";
    }
    return "Un-Reachable";
}

const Token stringToLiteralToken(const string &literalToken)
{
    if (literalToken == "=")
        return Token(TOKEN_COLON, "=");
    if (literalToken == ":")
        return Token(TOKEN_COLON, ":");
    if (literalToken == ";")
        return Token(TOKEN_SEMICOLON, ";");
    if (literalToken == "(")
        return Token(TOKEN_OPEN_PAREN, "(");
    if (literalToken == ")")
        return Token(TOKEN_CLOSE_PAREN, ")");
    if (literalToken == "{")
        return Token(TOKEN_OPEN_CURLY, "{");
    if (literalToken == "}")
        return Token(TOKEN_CLOSE_CURLY, "}");
    if (literalToken == "switch")
        return Token(TOKEN_SWITCH, "switch");
    if (literalToken == "case")
        return Token(TOKEN_CASE, "case");
    if (literalToken == "default")
        return Token(TOKEN_DEFAULT, "default");
    if (literalToken == "break")
        return Token(TOKEN_BREAK, "break");

    return Token(TOKEN_INVALID, literalToken);
}

// FIXME: not sure of its use
// bool lexer_starts_with(Lexer *lexer, const string prefix)
// {
//     unsigned int prefix_len = prefix.size();
//     if (prefix_len == 0)
//     {
//         return true;
//     }
//     if (lexer->cursor + prefix_len - 1 >= lexer->content.size())
//     {
//         return false;
//     }
//     for (unsigned int i = 0; i < prefix_len; ++i)
//     {
//         if (prefix[i] != lexer->content[lexer->cursor + i])
//         {
//             return false;
//         }
//     }
//     return true;
// }

bool isIdentifierStart(char x) { return isalpha(x) || x == '_'; }
bool isIdentifier(char x) { return isalnum(x) || x == '_'; }
char getChar(Lexer *l) { return l->content[l->cursor]; }

// TODO: unimplemented
Token getNextToken(Lexer *l)
{
    Token tok;
    auto s = l->content;
    return tok;
}

// TODO: almost done
vector<Token> tokenise(Lexer *l)
{
    unsigned int content_len = l->content.size();
    if (l->cursor >= content_len)
        return {Token(TOKEN_EOF, "")};

    vector<Token> tokens;
    while (l->cursor < content_len)
    {
        while (l->content[l->cursor] == ' ')
            l->cursor++;

        string tokenName = "";
        if (isIdentifierStart(getChar(l)))
        {
            tokenName += getChar(l);
            l->cursor++;
            while (isIdentifier(getChar(l)))
            {
                tokenName += getChar(l);
                l->cursor++;
            }
            bool isKeyword = false;
            for (int i = 0; i < keywords_size; i++)
            {
                if (tokenName == keywords[i])
                {
                    tokens.push_back(Token(TOKEN_KEYWORD, tokenName));
                    isKeyword = true;
                    break;
                }
            }
            if (!isKeyword)
                tokens.push_back(Token(TOKEN_ID, tokenName));
        }
        else if (isdigit(getChar(l)))
        {
            string number;
            number += getChar(l);
            l->cursor++;
            while (isdigit(getChar(l)))
            {
                number += getChar(l);
                l->cursor++;
            }
            if (isIdentifierStart(getChar(l)))
            {
                number += getChar(l);
                l->cursor++;
                while (isIdentifier(getChar(l)))
                {
                    number += getChar(l);
                    l->cursor++;
                }
                tokens.push_back(Token(TOKEN_INVALID, number));
                continue;
            }
            tokens.push_back(Token(TOKEN_INT_LITERAL, number));
        }
        else if (getChar(l) == '"')
        {
            string strLiteral;
            l->cursor++;
            while (getChar(l) != '"' && getChar(l) != '\0')
            {
                strLiteral += getChar(l);
                l->cursor++;
            }
            tokens.push_back(Token(TOKEN_STR_LITERAL, strLiteral));
            l->cursor++; // skip closing quote
        }
        else if (getChar(l) == '(')
        {
            tokens.push_back(Token(TOKEN_OPEN_PAREN, "("));
            l->cursor++;
        }
        else if (getChar(l) == ')')
        {
            tokens.push_back(Token(TOKEN_CLOSE_PAREN, ")"));
            l->cursor++;
        }
        else if (getChar(l) == '{')
        {
            tokens.push_back(Token(TOKEN_OPEN_CURLY, "{"));
            l->cursor++;
        }
        else if (getChar(l) == '}')
        {
            tokens.push_back(Token(TOKEN_CLOSE_CURLY, "}"));
            l->cursor++;
        }
        else if (getChar(l) == ';')
        {
            tokens.push_back(Token(TOKEN_SEMICOLON, ";"));
            l->cursor++;
        }
        else if (getChar(l) == ':')
        {
            tokens.push_back(Token(TOKEN_COLON, ":"));
            l->cursor++;
        }
        else if (getChar(l) == '=')
        {
            tokens.push_back(Token(TOKEN_EQUALS_ASSIGNMENT, "="));
            l->cursor++;
        }
        else if (isOperator(getChar(l)))
        {
            string op(1, getChar(l));
            tokens.push_back(Token(TOKEN_OPERATOR, op));
            l->cursor++;
        }
        else if (getChar(l) == '\0')
        {
            tokens.push_back(Token(TOKEN_EOF, ""));
            break;
        }
        else if (getChar(l) == '\n')
        {
            l->cursor++;
            continue;
        }
        else
        { // TOKEN_INVALID
            // Handle errors (consider throwing exceptions or providing more specific error messages)
            cerr << "Error: Unexpected character '" << getChar(l) << "'" << std::endl;
            l->cursor++;
            tokens.push_back(Token(TOKEN_INVALID, tokenName));
        }
    }
    return tokens;
}

#endif