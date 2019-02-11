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

class cWhileStatementNode : public cStmtNode
{
    public:
        // param is the value to be printed
        cWhileStatementNode(cExprNode *expr, cStmtNode* stmt) : cStmtNode()
        {
            AddChild(expr);
            AddChild(stmt);
        }
       
        virtual string NodeType() { return string("while"); }
        virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }
};