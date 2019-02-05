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

#include "cAstNode.h"
#include "cSymbol.h"
#include "cStmtNode.h"
#include "cStmtsNode.h"
#include "cDeclNode.h"
#include "cDeclsNode.h"



#include "cBlockNode.h"
#include "cProgramNode.h"
#include "cPrintNode.h"
#include "cExprNode.h"
#include "cIntExprNode.h"
#include "cFloatExprNode.h"
#include "cSymbolTable.h"
#include "cOpNode.h"
#include "cMathExprNode.h"
#include "cVarDeclNode.h"
#include "cVarRefNode.h"