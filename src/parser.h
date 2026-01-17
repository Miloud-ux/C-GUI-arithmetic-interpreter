#ifndef PARSER_H
#define PARSER_H
#include "tree.h"
#include <ctype.h>

typedef struct Parser {
        const char *input;
        int position;
} Parser;

void parserInit(Parser *p, const char *input);
char currentParsedChar(Parser *p);
char peekNextParsedChar(Parser *p);
void gotoNextParsedChar(Parser *p);
void skipWhitespace(Parser *p);
double getNumber(Parser *p);
ExprNode *parseFactor(Parser *p);
ExprNode *parseExpression(Parser *p);
ExprNode *parseTerm(Parser *p);
double evaluateExpression(ExprNode *node);
ExpressionTree *parseExpressionWrapper(const char *input);

#endif // !PARSER_H
