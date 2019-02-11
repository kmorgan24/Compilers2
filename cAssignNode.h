#pragma once
//**************************************
// cPrintNode.h
//
// Defines AST node for print statements
//
// Inherits from cStmtNode so print statments can go in statement lists, and be
// used anywhere a statement is legal.
//
// Author: Phil Howard 
// phil.howard@oit.edu
//

#include "cAstNode.h"
#include "cStmtNode.h"
#include "cStmtsNode.h"
#include "cExprNode.h"

class cAssignNode : public cStmtNode
{
    public:
        // param is the value to be printed
        cAssignNode(cExprNode *lval, cExprNode* expr) : cStmtNode()
        {
            AddChild(lval);
            AddChild(expr);
        }
       
        virtual string NodeType() { return string("assign"); }
        virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }
};