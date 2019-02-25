#pragma once
//**************************************
// cDeclNode
//
// Defines base class for all declarations.
// Future labs will add features to this class.
//
// Author: Phil Howard 
// phil.howard@oit.edu
//

#include "cAstNode.h"

class cDeclNode : public cAstNode
{
    public:
        cDeclNode() : cAstNode() {}
        void Insert(cAstNode* p){AddChild(p);}
        cDeclNode* GetType(){return dynamic_cast<cDeclNode*>(GetChild(0));}
};
