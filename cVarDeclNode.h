#pragma once
//**************************************
// cDeclsNode.h
//
// Defines a class to represent a list of declarations.
//
// Author: Phil Howard 
// phil.howard@oit.edu
//
#include "astnodes.h"
#include "cAstNode.h"

#include "cDeclNode.h"

class cVarDeclNode : public cDeclNode
{
    public:
        // param is the first decl in this decls
        cVarDeclNode(cSymbol *type, cSymbol *name) : cDeclNode()
        {
                if(!g_symbolTable.Find(name->GetName()))
                {
                     name = new cSymbol(name->GetName());
                     g_symbolTable.Insert(name);
                }
              

            AddChild(type);
            AddChild(name);
        }

        // Add a decl to the list
        void Insert(cSymbol *sym)
        {
            AddChild(sym);
        }

        virtual string NodeType() { return string("var_decl"); }
        virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }
};