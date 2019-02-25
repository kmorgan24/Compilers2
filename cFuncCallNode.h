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
            if (g_symbolTable.Find(symb->GetName()) != nullptr) {
                
                if (symb->GetDecl()== nullptr) {
                    SemanticError(symb->GetName() + "is not a function");
                }
                
            }
            else
            {
                SemanticError(symb->GetName() + "is not declared");
            }
            
            
            AddChild(symb);
        }
        cFuncCallNode(cSymbol * symb, cExprNode* expr) : cExprNode()
        {   
            if (g_symbolTable.Find(symb->GetName()) != nullptr) {
               if (symb->GetDecl()== nullptr) {
                    SemanticError(symb->GetName() + "is not a function");
                }
            }
            else
            {
                SemanticError(symb->GetName() + "is not declared");
            }  
            symb->setBaseType(dynamic_cast<cBaseTypeNode*>(g_symbolTable.Find(symb->GetName())->getBaseType()));
            AddChild(symb);
            AddChild(expr);
           }
        // Add a statement to the list
        void Insert(cAstNode *varref)
        {
            AddChild(varref);
        }
        cDeclNode* GetType()
        {
            return dynamic_cast<cDeclNode*>(dynamic_cast<cSymbol*>(GetChild(0))->getBaseType());
        }

        virtual string NodeType() { return string("funcCall"); }
        virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }
};
