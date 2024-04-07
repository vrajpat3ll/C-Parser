#ifndef __C__PARSER_H__
#define __C__PARSER_H__
#define __LEXER_IMPLEMENTATION__
#include "lexer.hpp"
using namespace std;

class Parser {
    int tokenIter = 0;
    vector<Token> tokenStream;
    void getNextToken();
    void error(const string &message);
    void labeled_statement_list();
    void labeled_statement_list_();
    void labeled_statement();
    void expression();
    void statement();
    void additive_expression();
    void additive_expression_();
    void multiplicative_expression();
    void multiplicative_expression_();
    void primary_expression();

   public:
    Parser(const vector<Token> &tokens) {
        this->tokenStream = tokens;
        this->currentToken = tokens[0];
    }
    Token currentToken;
    void parseSwitchStatement();
};

void Parser::getNextToken() {
    this->tokenIter++;
    this->currentToken = tokenStream[tokenIter];
}

void Parser::parseSwitchStatement() {
    if (currentToken.text == "switch") {
        getNextToken();
        if (currentToken.type == TOKEN_OPEN_PAREN) {
            getNextToken();
            expression();
            if (currentToken.type == TOKEN_CLOSE_PAREN) {
                getNextToken();
                if (currentToken.type == TOKEN_OPEN_CURLY) {
                    getNextToken();
                    labeled_statement_list();
                    if (currentToken.type == TOKEN_CLOSE_CURLY) {
                        getNextToken();
                        return;
                    } else {
                        error("Expected '}'");
                    }
                } else {
                    error("Expected '{'");
                }
            } else {
                error("Expected ')'");
            }
        } else {
            error("Expected '('");
        }
    } else {
        error("Expected 'switch'");
    }
}

void Parser::error(const string &message) {
    cerr << "Error: " << message << endl;
    exit(1);
}

void Parser::labeled_statement_list() {
    if (currentToken.text == "case" || currentToken.text == "default") {
        labeled_statement();
        labeled_statement_list_();
    }
}
void Parser::labeled_statement_list_()
{
    if (currentToken.text == "case" || currentToken.text == "default")
    {
        labeled_statement();
        labeled_statement_list_();
    }
}

void Parser::labeled_statement() {
    if (currentToken.text == "case") {
        getNextToken();
        if (currentToken.type == TOKEN_INT_LITERAL)  // works only for constant integers for now
        {
            getNextToken();
            if (currentToken.type == TOKEN_COLON) {
                getNextToken();
                statement();
                // Parse statement here (not implemented)
            } else {
                error("Expected ':'");
            }
        } else {
            error("Expected constant");
        }
    } else if (currentToken.text == "default") {
        getNextToken();
        if (currentToken.type == TOKEN_COLON) {
            getNextToken();
            // Parse statement here (not implemented)
        } else {
            error("Expected ':'");
        }
    } else {
        error("Expected 'case' or 'default'");
    }
}

void Parser::statement() {
    
}

void Parser::expression() {
    additive_expression();
}

void Parser::additive_expression() {
    multiplicative_expression();
    additive_expression_();
}

void Parser::additive_expression_() {
    if (currentToken.text == "+" || currentToken.text == "-") {
        getNextToken();
        multiplicative_expression();
        additive_expression_();
    }
}

void Parser::multiplicative_expression() {
    primary_expression();
    multiplicative_expression_();
}

void Parser::multiplicative_expression_() {
    if (currentToken.text == "*" || currentToken.text == "/") {
        getNextToken();
        primary_expression();
        multiplicative_expression_();
    }
}

void Parser::primary_expression() {
    if (currentToken.type == TOKEN_ID || currentToken.type == TOKEN_INT_LITERAL) {
        getNextToken();
    } else if (currentToken.type == TOKEN_OPEN_PAREN) {
        getNextToken();
        expression();
        if (currentToken.type == TOKEN_CLOSE_PAREN) {
            getNextToken();
        } else {
            error("Expected ')'");
        }
    } else {
        error("Expected identifier, constant, or '('");
    }
}
#endif  // __C__PARSER_H__