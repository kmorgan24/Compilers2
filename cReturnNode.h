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
#include "cExprNode.h"


class cReturnNode : public cExprNode
{
    public:
        // param is first stmt in the list of statements
        cReturnNode(cAstNode *varref) : cExprNode()
        {
            AddChild(varref);
        }

        // Add a statement to the list
        void Insert(cAstNode *varref)
        {
            AddChild(varref);
        }

        virtual string NodeType() { return string("return"); }
        virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }
};
