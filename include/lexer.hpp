#ifndef LEXER_H_
#define LEXER_H_

#include <iostream>
#include <vector>
using namespace std;
#define len(s) sizeof(s) / sizeof(s[0])

typedef enum
{
    TOKEN_EOF,         // End of File
    TOKEN_INVALID,     // Invalid token
    TOKEN_ID,          // Symbol / Identifier
    TOKEN_OPEN_PAREN,  // (
    TOKEN_CLOSE_PAREN, // )
    TOKEN_OPEN_CURLY,  // {
    TOKEN_CLOSE_CURLY, // }
    TOKEN_SEMICOLON,   // ;
    TOKEN_COLON,       // :
    TOKEN_EQUALS,      // =
    TOKEN_SWITCH,      // switch
    TOKEN_CASE,        // case
    TOKEN_DEFAULT,     // default
    TOKEN_BREAK,       // break
    TOKEN_INT_LITERAL, // Integer Literal
    TOKEN_STR_LITERAL, // String Literal
    TOKEN_OPERATOR,    // Operator
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
bool isalpha(char c) { return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'); }
const string tokenTypeName(const TokenType type);
const Token stringToLiteralToken(const string &tokenName);
Token getNextToken(Lexer *lexer);
vector<Token> tokenise(Lexer *l);
#endif

// #ifdef LEXER_IMPLEMENTATION_

/// @param type Token to get its name
/// @return name of the type of token passed
const string tokenTypeName(const TokenType type)
{
    switch (type)
    {
    case TOKEN_EOF:         return "(end of content)\t";
    case TOKEN_INVALID:     return "(invalid token)\t\t";
    case TOKEN_ID:          return "(identifier)\t\t";
    case TOKEN_OPEN_PAREN:  return "(open parenthesis)\t";
    case TOKEN_CLOSE_PAREN: return "(close parenthesis)\t";
    case TOKEN_OPEN_CURLY:  return "(open curly brace)\t";
    case TOKEN_CLOSE_CURLY: return "(close curly brace)\t";
    case TOKEN_SEMICOLON:   return "(semicolon)\t\t";
    case TOKEN_COLON:       return "(colon)\t\t\t";
    case TOKEN_EQUALS:      return "(equals)\t\t";
    case TOKEN_SWITCH:      return "(switch)\t\t";
    case TOKEN_CASE:        return "(case)\t\t\t";
    case TOKEN_DEFAULT:     return "(default)\t\t";
    case TOKEN_BREAK:       return "(break)\t\t\t";
    case TOKEN_INT_LITERAL: return "(integer literal)\t";
    case TOKEN_STR_LITERAL: return "(string literal)\t";
    case TOKEN_OPERATOR:    return "(operator)\t\t";
    default:                return "(Unreachable TokenType Name)\t\t";
    }
    return "";
}

const Token stringToLiteralToken(const string &literalToken)
{
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

    return Token(TOKEN_INVALID, literalToken);
}

// FIXME: not sure of its use
bool lexer_starts_with(Lexer *lexer, const string prefix)
{
    unsigned int prefix_len = prefix.size();

    if (prefix_len == 0)
    {
        return true;
    }
    if (lexer->cursor + prefix_len - 1 >= lexer->content.size())
    {
        return false;
    }
    for (unsigned int i = 0; i < prefix_len; ++i)
    {
        if (prefix[i] != lexer->content[lexer->cursor + i])
        {
            return false;
        }
    }
    return true;
}

bool isIdentifierStart(char x) { return isalpha(x) || x == '_'; }

bool isIdentifier(char x) { return isalnum(x) || x == '_'; }

// char getChar(Lexer *l) { return l->content[l->cursor]; }

// TODO: unimplemented
Token getNextToken(Lexer *l)
{
    Token tok;
    auto s = l->content;
    return tok;
}

// TODO: unimplemented
vector<Token> tokenise(Lexer *l)
{
    unsigned int content_len = l->content.size();
    if (l->cursor >= content_len)
    {
        return {Token(TOKEN_EOF, "")};
    }
    vector<Token> tokens;

    while (l->cursor < content_len)
    {
        while (l->content[l->cursor] == ' ')
            l->cursor++;

        if (isalpha((l->content)[l->cursor]))
        {
            string tokenName = "";
            while (isalpha(l->content[l->cursor]))
            {
                tokenName += l->content[l->cursor];
                l->cursor++;
            }

            if (tokenName == "switch")
            {
                tokens.push_back(Token(TOKEN_SWITCH, tokenName));
            }
            else if (tokenName == "case")
            {
                tokens.push_back(Token(TOKEN_CASE, tokenName));
            }
            else if (tokenName == "default")
            {
                tokens.push_back(Token(TOKEN_DEFAULT, tokenName));
            }
            else if (tokenName == "break")
            {
                tokens.push_back(Token(TOKEN_BREAK, tokenName));
            }
            else
            {
                tokens.push_back(Token(TOKEN_ID, tokenName));
            }
        }
        else if (isdigit(l->content[l->cursor]))
        {
            string number;
            while (isdigit(l->content[l->cursor]))
            {
                number += l->content[l->cursor];
                l->cursor++;
            }
            tokens.push_back(Token(TOKEN_INT_LITERAL, number));
        }

        else if (l->content[l->cursor] == '"')
        {
            string strLiteral;
            l->cursor++;
            while (l->content[l->cursor] != '"' && l->content[l->cursor] != '\0')
            {
                strLiteral += l->content[l->cursor];
                l->cursor++;
            }
            tokens.push_back(Token(TOKEN_STR_LITERAL, strLiteral));
            l->cursor++; // skip closing quote
        }
        else if (l->content[l->cursor] == '(')
        {
            tokens.push_back(Token(TOKEN_OPEN_PAREN, "("));
            l->cursor++;
        }
        else if (l->content[l->cursor] == ')')
        {
            tokens.push_back(Token(TOKEN_CLOSE_PAREN, ")"));
            l->cursor++;
        }
        else if (l->content[l->cursor] == '{')
        {
            tokens.push_back(Token(TOKEN_OPEN_CURLY, "{"));
            l->cursor++;
        }
        else if (l->content[l->cursor] == '}')
        {
            tokens.push_back(Token(TOKEN_CLOSE_CURLY, "}"));
            l->cursor++;
        }
        else if (l->content[l->cursor] == ';')
        {
            tokens.push_back(Token(TOKEN_SEMICOLON, ";"));
            l->cursor++;
        }
        else if (l->content[l->cursor] == ':')
        {
            tokens.push_back(Token(TOKEN_COLON, ":"));
            l->cursor++;
        }
        else if (l->content[l->cursor] == '=')
        {
            tokens.push_back(Token(TOKEN_EQUALS, "="));
            l->cursor++;
        }
        else if (isOperator(l->content[l->cursor]))
        {
            string op(1, l->content[l->cursor]);
            tokens.push_back(Token(TOKEN_OPERATOR, op));
            l->cursor++;
        }
        else if (l->content[l->cursor] == '\0')
        {
            tokens.push_back(Token(TOKEN_EOF, ""));
            break;
        }

        else
        { // TOKEN_INVALID
            // Handle errors (consider throwing exceptions or providing more specific error messages)
            cerr << "Error: Unexpected character '" << l->content[l->cursor] << "'" << std::endl;
            l->cursor++;
        }
    }
    return tokens;
}

// #endif