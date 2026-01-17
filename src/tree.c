#include "tree.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

ExprNode *createNumberNode(double value) {
    ExprNode *numNode = malloc(sizeof(ExprNode));
    if (!numNode) {
        fprintf(stderr, "Error allocating memory\n");
        return NULL;
    }
    numNode->type = NODE_NUMBER;
    numNode->data.numValue = value;
    return numNode;
}

ExprNode *createOperatorNode(char op, ExprNode *left, ExprNode *right) {
    ExprNode *operatorNode = malloc(sizeof(ExprNode));
    if (!operatorNode) {
        fprintf(stderr, "Error allocating memory\n");
        return NULL;
    }

    operatorNode->type = NODE_OPERATOR;
    operatorNode->data.op.operator = op; // Add a check for valid operators
    operatorNode->data.op.left = left;
    operatorNode->data.op.right = right;

    return operatorNode;
}

void freeExpressionTree(ExprNode *node) {
    if (!node) {
        return;
    }
    if (node->type == NODE_OPERATOR) {
        freeExpressionTree(node->data.op.left);
        freeExpressionTree(node->data.op.right);
    }
    free(node);
}

int getInfixPrecedence(char operator) {
    switch (operator) {
    case '+':
    case '-':
        return 1;
    case '*':
    case '/':
        return 2;
    default:
        return 0;
    }
}
void printExpressionInfix(ExprNode *node, int parentPrecedence, char *buffer) {
    if (!node) {
        return;
    }
    if (node->type == NODE_NUMBER) {
        char temp[32];
        snprintf(temp, sizeof(temp), "%.2f", node->data.numValue);
        strcat(buffer, temp);
        return;
    }
    int needParentheses = (parentPrecedence != 0);
    if (needParentheses) {
        strcat(buffer, "(");
    }
    int nodePrecedence = getInfixPrecedence(node->data.op.operator);

    printExpressionInfix(node->data.op.left, nodePrecedence, buffer);
    char operatorStr[4];
    snprintf(operatorStr, sizeof(operatorStr), " %c ", node->data.op.operator);
    strcat(buffer, operatorStr);

    int rightprecedence = nodePrecedence;
    if (node->data.op.operator == '-' || node->data.op.operator == '/') {
        // Pass higher precedence (nodePrecedence + 1)
        rightprecedence++;
    }
    printExpressionInfix(node->data.op.right, rightprecedence, buffer);

    if (needParentheses) {
        strcat(buffer, ")");
    }
}

int calculateTreeDepth(ExprNode *node) {
    if (node == NULL) {
        return 0;
    }

    if (node->type == NODE_NUMBER) {
        return 1;
    }

    int leftDepth = calculateTreeDepth(node->data.op.left);
    int rightDepth = calculateTreeDepth(node->data.op.right);

    return 1 + (leftDepth > rightDepth ? leftDepth : rightDepth);
}
