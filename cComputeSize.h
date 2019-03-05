#pragma once

#include "cVisitor.h"
#include "astnodes.h"
class cComputeSize : public cVisitor
{
    int m_offset;
    int m_highWater;

  public:
    cComputeSize() : cVisitor()
    {
        m_offset = 0;
        m_highWater = 0;
    }

    void Visit(cBlockNode *node)
    {
        int startH = m_highWater;
        int startOff = m_offset;

        m_highWater = m_offset;
        VisitAllChildren(node);

        if (m_offset > m_highWater)
        {
            m_highWater = m_offset;
        }

        node->SetSize(m_highWater - startOff);

        if (startH > m_highWater)
        {
            m_highWater = startH;
        }

        m_offset = startOff;
    }
    void Visit(cDeclNode *node) { VisitAllChildren(node); }
    void Visit(cDeclsNode *node)
    {
        int startOff = m_offset;
        VisitAllChildren(node);
        node->SetSize(m_offset - startOff);
    }

    void Visit(cFuncDeclNode *node)
    {
        int startOff = m_offset;
        int startH = m_highWater;
        m_offset = 0;
        m_highWater = 0;
        VisitAllChildren(node);
        while (m_offset % 4 != 0)
        {
            ++m_offset;
        }

        node->SetSize(m_offset);
        node->SetOffset(startOff - 8);
        m_offset = startOff;
        m_highWater = startH;
    }

    void Visit(cParamListNode *node) { VisitAllChildren(node); }

    void Visit(cStructDeclNode *node) { VisitAllChildren(node); }

    void Visit(cVarDeclNode *node)
    {
        int itemsize = node->Sizeof();
        while (m_offset % 4 != 0 && itemsize != 1)
        {
            ++m_offset;
        }
        node->SetOffset(m_offset);

        m_offset += itemsize;
        if (m_offset > m_highWater)
        {
            m_highWater = m_offset;
            // while (m_highWater % 4 != 0)
            // {
            //     ++m_highWater;
            // }
        }
    }

    virtual void VisitAllNodes(cAstNode *node)
    {
        VisitAllChildren(node);
    }

    // dont need?

    void Visit(cSymbol *node) { VisitAllChildren(node); }
    void Visit(cPrintNode *node) { VisitAllChildren(node); }
    void Visit(cReturnNode *node) { VisitAllChildren(node); }
    void Visit(cStmtNode *node) { VisitAllChildren(node); }
    void Visit(cStmtsNode *node) { VisitAllChildren(node); }
    void Visit(cFuncExprNode *node) { VisitAllChildren(node); }
    void Visit(cIfNode *node) { VisitAllChildren(node); }
    void Visit(cIntExprNode *node) { VisitAllChildren(node); }
    void Visit(cOpNode *node) { VisitAllChildren(node); }
    void Visit(cExprNode *node) { VisitAllChildren(node); }
    void Visit(cFloatExprNode *node) { VisitAllChildren(node); }
    void Visit(cAstNode *node) { VisitAllChildren(node); }
    void Visit(cAssignNode *node) { VisitAllChildren(node); }
    void Visit(cBinaryExprNode *node) { VisitAllChildren(node); }
    void Visit(cVarExprNode *node) { VisitAllChildren(node); }
    void Visit(cWhileNode *node) { VisitAllChildren(node); }
};