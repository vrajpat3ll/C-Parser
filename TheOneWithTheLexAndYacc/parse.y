%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"

struct TreeNode *parse_tree;
%}

%token LEFT_PAREN RIGHT_PAREN LEFT_CURLY RIGHT_CURLY COLON SEMICOLON EQUALS_ASSIGN
%token INT FLOAT DOUBLE CHAR SHORT LONG SIGNED UNSIGNED 

%start Program

%union {
    struct TreeNode *node;
    char *str;
}

%type <node> Program 
%type <node> switch_statement 
%type <node> expression 
%type <node> statement
%type <node> assignment_statement
%type <node> type_specifier
%type <node> statement_list
/* %type <node> const_expression */
%type <node> return_expression

%token <str> IDENTIFIER CONSTANT STRING_LITERAL SWITCH CASE DEFAULT GOTO CONTINUE BREAK RETURN

%%

Program: switch_statement 
    {
        // parse_tree->left = $1 = (TreeNode*)malloc(sizeof(TreeNode*));
    }
    ;

switch_statement: SWITCH LEFT_PAREN expression RIGHT_PAREN statement 
    {
        $$ = parse_tree;
        parse_tree->left = create_switch_statement_node($3, $5);}
    ;

expression : IDENTIFIER                         { $$ = create_identifier_node($1); }                         
    | CONSTANT                                  { $$ = create_constant_node($1); }
    | STRING_LITERAL                            { $$ = create_string_literal_node($1); }
    | LEFT_PAREN expression RIGHT_PAREN         { $$ = $2; }
    ;

statement : LEFT_CURLY RIGHT_CURLY              {}  
    | LEFT_CURLY statement_list RIGHT_CURLY     { $$ = create_statement_list_node($2); }  
    | CASE expression COLON statement           { $$ = create_case_statement_node($2, $4); }  
    | DEFAULT COLON statement                   { $$ = create_default_statement_node($3); }  
    | GOTO IDENTIFIER SEMICOLON                 { $$ = create_goto_statement_node($2); }  
    | CONTINUE SEMICOLON                        { $$ = create_continue_statement_node(); }
    | BREAK SEMICOLON                           { $$ = create_break_statement_node(); }  
    | RETURN return_expression SEMICOLON        { $$ = create_return_statement_node($2); }  
    | assignment_statement                      { $$ = $1; }
    ;

return_expression: expression  { $$ = $1; }
    | {$$ = NULL;};

assignment_statement :
    type_specifier IDENTIFIER EQUALS_ASSIGN expression SEMICOLON
    { $$ = create_assignment_statement_node($1, $2, $4); }
    | type_specifier IDENTIFIER SEMICOLON
    { $$ = create_assignment_statement_node($1, $2, NULL); }
    ;

type_specifier: INT 
    { $$ = create_type_node("int"); } 
    | FLOAT 
    { $$ = create_type_node("float"); } 
    | DOUBLE 
    { $$ = create_type_node("double");} 
    | CHAR 
    { $$ = create_type_node("char");} 
    | SHORT 
    { $$ = create_type_node("short");} 
    | LONG 
    { $$ = create_type_node("long");} 
    | SIGNED 
    { $$ = create_type_node("signed"); } 
    | UNSIGNED 
    { $$ = create_type_node("unsigned"); } 
    ;   

statement_list: statement { $$ = $1; }
    | statement_list statement { $$ = create_statement_list_node($1);}
    ;

%%


int main(int argc, char*arg[]) {

    parse_tree = (TreeNode*)malloc(sizeof(TreeNode*));

    int result = yyparse();

    if (result != 0) {
        printf("\e31mParsing failed.\e[0m\n");
        return 1;
    } 
    printf("\n\n");
    printf("+-----------------------------------------------------------------------+\n");
    printf("|\t\t\e[32mParsing successful. Printing parse tree:\e[0m\t\t|\n");
    printf("+-----------------------------------------------------------------------+\n");
    print_tree(parse_tree);
    
  
    return 0;
}

void yyerror(const char *msg) {
    fprintf(stderr, "Parser error: %s\n", msg);
    exit(1);
}
