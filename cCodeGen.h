#pragma once
#include "emit.h"

class cCodeGen : public cVisitor
{
  private:
    int m_firstRun = 0;

  public:
    cCodeGen(std::string filename)
    {
        InitOutput(filename.c_str());
    }
    ~cCodeGen()
    {
        FinalizeOutput();
    }
    virtual void VisitAllChildren(cAstNode *node)
    {
        cAstNode::iterator it;
        for (it = node->FirstChild(); it != node->LastChild(); it++)
        {
            if ((*it) != nullptr)
                (*it)->Visit(this);
        }
    }
    virtual void VisitAllNodes(cAstNode *node)
    {
        VisitAllChildren(node);
    }

    void Visit(cProgramNode *node)
    {
        EmitString("main:\n");
    }
    void Visit(cIntExprNode *node)
    {
        EmitString("PUSH ");
        EmitInt(node->GetValue());
        EmitString("\n");
    }

    void Visit(cPrintNode *node)
    {
        node->GetExpr()->Visit(this);
        EmitString("CALL @print\n");
        EmitString("POP\n");
        EmitString("POP\n");
    }
    void Visit(cBlockNode *node)
    {
        if (m_firstRun == 0)
        {
            m_firstRun++;
            EmitString("main:\n");
        }

        VisitAllChildren(node);
    }
    // void Visit(cAstNode *node) { VisitAllChildren(node); }
    // void Visit(cAssignNode *node) { VisitAllChildren(node); }
    // void Visit(cBinaryExprNode *node) { VisitAllChildren(node); }

    // void Visit(cDeclNode *node) { VisitAllChildren(node); }
    // void Visit(cDeclsNode *node) { VisitAllChildren(node); }
    // void Visit(cExprNode *node) { VisitAllChildren(node); }
    // void Visit(cFloatExprNode *node) { VisitAllChildren(node); }
    // void Visit(cFuncDeclNode *node) { VisitAllChildren(node); }
    // void Visit(cFuncExprNode *node) { VisitAllChildren(node); }
    // void Visit(cIfNode *node) { VisitAllChildren(node); }

    // void Visit(cOpNode *node) { VisitAllChildren(node); }
    // void Visit(cParamListNode *node) { VisitAllChildren(node); }
    // void Visit(cParamsNode *node) { VisitAllChildren(node); }

    // void Visit(cReturnNode *node) { VisitAllChildren(node); }
    // void Visit(cStmtNode *node) { VisitAllChildren(node); }
    // void Visit(cStmtsNode *node) { VisitAllChildren(node); }
    // void Visit(cStructDeclNode *node) { VisitAllChildren(node); }
    // void Visit(cSymbol *node) { VisitAllChildren(node); }
    // void Visit(cVarDeclNode *node) { VisitAllChildren(node); }
    // void Visit(cVarExprNode *node) { VisitAllChildren(node); }
    // void Visit(cWhileNode *node) { VisitAllChildren(node); }
    // void Visit(cBaseTypeNode *node) { VisitAllChildren(node); }
};