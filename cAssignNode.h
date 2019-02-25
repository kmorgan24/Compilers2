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
#include "astnodes.h"
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
            bool ischar=dynamic_cast<cBaseTypeNode*>(lval->GetType())->isChar();
            if ( ischar )
            {
                bool isint = dynamic_cast<cBaseTypeNode*>(expr->GetType())->isInt();
                if (isint) {
                    SemanticError("Cannot assign int to char");
                }
                bool isfloat = dynamic_cast<cBaseTypeNode*>(expr->GetType())->isFloat();
                if (isfloat) {
                    SemanticError("Cannot assign float to char");
                }
            }
            else if (dynamic_cast<cBaseTypeNode*>(lval->GetType())->isInt()) {
                if (dynamic_cast<cBaseTypeNode*>(expr->GetType())->isFloat()) {
                    SemanticError("Cannot assign float to int");
                }
            }
            AddChild(lval);
            AddChild(expr);
        }
       
        virtual string NodeType() { return string("assign"); }
        virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }
};