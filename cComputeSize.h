#pragma once

#include "cVisitor.h"
#include "astnodes.h"
#define WORD_SIZE 8
class cComputeSize : public cVisitor
{
    int m_offset;
    int m_highWater;
    void Align()
    {
        while (m_offset % 4 != 0)
        {
            ++m_offset;
        }
    }

  public:
    cComputeSize() : cVisitor()
    {
        m_offset = 0;
        m_highWater = 0;
    }

    virtual void Visit(cBlockNode *node)
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
    virtual void Visit(cDeclNode *node) { VisitAllChildren(node); }
    virtual void Visit(cDeclsNode *node)
    {
        int startOff = m_offset;
        VisitAllChildren(node);
        node->SetSize(m_offset - startOff);
    }

    virtual void Visit(cFuncDeclNode *node)
    {
        int startOff = m_offset;
        int startH = m_highWater;
        VisitAllChildren(node);
        m_offset = 0;
        m_highWater = 0;

        //Align();
        if (m_offset > m_highWater)
        {
            m_highWater = m_offset;
        }

        //node->SetSize(m_highWater);

        //manual visit
        //get rvalue size
        int sizerval = node->GetType()->Sizeof();
        //get params size
        int sizeparams = 0;
        cDeclsNode *params = node->GetParams();
        if (params != nullptr)
        {
            for (int i = 0; i < params->NumDecls(); i++)
            {
                int off = sizeparams;
                sizeparams += params->GetDecl(i)->Sizeof();
                while (sizeparams % 4 != 0)
                {
                    ++sizeparams;
                }

                params->GetDecl(i)->SetOffset(off);
            }
            params->SetSize(sizeparams);
        }

        //get decls size
        cDeclsNode *funcdecls = node->GetLocals();
        m_offset = sizeparams;
        int sizelocals = 0;
        for (int i = 0; i < funcdecls->NumDecls(); i++)
        {
            int size = funcdecls->GetDecl(i)->Sizeof();
            sizelocals += size;

            funcdecls->GetDecl(i)->SetOffset(m_offset);
            m_offset += size;
            Align();
            if (m_offset > m_highWater)
            {
                m_highWater = m_offset;
            }
        }
        sizeparams += sizelocals;
        while (sizeparams % 4 != 0)
        {
            ++sizeparams;
        }
        if (sizeparams > m_highWater)
        {
            m_highWater = sizeparams;
        }

        node->SetSize(m_highWater);
        node->SetOffset(startOff - 8);
        if (startOff - 8 < 0)
        {
            node->SetOffset(0);
        }

        m_offset = startOff;
        m_highWater = startH;
    }

    virtual void Visit(cParamListNode *node)
    {
        int paramSize = 0;
        for (int ii = 0; ii < node->NumParams(); ii++)
        {
            cExprNode *expr = node->GetParam(ii);

            if (expr != nullptr)
            {
                expr->Visit(this);
                int pSize = expr->GetType()->Sizeof();
                while (pSize % 4 != 0)
                {
                    pSize++;
                }
                paramSize += pSize;
            }
        }
        m_offset += paramSize;
        node->SetSize(paramSize);
        node->SetOffset(m_offset);
    }

    virtual void Visit(cParamsNode *node)
    {
        // Init the offset based on function call stack overhead
        m_offset = -12;

        // Need to loop through params because computation runs
        // opposite of other vars
        for (int ii = 0; ii < node->NumDecls(); ii++)
        {
            cDeclNode *param = node->GetDecl(ii);
            param->SetSize(param->GetType()->Sizeof());
            param->SetOffset(m_offset);

            m_offset -= param->Sizeof();
            m_offset = RoundDown(m_offset);
        }

        // Compute size based on call stack overhead
        node->SetSize(-12 - m_offset);

        // reset m_offset for funciton locals
        m_offset = 0;
    }

    int RoundDown(int value)
    {
        if (value % WORD_SIZE == 0)
            return value;
        return value - (WORD_SIZE + value % WORD_SIZE);
    }

    virtual void Visit(cStructDeclNode *node)
    {
        int startOff = m_offset;
        int startH = m_highWater;
        m_offset = 0;
        m_highWater = 0;
        VisitAllChildren(node);

        node->SetSize(m_highWater);
        node->SetOffset(0);
        m_offset = startOff;
        m_highWater = startH;
    }

    virtual void Visit(cVarDeclNode *node)
    {
        int itemsize = node->GetBaseType()->Sizeof();
        node->SetSize(itemsize);
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
    virtual void Visit(cVarExprNode *node)
    {
        int size = node->GetDecl()->Sizeof();
        int off = node->GetDecl()->GetOffset();
        node->SetSize(size);
        Align();
        node->SetOffset(off);
        //m_offset += off;
    }

    void Visit(cStmtsNode *node)
    {
        int startoff = m_offset;
        VisitAllChildren(node);
        m_offset = startoff;
    }
    virtual void VisitAllNodes(cAstNode *node)
    {
        VisitAllChildren(node);
    }

    // dont need?

    // void Visit(cSymbol *node) { VisitAllChildren(node); }
    // void Visit(cPrintNode *node) { VisitAllChildren(node); }
    // void Visit(cReturnNode *node) { VisitAllChildren(node); }
    // void Visit(cStmtNode *node) { VisitAllChildren(node); }

    // void Visit(cFuncExprNode *node) { VisitAllChildren(node); }
    // void Visit(cIfNode *node) { VisitAllChildren(node); }
    // void Visit(cIntExprNode *node) { VisitAllChildren(node); }
    // void Visit(cOpNode *node) { VisitAllChildren(node); }
    // void Visit(cExprNode *node) { VisitAllChildren(node); }
    // void Visit(cFloatExprNode *node) { VisitAllChildren(node); }
    // void Visit(cAstNode *node) { VisitAllChildren(node); }
    // void Visit(cAssignNode *node) { VisitAllChildren(node); }
    // void Visit(cBinaryExprNode *node) { VisitAllChildren(node); }

    // void Visit(cWhileNode *node) { VisitAllChildren(node); }
};