#ifndef TREE_STRUCTURE_H
#define TREE_STRUCTURE_H

typedef enum { NODE_NUMBER, NODE_OPERATOR } NodeType;

typedef struct ExprNode {
        NodeType type;
        union {
                double numValue;
                struct {
                        char operator;
                        struct ExprNode *left;
                        struct ExprNode *right;
                } op;
        } data;
} ExprNode;

typedef struct {
        ExprNode *node;
        int depth;
} ExpressionTree;

ExprNode *createNumberNode(double value);
ExprNode *createOperatorNode(char op, ExprNode *left, ExprNode *right);
void freeExpressionTree(ExprNode *node);
void printExpressionInfix(ExprNode *node, int parentPrecedence, char *buffer);
int calculateTreeDepth(ExprNode *node);
int getInfixPrecedence(char operator);

#endif // !TREE_STRUCTURE_H
