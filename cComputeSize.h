#pragma once

#include "cVisitor.h"
#include "astnodes.h"
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
            sizelocals += funcdecls->GetDecl(i)->Sizeof();
            int resize = m_offset;
            Align();
            resize = m_offset - resize;
            sizelocals += resize;
            funcdecls->GetDecl(i)->SetOffset(m_offset);
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
        VisitAllChildren(node);
        Align();

        node->SetSize(m_offset);
    }

    virtual void Visit(cStructDeclNode *node)
    {
        int startOff = m_offset;
        int startH = m_highWater;
        m_offset = 0;
        m_highWater = 0;
        VisitAllChildren(node);
        // while (m_offset % 4 != 0)
        // {
        //     ++m_offset;
        // }

        node->SetSize(m_highWater);
        node->SetOffset(startOff - 8);
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