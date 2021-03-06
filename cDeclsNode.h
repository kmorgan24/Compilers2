#pragma once
//**************************************
// cDeclsNode.h
//
// Defines a class to represent a list of declarations.
//
// Author: Phil Howard
// phil.howard@oit.edu
//
// Date: Nov. 28, 2015
//

#include "cAstNode.h"
#include "cDeclNode.h"

class cDeclsNode : public cAstNode
{
  public:
    // param is the first decl in this decls
    cDeclsNode(cDeclNode *decl) : cAstNode()
    {
        AddChild(decl);
    }

    // Add a decl to the list
    void Insert(cDeclNode *decl)
    {
        AddChild(decl);
    }

    int NumDecls() { return NumChildren(); }

    cDeclNode *GetDecl(int index)
    {
        return (cDeclNode *)GetChild(index);
    }

    // return the XML node name
    virtual string NodeType() { return string("decls"); }
    virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }
    void SetSize(int s)
    {
        m_sizeDecl = s;
    }
    void SetOffset(int o)
    {
        m_offsetDecl = o;
    }
    virtual string AttributesToString()
    {
        string rval = "";
        if (m_sizeDecl != 0)
        {
            rval = " size=\"" + std::to_string(m_sizeDecl) + "\"";
        }

        return rval;
    }

  private:
    int m_sizeDecl;
    int m_offsetDecl;
};
