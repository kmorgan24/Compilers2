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
#include "cStmtNode.h"

class cVarRefNode : public cExprNode
{
    public:
        // param is first stmt in the list of statements
        cVarRefNode(cAstNode *varref) : cExprNode()
        {
            AddChild(varref);
        }

        // Add a statement to the list
        void Insert(cAstNode *varref)
        {
            AddChild(varref);
        }

        virtual string NodeType() { return string("varref"); }
        virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }
};
