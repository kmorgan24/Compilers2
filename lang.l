%{
//**************************************
// lang.l
//
// scanner definition file. flex uses this file to create the scanner
//
// Author: <<<< insert your name here >>>>
//

#include "lex.h"
#include "langparse.h"
#include "cSymbolTable.h"
#include "astnodes.h"


// Macros that can be used to create debug output from the scanner
// The first one does NOT create debug output, the second does.
// Uncomment one or the other then use DO_RETURN(val) for all your return 
// statements
#define DO_RETURN(a) { return (a); }
//#define DO_RETURN(a) { return Return(a); }

int Return(int val);

%}

%option noyywrap
%option noinput
%option nounput
%option yylineno


    /* definitions go here. period is an example. */
    /* NOTE: You do not need to use definitions */
period          ['.']
%%

    // token definitions. I gave "program" as an example
"program"                   DO_RETURN(PROGRAM);
"if"                        DO_RETURN(IF);
"else"                      DO_RETURN(ELSE);
"while"                     DO_RETURN(WHILE);
"print"                     DO_RETURN(PRINT);
"int"                       DO_RETURN(INT_VAL);
"float"                     DO_RETURN(FLOAT_VAL);
"struct"                    DO_RETURN(STRUCT);
"return"                    DO_RETURN(RETURN);
"array"                     DO_RETURN(ARRAY);
"char"                      DO_RETURN(CHAR_VAL);
"endif"			            DO_RETURN(ENDIF);
"("                         DO_RETURN('(');
")"                         DO_RETURN(')');
"{"                         {
				                /*g_symbolTable.IncreaseScope()*/;
				                return yytext[0];
			                };
"}"                         {
				                /*g_symbolTable.DecreaseScope()*/;
				                return yytext[0];
			                };
"["                         DO_RETURN('[');
"]"                         DO_RETURN(']');
";"                         DO_RETURN(';');
","                         DO_RETURN(',');
"."                         DO_RETURN('.');
"+"                         DO_RETURN('+');
"-"                         DO_RETURN('-');
"*"                         DO_RETURN('*');
"/"                         DO_RETURN('/');
"%"                         DO_RETURN('%');
"="                         DO_RETURN('=');
"=="                        DO_RETURN(EQUALS);
"&&"                        DO_RETURN(AND);
"||"                        DO_RETURN(OR);
" "                         {};
"\t"                        {};
"\n"                        {};
[0-9]+\.[0-9]+              {
                                yylval.float_val = atof(yytext);
                                DO_RETURN(FLOAT_VAL);
                            };
[0-9]*                      {
                                yylval.int_val = atoi(yytext);
                                DO_RETURN(INT_VAL);
                            }

[/][/].*$                   {};
[a-zA-Z_][0-9a-zA-Z_]*      {
				                /*yylval.symbol = g_symbolTable.FindLocal(yytext);
                                if(yylval.symbol == nullptr) yylval.symbol = new cSymbol(yytext);
				                g_symbolTable.Insert(yylval.symbol);*/
                                return IDENTIFIER;
                            };
. DO_RETURN(JUNK_TOKEN);

%%

// This function allows us to do extra processing on each token
// It is used to generate lexer debug info
int Return(int val)
{
    printf("Scanned '%s': %d\n", yytext, val);
    return val;
}
