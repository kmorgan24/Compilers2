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
#include "cDeclsNode.h"

class cFuncDeclNode : public cDeclNode
{
    public:
        // param is the first decl in this decls
        cFuncDeclNode(cSymbol *type, cSymbol *name) : cDeclNode()
        {   
            if (!g_symbolTable.Find(name->GetName())) 
            {
                if (name->isType() == false) 
                {
                    //name->setType(true);
                }
                
                g_symbolTable.Insert(name);
            }
            else
            {
                name = new cSymbol(name->GetName(), false);
                g_symbolTable.Insert(name);
            }
            AddChild(type);
            AddChild(name);
        }

        // Add a decl to the list
        void Insert(cAstNode *sym)
        {
            AddChild(sym);
        }

        virtual string NodeType() { return string("func"); }
        virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }
};