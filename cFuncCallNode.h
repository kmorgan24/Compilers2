#pragma once
//**************************************
// cStmtsNode.h
//
// Defines AST node that represents a list of statements
//
// Author: Phil Howard 
// phil.howard@oit.edu
//

#include "cAstNode.h"
#include "cSymbol.h"
#include "cExprNode.h"


class cFuncCallNode : public cExprNode
{
    public:
        // param is first stmt in the list of statements
        cFuncCallNode(cSymbol *symb) : cExprNode()
        {
            AddChild(symb);
        }
        cFuncCallNode(cSymbol * symb, cExprNode* expr) : cExprNode()
        {     
            AddChild(symb);
            AddChild(expr);
           }
        // Add a statement to the list
        void Insert(cAstNode *varref)
        {
            AddChild(varref);
        }

        virtual string NodeType() { return string("funcCall"); }
        virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }
};
