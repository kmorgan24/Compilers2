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
                name->setBaseType(dynamic_cast<cBaseTypeNode*>(type->getBaseType()));
                name->SetDecl(this);
                g_symbolTable.Insert(name);
            }
            else
            {
                cSymbol* temp = g_symbolTable.FindLocal(name->GetName());
                if (temp) 
                {
                    if (temp->getBaseType() != type->getBaseType()) 
                    {
                        SemanticError(name->GetName() + " previously defined with different return type");
                    }
                    //cFuncDeclNode* funcsdecls = temp->GetDecl();
                    // if () // check if already defined with more params
                    // {
                    //     /* code */
                    // }
                    // if (/* condition */) // check if defined with different params
                    // {
                    //     /* code */
                    // }
                    
                }
                
                name = new cSymbol(name->GetName(), false);
                name->setBaseType(dynamic_cast<cBaseTypeNode*>(type->getBaseType()));
                name->SetDecl(this);
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