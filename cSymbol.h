#pragma once
//**************************************
// cSymbol.h
//
// Defines class used to represent symbols.
// Later labs will add features to this class.
//
// Author: Phil Howard 
// phil.howard@oit.edu
//

#include <string>

using std::string;

#include "cAstNode.h"
#include "cBaseTypeNode.h"

class cSymbol : public cAstNode
{
    public:
        // param is name of symbol
        cSymbol(string name) : cAstNode()
        {
            m_id = ++nextId;        // get next available ID
            m_name = name;
            type = false;
        }
        cSymbol(string name, bool istype) : cAstNode()
        {
            m_id = ++nextId;        // get next available ID
            m_name = name;
            type = istype;
        }
        // return name of symbol
        string GetName() { return m_name; }
        cDeclNode* GetDecl(){return m_decl;}
        void SetDecl(cDeclNode* decl){m_decl = decl;}
        bool isType() {return type;}
        void setType(bool t) { type = t;}
        void setBaseType(cBaseTypeNode* base){ m_base = base; }
        cBaseTypeNode* getBaseType(){return m_base;}

        virtual string AttributesToString()
        {
            string result(" id=\"");
            result += std::to_string(m_id);
            result += "\" name=\"" + m_name + "\"";
            return result;
        }
        virtual string NodeType() { return string("sym"); }
        virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }
    protected:
        static long long nextId;        // Next avail symbol ID
        long long m_id;                 // Unique ID for this symbol
        string m_name;                  // name of symbol
        bool type;
        cDeclNode* m_decl;
        cBaseTypeNode* m_base;
};
