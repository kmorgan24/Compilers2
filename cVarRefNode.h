#pragma once
//**************************************
// cStmtsNode.h
//
// Defines AST node that represents a list of statements
//
// Author: Phil Howard 
// phil.howard@oit.edu
//
#include "astnodes.h"
#include "cAstNode.h"
#include "cExprNode.h"


class cVarRefNode : public cExprNode
{
    public:
        // param is first stmt in the list of statements
        cVarRefNode(cSymbol *varref) : cExprNode()
        {
            if (!g_symbolTable.Find(varref->GetName())) {
                SemanticError("Symbol " + varref->GetName() + " not defined");
            }
            
            AddChild(varref);
        }

        // Add a statement to the list
        void Insert(cAstNode *varref)
        {
            AddChild(varref);
        }
        cDeclNode* GetType()
        {
            cDeclNode* rval = dynamic_cast<cSymbol*>(GetChild(0))->getBaseType();
            return rval;
        }
        virtual string NodeType() { return string("varref"); }
        virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }
};
