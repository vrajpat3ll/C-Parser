%{
#include <stdio.h>
#include <stdlib.h>
#include "parse.tab.h" // Include the parser header file
int whitespace = 0;
%}

%%

[ \n\t]+                        { whitespace++; }  // Skip whitespace and newlines
"int"                           { yylval.str = strdup(yytext); printf("INT\t\t-> %s\n", yytext); return INT;}
"short"                         { yylval.str = strdup(yytext); printf("SHORT\t\t-> %s\n", yytext); return SHORT;}
"float"                         { yylval.str = strdup(yytext); printf("FLOAT\t\t-> %s\n", yytext); return FLOAT;}
"long"                          { yylval.str = strdup(yytext); printf("LONG\t\t-> %s\n", yytext); return LONG;}
"double"                        { yylval.str = strdup(yytext); printf("DOUBLE\t\t-> %s\n", yytext); return DOUBLE;}
"char"                          { yylval.str = strdup(yytext); printf("CHAR\t\t-> %s\n", yytext); return CHAR;}
"signed"                        { yylval.str = strdup(yytext); printf("SIGNED\t\t-> %s\n", yytext); return SIGNED;}
"unsigned"                      { yylval.str = strdup(yytext); printf("UNSIGNED\t-> %s\n", yytext); return UNSIGNED;}
"goto"                          { yylval.str = strdup(yytext); printf("GOTO\t\t-> %s\n", yytext); return GOTO;}
"continue"                      { yylval.str = strdup(yytext); printf("CONTINUE\t-> %s\n", yytext); return CONTINUE;}
"break"                         { yylval.str = strdup(yytext); printf("BREAK\t\t-> %s\n", yytext); return BREAK;}
"return"                        { yylval.str = strdup(yytext); printf("RETURN\t\t-> %s\n", yytext); return RETURN;}
"switch"                        { yylval.str = strdup(yytext); printf("SWITCH\t\t-> %s\n", yytext); return SWITCH;}
"case"                          { yylval.str = strdup(yytext); printf("CASE\t\t-> %s\n", yytext); return CASE;}
"default"                       { yylval.str = strdup(yytext); printf("DEFAULT\t\t-> %s\n", yytext); return DEFAULT;}
[A-Za-z_][A-Za-z0-9_]*          { yylval.str = strdup(yytext); printf("IDENTIFIER\t-> %s\n", yytext); return IDENTIFIER; }
\"(?:[^"\\]|\\.)*\"             { yylval.str = strdup(yytext); printf("STRING LITERAL\t-> %s\n", yytext);return STRING_LITERAL; }
[0-9]+                          { yylval.str = strdup(yytext); printf("CONSTANT\t-> %s\n", yytext); return CONSTANT; } // for temporary 
\(                              { yylval.str = strdup(yytext); printf("LEFT_PAREN\t-> %s\n", yytext); return LEFT_PAREN; }
\)                              { yylval.str = strdup(yytext); printf("RIGHT_PAREN\t-> %s\n", yytext); return RIGHT_PAREN; }
\{                              { yylval.str = strdup(yytext); printf("LEFT_CURLY\t-> %s\n", yytext); return LEFT_CURLY; }
\}                              { yylval.str = strdup(yytext); printf("RIGHT_CURLY\t-> %s\n", yytext); return RIGHT_CURLY; }
\;                              { yylval.str = strdup(yytext); printf("SEMICOLON\t-> %s\n", yytext); return SEMICOLON; }
\:                              { yylval.str = strdup(yytext); printf("COLON\t\t-> %s\n", yytext); return COLON; }
"="                             { yylval.str = strdup(yytext); printf("EQUALS_ASSIGN\t-> %s\n", yytext); return EQUALS_ASSIGN;}
. { printf("Number of whitespaces = %d.\nInvalid character found:{ %s\n}\n",whitespace, yytext); exit(1); } // Error for unknown characters


%%

int yywrap(void) {
    return 1;
}