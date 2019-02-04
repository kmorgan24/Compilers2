#pragma once
#include "cAstNode.h"
#include "cExprNode.h"

class cMathExprNode : public cExprNode
{
public:
   cMathExprNode(cExprNode* left, cOpNode* operation, cExprNode* right) : cExprNode()
   {
         AddChild(left);
         AddChild(operation);
         AddChild(right);
   }

   virtual string NodeType() {return string("expr"); }
   virtual void Visit(cVisitor *visitor) {visitor->Visit(this); }
};
