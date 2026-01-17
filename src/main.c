#include "parser.h"
#include "tree.h"
#include "ui.h"
#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    InitWindow(800, 600, "Arithmetic Expression Parser");
    SetTargetFPS(60);

    AppState currentState = STATE_MENU;
    char inputBuffer[256] = {0};
    int letterCount = 0;
    char infixResult[256] = {0};
    double mathResult = 0;
    int treeDepth = 0;

    while (!WindowShouldClose()) {
        if (currentState == STATE_RESULT && infixResult[0] == '\0') {
            ExpressionTree *tree = parseExpressionWrapper(inputBuffer);
            printExpressionInfix(tree->node, 0, infixResult);
            mathResult = evaluateExpression(tree->node);
            treeDepth = tree->depth;
            freeExpressionTree(tree->node);
            free(tree);
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        switch (currentState) {
        case STATE_MENU:
            infixResult[0] = '\0';
            updateAndDrawMenu(&currentState);
            break;
        case STATE_INPUT:
            updateAndDrawInput(&currentState, inputBuffer, &letterCount);
            break;
        case STATE_RESULT:
            updateAndDrawResult(&currentState, infixResult, mathResult,
                                treeDepth);
            if (currentState == STATE_MENU) {
                inputBuffer[0] = '\0';
                letterCount = 0;
            }
            break;
        default:
            fprintf(stderr, "Error : Invalid state");
            exit(1);
        }
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
