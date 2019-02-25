#pragma once
#include "astnodes.h"
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
      cDeclNode* GetType()
      {
            cExprNode* left = dynamic_cast<cExprNode*>(GetChild(0));
            cExprNode* right = dynamic_cast<cExprNode*>(GetChild(2));
            cBaseTypeNode* leftType = dynamic_cast<cBaseTypeNode*>(left->GetType());
            cBaseTypeNode* rightType = dynamic_cast<cBaseTypeNode*>(right->GetType());

            if (leftType->isFloat()) 
            {
                  return leftType;  // if left is a float type is float
            }
            if (rightType->isFloat()) 
            {
                  return rightType; // if right is float the nthe type is float
            }
            if (rightType->isInt()) {
                  return rightType; //if both arent char and none are float and one is int then type is int
            }
            if (leftType->isInt()) {
                  return leftType;  // same as last
            }
            return rightType;
            
            
            
            
            return nullptr; // shouldnt happen 
      }
   virtual string NodeType() {return string("expr"); }
   virtual void Visit(cVisitor *visitor) {visitor->Visit(this); }
};
