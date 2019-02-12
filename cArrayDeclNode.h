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

class cArrayDeclNode : public cDeclNode
{
    int m_count;
    public:
        // param is the first decl in this decls
        cArrayDeclNode(cSymbol* type, int count, cSymbol *name) : cDeclNode()
        {   
            m_count = count;
            if (!g_symbolTable.Find(name->GetName())) 
            {
                if (name->isType() == false) 
                {
                    name->setType(true);
                }
                
                g_symbolTable.Insert(name);
            }
            else
            {
                name = new cSymbol(name->GetName(), true);
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

        virtual string NodeType() { return string("array_decl"); }
        virtual string AttributesToString() {return string(" count=\""+std::to_string(m_count)+ '"');}
        virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }

};