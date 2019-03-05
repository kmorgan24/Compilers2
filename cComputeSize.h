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
    void Visit(cAstNode *node) { VisitAllChildren(node); }
    void Visit(cAssignNode *node) { VisitAllChildren(node); }
    void Visit(cBinaryExprNode *node) { VisitAllChildren(node); }
    void Visit(cBlockNode *node)
    {
        VisitAllChildren(node);
        node->SetSize(m_highWater);
    }
    void Visit(cDeclNode *node) { VisitAllChildren(node); }
    void Visit(cDeclsNode *node)
    {
        VisitAllChildren(node);
        node->SetSize(m_offset);
    }
    void Visit(cExprNode *node) { VisitAllChildren(node); }
    void Visit(cFloatExprNode *node) { VisitAllChildren(node); }
    void Visit(cFuncDeclNode *node) { VisitAllChildren(node); }
    void Visit(cFuncExprNode *node) { VisitAllChildren(node); }
    void Visit(cIfNode *node) { VisitAllChildren(node); }
    void Visit(cIntExprNode *node) { VisitAllChildren(node); }
    void Visit(cOpNode *node) { VisitAllChildren(node); }
    void Visit(cParamListNode *node) { VisitAllChildren(node); }
    void Visit(cPrintNode *node) { VisitAllChildren(node); }
    void Visit(cReturnNode *node) { VisitAllChildren(node); }
    void Visit(cStmtNode *node) { VisitAllChildren(node); }
    void Visit(cStmtsNode *node) { VisitAllChildren(node); }
    void Visit(cStructDeclNode *node) { VisitAllChildren(node); }
    void Visit(cSymbol *node) { VisitAllChildren(node); }
    void Visit(cVarDeclNode *node)
    {
        node->SetOffset(m_offset);
        m_offset += node->Sizeof();
        m_highWater = m_offset;
    }
    void Visit(cVarExprNode *node) { VisitAllChildren(node); }
    void Visit(cWhileNode *node) { VisitAllChildren(node); }
    virtual void VisitAllNodes(cAstNode *node)
    {
        VisitAllChildren(node);
    }
};