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
        //EmitString("main:\n");
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
    void Visit(cVarExprNode *node)
    {
        VisitAllChildren(node);
        EmitString("PUSHVAR ");
        EmitInt(node->GetOffset());
        EmitString("\n");
    }
    void Visit(cAssignNode *node)
    {
        VisitAllChildren(node);
        EmitString("POPVAR ");
        EmitInt(node->GetLval()->GetOffset());
        EmitString("\n");
    }
    void Visit(cBinaryExprNode *node)
    {
        VisitAllChildren(node);
        string temp = node->GetOperator()->GetOpAsString();
        if (temp.compare("+") == 0)
        {
            EmitString("PLUS\n");
        }
        else if (temp.compare("-") == 0)
        {
            EmitString("MINUS\n");
        }
        else if (temp.compare("*") == 0)
        {
            EmitString("TIMES\n");
        }
        else if (temp.compare("/") == 0)
        {
            EmitString("DIVIDE\n");
        }
        else if (temp.compare("==") == 0)
        {
            EmitString("EQ\n");
        }
        else if (temp.compare("!=") == 0)
        {
            EmitString("NE\n");
        }
        else if (temp.compare("||") == 0)
        {
            EmitString("OR\n");
        }
        else if (temp.compare("&&") == 0)
        {
            EmitString("AND\n");
        }
    }
    void Visit(cOpNode *node)
    {
        VisitAllChildren(node);
    }
    void Visit(cFuncExprNode *node)
    {
        EmitString(node->GetSymbol()->GetName() + ":\n");
        VisitAllChildren(node);
    }
    void Visit(cParamListNode *node)
    {
        VisitAllChildren(node);
    }
    void Visit(cIfNode *node)
    {
        string endofif = GenerateLabel();
        string endofelse = GenerateLabel();
        node->GetCond()->Visit(this);
        //VisitAllChildren(node);
        EmitString("JUMPE @" + endofif + "\n");
        (node->GetIf()->Visit(this));
        EmitString("JUMP @" + endofelse + "\n");
        EmitString(endofif + ":\n");
        if (node->GetElse() != nullptr)
        {
            node->GetElse()->Visit(this);
        }
        EmitString(endofelse + ":\n");
    }
    void Visit(cWhileNode *node)
    {
        string startOfWhile = GenerateLabel();
        string endOfWhile = GenerateLabel();
        EmitString(startOfWhile + ":\n");
        node->GetCondition()->Visit(this);

        EmitString("JUMPE @" + endOfWhile + "\n");
        node->GetStmt()->Visit(this);
        EmitString("JUMP @" + startOfWhile + "\n");
        EmitString(endOfWhile + ":\n");
    }

    // void Visit(cExprNode *node) { VisitAllChildren(node); }
    // void Visit(cParamsNode *node) { VisitAllChildren(node); }
    // void Visit(cReturnNode *node) { VisitAllChildren(node); }
};