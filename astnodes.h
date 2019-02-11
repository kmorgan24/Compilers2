#pragma once
//**************************************
// astnodes.h
//
// Single place that includes all the ast nodes.
// Useful for lang.y and lang.l
//
// Author: Phil Howard 
// phil.howard@oit.edu
//
// Date: Jan. 18, 2015
//
/****************************************
 * Needs:
 *      None
 * Needed By:
 *      Everything
*****************************************/
#include "cAstNode.h"

/****************************************
 * Needs:
 *      cAstNode.h
 * Needed By:
 *      cStmtsNode.h
 *      cBlockNode.h
 *      cExprNode.h
 *      cPrintNode.h
*****************************************/
#include "cStmtNode.h"   

/****************************************
 * Needs:
 *      cStmtNode.h
 * Needed By:
 *      cBlockNode.h
*****************************************/
#include "cStmtsNode.h"

/****************************************
 * Needs:
 *      cAstNode.h
 * Needed By:
 *      
*****************************************/
#include "cDeclNode.h"

/****************************************
 * Needs:
 *      "cDeclNode.h"
 * Needed By:
 *      
*****************************************/
#include "cDeclsNode.h"


/****************************************
 * Needs:
 *      "cAstNode.h"
 *      "cDeclsNode.h"
 *      "cStmtNode.h"
 *      "cStmtsNode.h"
 * Needed By:
 *      
*****************************************/
#include "cBlockNode.h"

/****************************************
 * Needs:
 *      cAstNode.h
 * Needed By:
 *      
*****************************************/
#include "cProgramNode.h"

/****************************************
 * Needs:
 *      cStmtNode.h
 * Needed By:
 *      
*****************************************/
#include "cPrintNode.h"

/****************************************
 * Needs:
 *      cStmtNode.h
 * Needed By:
 *      
*****************************************/
#include "cExprNode.h"

/****************************************
 * Needs:
 *      cAstNode.h
 * Needed By:
 *      
*****************************************/
#include "cSymbol.h"

/****************************************
 * Needs:
 *      cExprNode.h
 * Needed By:
 *      
*****************************************/
#include "cIntExprNode.h"

/****************************************
 * Needs:
 *      cExprNode.h
 * Needed By:
 *      
*****************************************/
#include "cFloatExprNode.h"

/****************************************
 * Needs:
 *      cSymbol.h
 * Needed By:
 *      
*****************************************/
#include "cSymbolTable.h"

/****************************************
 * Needs:
 *      cStmtNode.h
 * Needed By:
 *      
*****************************************/
#include "cIfStatementNode.h"

/****************************************
 * Needs:
 *      cAstNode.h
 * Needed By:
 *      
*****************************************/
#include "cOpNode.h"

/****************************************
 * Needs:
 *      cExprNode.h
 * Needed By:
 *      
*****************************************/
#include "cMathExprNode.h"

/****************************************
 * Needs:
 *      cDeclNode.h
 * Needed By:
 *      
*****************************************/
#include "cVarDeclNode.h"

/****************************************
 * Needs:
 *      cExprNode.h
 * Needed By:
 *      
*****************************************/
#include "cVarRefNode.h"

/****************************************
 * Needs:
 *      cExprNode.h
 * Needed By:
 *      
*****************************************/
#include "cReturnNode.h"

/****************************************
 * Needs:
 *      cStmtNode.h
 * Needed By:
 *      
*****************************************/
#include "cWhileStatementNode.h"
