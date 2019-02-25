#pragma once
//**************************************
// cFloatExprNode.h
//
// Defines an AST node for an float constant (literals).
//
// Inherits from cExprNode so that integer constants can be used anywhere 
// expressions are used.
//
// Author: Kyronn Morgan
//
#include "astnodes.h"
#include "cAstNode.h"
#include "cExprNode.h"
#include "cSymbolTable.h"

class cFloatExprNode : public cExprNode
{
    public:
        // param is the value of the integer constant
        cFloatExprNode(float value) : cExprNode()
        {
            m_value = value;
            m_type = dynamic_cast<cBaseTypeNode*>(g_symbolTable.Find("float")->getBaseType());
        }

        virtual string AttributesToString() 
        {
            return " value=\"" + std::to_string(m_value) + "\"";
        }
        cDeclNode* GetType()
        {
            return m_type;
        }
        virtual string NodeType() { return string("float"); }
        virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }
    protected:
        float m_value;        // value of integer constant (literal)
        cBaseTypeNode* m_type;
};