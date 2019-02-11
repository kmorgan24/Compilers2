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
    cSymbol*        symbol;
    symbolTable_t*  sym_table; // have to do this for $$ = g_symbolTable ?
    }

%{
    int yyerror(const char *msg);

    cAstNode *yyast_root;
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
%type <ast_node> struct_decl
%type <ast_node> array_decl
%type <ast_node> func_decl
%type <ast_node> func_header
%type <ast_node> func_prefix
%type <ast_node> func_call
%type <ast_node> paramsspec
%type <ast_node> paramspec
%type <stmts_node> stmts
%type <stmt_node> stmt
%type <expr_node> lval
%type <ast_node> params
%type <ast_node> param
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

decls:      decls decl          { $1->AddChild($2); }
        |   decl                { $$ = new cDeclsNode($1); }
decl:       var_decl ';'        { $$ = $1; }
        |   struct_decl ';'     {  }
        |   array_decl ';'      {  }
        |   func_decl           {  }
        |   error ';'           {  }

var_decl:   TYPE_ID IDENTIFIER  { $$ = new cVarDeclNode($1, $2); }
struct_decl:  STRUCT open decls close IDENTIFIER    
                                {  }
array_decl: ARRAY TYPE_ID '[' INT_VAL ']' IDENTIFIER
                                {  }

func_decl:  func_header ';'
                                {  }
        |   func_header  '{' decls stmts '}'
                                {  }
        |   func_header  '{' stmts '}'
                                {  }
func_header: func_prefix paramsspec ')'
                                {  }
        |    func_prefix ')'    {  }
func_prefix: TYPE_ID IDENTIFIER '('
                                {  }
paramsspec: paramsspec',' paramspec 
                                {  }
        |   paramspec           {  }

paramspec:  var_decl            {  }

stmts:      stmts stmt          { $1->AddChild($2); }
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
        |   lval '=' func_call ';'   {  }
        |   func_call ';'       {  }
        |   block               {  }
        |   RETURN expr ';'     { $$ = new cReturnNode($2); }
        |   error ';'           {}

func_call:  IDENTIFIER '(' params ')' {  }
        |   IDENTIFIER '(' ')'  {  }

varref:   varref '.' varpart    {  }
        | varref '[' expr ']'   {  }
        | varpart               { $$ = new cVarRefNode($1); }

varpart:  IDENTIFIER            { $$ = $1; }

lval:     varref                { $$ = $1; }

params:     params',' param     {  }
        |   param               {  }

param:      expr                {  }

expr:       expr EQUALS addit   {  }
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
