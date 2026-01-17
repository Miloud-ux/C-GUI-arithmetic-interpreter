#include "parser.h"
#include "tree.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_DIGITS 9

void parserInit(Parser *p, const char *input) {
    p->input = input;
    p->position = 0;
}

char currentParsedChar(Parser *p) { return p->input[p->position]; }
char peekNextParsedChar(Parser *p) {
    if (p->input[p->position] != '\0') {
        return p->input[p->position++];
    }
    printf("End of input\n");
    return '\0';
}
void gotoNextParsedChar(Parser *p) {
    if (p->input[p->position] != '\0') {
        p->position++;
    }
}

void skipWhitespace(Parser *p) {
    while (currentParsedChar(p) == ' ' || currentParsedChar(p) == '\n' ||
           currentParsedChar(p) == '\r' || currentParsedChar(p) == '\t') {
        gotoNextParsedChar(p);
    }
}

double getNumber(Parser *p) {
    char *endPtr;
    // strtod is smart: it reads the number and tells you where it stopped
    double value = strtod(&p->input[p->position], &endPtr);

    // Move the parser position to where strtod finished
    p->position = (int)(endPtr - p->input);

    return value;
}

ExprNode *parseFactor(Parser *p) {
    skipWhitespace(p);

    if (currentParsedChar(p) == '(') {
        gotoNextParsedChar(p);
        ExprNode *node = parseExpression(p);
        skipWhitespace(p);
        if (currentParsedChar(p) == ')') {
            gotoNextParsedChar(p);
        } else {
            fprintf(stderr, "\nError : Expected ')' here\n : %.*s", p->position,
                    "^");
        }
        return node;
    }

    if (isdigit(currentParsedChar(p)) || currentParsedChar(p) == '.') {
        double value = getNumber(p);
        return createNumberNode(value);
    }

    fprintf(stderr, "\nError : Expected number or '(' here\n %.*s", p->position,
            "^");
    exit(1);
}

ExprNode *parseTerm(Parser *p) {
    ExprNode *left = parseFactor(p);
    skipWhitespace(p);

    while (currentParsedChar(p) == '*' || currentParsedChar(p) == '/') {
        char operator = currentParsedChar(p);
        gotoNextParsedChar(p);
        skipWhitespace(p);

        ExprNode *right = parseFactor(p);
        left = createOperatorNode(operator, left, right);
        skipWhitespace(p);
    }
    return left;
}

ExprNode *parseExpression(Parser *p) {
    ExprNode *left = parseTerm(p);
    skipWhitespace(p);

    while (currentParsedChar(p) == '+' || currentParsedChar(p) == '-') {
        char operator = currentParsedChar(p);
        gotoNextParsedChar(p);
        skipWhitespace(p);

        ExprNode *right = parseTerm(p);
        left = createOperatorNode(operator, left, right);
        skipWhitespace(p);
    }
    return left;
}

double evaluateExpression(ExprNode *node) {
    if (node == NULL) {
        fprintf(stderr, "Error : Trying to evaluate a NULL node");
        exit(1);
    }

    // basecase
    if (node->type == NODE_NUMBER) {
        return node->data.numValue;
    }

    double left = evaluateExpression(node->data.op.left);
    double right = evaluateExpression(node->data.op.right);

    switch (node->data.op.operator) {
    case '+':
        return left + right;
    case '-':
        return left - right;
    case '*':
        return left * right;
    case '/':
        if (right == 0.0) {
            fprintf(stderr, "Math Error : Devision by zero");
            exit(1);
        }
        return left / right;
    default:
        fprintf(stderr, "Syntax Error : Unknown operator %c",
                node->data.op.operator);
        exit(1);
    }
}

ExpressionTree *parseExpressionWrapper(const char *input) {
    Parser p;
    parserInit(&p, input);

    ExprNode *root = parseExpression(&p);

    // Check for unparsed chars
    skipWhitespace(&p);
    if (currentParsedChar(&p) != '\0') {
        fprintf(stderr, "Error : Unexpected characters after expression");
        freeExpressionTree(root);
        exit(1);
    }

    int depth = calculateTreeDepth(root);

    ExpressionTree *tree = (ExpressionTree *)malloc(sizeof(ExpressionTree));
    tree->node = root;
    tree->depth = depth;
    return tree;
}
