%{
//**************************************
// lang.y
//
// Parser definition file. bison uses this file to generate the parser.
//
// Author: Phil Howard 
// phil.howard@oit.edu
//

#include <iostream>
#include "lex.h"
#include "astnodes.h"
#include "cSymbolTable.h"

// questions
// 0. 
// 1. 
// 2. 
// 3. 

%}

%locations

 /* union defines the type for lexical values */
%union{
    int             int_val;
    float           float_val;
    cAstNode*       ast_node;
    cProgramNode*   program_node;
    cBlockNode*     block_node;
    cStmtsNode*     stmts_node;
    cStmtNode*      stmt_node;
    cExprNode*      expr_node;
    cIntExprNode*   int_node;
    cDeclsNode*     decls_node;
    cDeclNode*      decl_node;
    cStructDeclNode* struct_node;
    cFuncDeclNode*  func_node;
    cParamNode*     param_node;
    cSymbol*        symbol;
    symbolTable_t*  sym_table; // have to do this for $$ = g_symbolTable ?
    }

%{
    int yyerror(const char *msg);

    cAstNode *yyast_root;
    bool g_semanticErrorHappened = false;
// Function that gets called when a semantic error happens
void SemanticError(std::string error)
{
    std::cout << "ERROR: " << error << " on line " 
              << yylineno << "\n";
    g_semanticErrorHappened = true;
    yynerrs++;
}
#define CHECK_ERROR() { if (g_semanticErrorHappened) \
    { g_semanticErrorHappened = false; } }
#define PROP_ERROR() { if (g_semanticErrorHappened) \
    { g_semanticErrorHappened = false; YYERROR; } }
%}

%start  program

%token <symbol>    IDENTIFIER
%token <symbol>    TYPE_ID
%token <int_val>   CHAR_VAL
%token <int_val>   INT_VAL
%token <float_val> FLOAT_VAL
%token <int_val>   AND
%token <int_val>   OR
%token <int_val>   EQUALS
%token <int_val>   NOT_EQUALS

%token  PROGRAM
%token  PRINT
%token  WHILE IF ELSE ENDIF
%token  STRUCT ARRAY
%token  RETURN
%token  JUNK_TOKEN

%type <program_node> program
%type <block_node> block
%type <sym_table> open
%type <sym_table> close
%type <decls_node> decls
%type <decl_node> decl
%type <decl_node> var_decl
%type <struct_node> struct_decl
%type <ast_node> array_decl
%type <func_node> func_decl
%type <func_node> func_header
%type <func_node> func_prefix
%type <expr_node> func_call
%type <decl_node> paramsspec
%type <decl_node> paramspec
%type <stmts_node> stmts
%type <stmt_node> stmt
%type <expr_node> lval
%type <expr_node> params
%type <param_node> param
%type <expr_node> expr
%type <expr_node> addit
%type <expr_node> term
%type <expr_node> fact
%type <expr_node> varref
%type <symbol> varpart



%%

program: PROGRAM block          { $$ = new cProgramNode($2);
                                  yyast_root = $$;
                                  if (yynerrs == 0) 
                                      YYACCEPT;
                                  else
                                      YYABORT;
                                }
block:  open decls stmts close  { $$ = new cBlockNode($2, $3);  }
    |   open stmts close        { $$ = new cBlockNode(nullptr, $2); }

open:   '{'                     {  $$ = g_symbolTable.IncreaseScope(); }

close:  '}'                     {  $$ =  g_symbolTable.DecreaseScope();  }

decls:      decls decl          { $1->Insert($2); }
        |   decl                { $$ = new cDeclsNode($1); }
decl:       var_decl ';'        { $$ = $1; }
        |   struct_decl ';'     { $$ = $1; }
        |   array_decl ';'      {  }
        |   func_decl           { $$ = $1; }
        |   error ';'           {  }

var_decl:   TYPE_ID IDENTIFIER  { $$ = new cVarDeclNode($1, $2); PROP_ERROR();}
struct_decl:  STRUCT open decls close IDENTIFIER    
                                { 
                                    $$ = new cStructDeclNode($3, $5);
                                }
array_decl: ARRAY TYPE_ID '[' INT_VAL ']' IDENTIFIER
                                { $$ = new cArrayDeclNode($2, $4, $6); }

func_decl:  func_header ';'
                                { g_symbolTable.DecreaseScope(); $$ = $1; }
        |   func_header  '{' decls stmts '}'
                                { g_symbolTable.DecreaseScope(); $1->Insert($3); $1->Insert($4); }
        |   func_header  '{' stmts '}'
                                { g_symbolTable.DecreaseScope(); $1->Insert($3); }
func_header: func_prefix paramsspec ')'
                                { $1->Insert($2); }
        |    func_prefix ')'    { $$ = $1; }
func_prefix: TYPE_ID IDENTIFIER '('
                                { g_symbolTable.IncreaseScope(); $$ = new cFuncDeclNode($1, $2); }
paramsspec: paramsspec',' paramspec 
                                { $1->Insert($3); }
        |   paramspec           { $$ = new cFuncArgsNode($1); }

paramspec:  var_decl            { $$ = $1; }

stmts:      stmts stmt          { $1->Insert($2); }
        |   stmt                { $$ = new cStmtsNode($1); }

stmt:       IF '(' expr ')' stmts ENDIF ';'
                                { $$ = new cIfStatementNode($3, $5); }
        |   IF '(' expr ')' stmts ELSE stmts ENDIF ';'
                                { $$ = new cIfStatementNode($3, $5, $7); }
        |   WHILE '(' expr ')' stmt 
                                { $$ = new cWhileStatementNode($3, $5); }
        |   PRINT '(' expr ')' ';'
                                { $$ = new cPrintNode($3); }
        |   lval '=' expr ';'   { $$ = new cAssignNode($1, $3); }
        |   lval '=' func_call ';'   { $$ = new cAssignNode($1, $3); }
        |   func_call ';'       { $$ = $1; }
        |   block               {  }
        |   RETURN expr ';'     { $$ = new cReturnNode($2); }
        |   error ';'           {}

func_call:  IDENTIFIER '(' params ')' { $$ = new cFuncCallNode($1, $3); }
        |   IDENTIFIER '(' ')'  { $$ = new cFuncCallNode($1); }

varref:   varref '.' varpart    { $1->Insert($3); }
        | varref '[' expr ']'   { $1->Insert($3); }
        | varpart               { $$ = new cVarRefNode($1); PROP_ERROR(); }

varpart:  IDENTIFIER            { $$ = $1; }

lval:     varref                { $$ = $1; }

params:     params',' param     { $1->Insert($3); }
        |   param               { $$ = $1; }

param:      expr                { $$ = new cParamNode($1); }

expr:       expr EQUALS addit   { $$ = new cMathExprNode($1, new cOpNode(EQUALS), $3); }
        |   addit               { $$ = $1; }

addit:      addit '+' term      { $$ = new cMathExprNode($1, new cOpNode('+'), $3); }
        |   addit '-' term      { $$ = new cMathExprNode($1, new cOpNode('-'), $3); }
        |   term                { $$ = $1; }

term:       term '*' fact       { $$ = new cMathExprNode($1, new cOpNode('*'), $3);  }
        |   term '/' fact       { $$ = new cMathExprNode($1, new cOpNode('/'), $3); }
        |   term '%' fact       { $$ = new cMathExprNode($1, new cOpNode('%'), $3); }
        |   fact                { $$ = $1; }

fact:        '(' expr ')'       { $$= $2; }
        |   INT_VAL             { $$ = new cIntExprNode($1); }
        |   FLOAT_VAL           { $$ = new cFloatExprNode($1); }
        |   varref              { $$ = $1; }

%%

// Function to format error messages
int yyerror(const char *msg)
{
    std::cerr << "ERROR: " << msg << " at symbol "
        << yytext << " on line " << yylineno << "\n";

    return 0;
}
