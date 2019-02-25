#pragma once
#include "astnodes.h"
#include "cDeclNode.h"

class cBaseTypeNode : public cDeclNode
{
    protected:
    string m_name;
    int m_size; 
    bool m_isFloat;
    bool m_isInt;
    bool m_isChar;
    public:
    cBaseTypeNode(string name, int size, bool isfloat) : cDeclNode()
    {
        m_name = name;
        m_size = size;
        m_isFloat = isfloat;
        m_isChar = false;
        m_isInt = false;
        if (!m_isFloat) {
            if(name == "char")
            {
                m_isChar = true;
            }
            else
            {
                m_isInt = true;
            }
            
        }
        
    }
    bool isFloat(){return m_isFloat;}
    bool isInt(){return m_isInt;}
    bool isChar(){return m_isChar;}

        virtual string NodeType() { return string("base_decl"); }
        virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }
};