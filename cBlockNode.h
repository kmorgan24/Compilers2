#pragma once
//**************************************
// cBlockNode.h
//
// Defines AST node for a block of code (stuff inside {})
//
// Since blocks can take the place of statements, this class inherits from
// cStmtNode
//
// Author: Phil Howard
// phil.howard@oit.edu
//
// Date: Jan. 18, 2016
//

#include "cAstNode.h"
#include "cDeclsNode.h"
#include "cStmtNode.h"
#include "cStmtsNode.h"

class cBlockNode : public cStmtNode
{
  public:
    // params are the decls and statements contained in the block
    cBlockNode(cDeclsNode *decls, cStmtsNode *statements)
        : cStmtNode()
    {
        AddChild(decls);
        AddChild(statements);
    }

    virtual string NodeType() { return string("block"); }
    virtual void Visit(cVisitor *visitor) { visitor->Visit(this); }
    void SetSize(int s)
    {
        m_sizeblock = s;
    }
    int GetSize() { return m_sizeblock; }
    int Sizeof() { return GetSize(); }
    virtual string AttributesToString()
    {
        string rval = "";
        if (m_sizeblock != 0)
        {
            rval = " size=\"" + std::to_string(m_sizeblock) + "\"";
        }

        return rval;
    }

  private:
    int m_sizeblock;
};
