#pragma once
//**************************************
// cDeclsNode.h
//
// Defines a class to represent a list of declarations.
//
// Author: Phil Howard 
// phil.howard@oit.edu
//

#include "cAstNode.h"
#include "cDeclNode.h"

class cFuncArgsNode : public cDeclNode
{
    public:
        // param is the first decl in this decls
        cFuncArgsNode(cDeclNode *decl) : cDeclNode()
        {
            AddChild(decl);
        }

        // Add a decl to the list
        void Insert(cDeclNode *decl)
        {
            AddChild(decl);
        }

        virtual string NodeType() { return string("args"); }
        virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }
};