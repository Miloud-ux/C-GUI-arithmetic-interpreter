// #include "ui.h"
// #include "parser.h"
// #include "tree.h"
// #include <raylib.h>
// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
//
// void updateAndDrawMenu(AppState *state) {
//     Vector2 mousePos = GetMousePosition();
//     Rectangle startButton = {300, 200, 200, 50};
//
//     if (CheckCollisionPointRec(mousePos, startButton) &&
//         IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
//         *state = STATE_INPUT;
//     }
//     DrawText("MAIN MENU", 320, 100, 30, DARKGRAY);
//     bool hover = CheckCollisionPointRec(mousePos, startButton);
//     DrawRectangleRec(startButton, hover ? SKYBLUE : GRAY);
//     DrawText("START", startButton.x + 50, startButton.y + 15, 20, WHITE);
// }
//
// void updateAndDrawInput(AppState *state, char *input, int *lettercount) {
//     Vector2 mousePos = GetMousePosition();
//     Rectangle doneButton = {300, 350, 200, 50};
//     Rectangle inputBar = {200, 250, 500, 50};
//
//     int keyPressed = GetCharPressed();
//     while (keyPressed > 0) {
//         if ((keyPressed >= 32 && keyPressed <= 125) && (*lettercount) < 254)
//         {
//             input[(*lettercount)++] = (char)keyPressed;
//             input[*lettercount] = '\0';
//         }
//         keyPressed = GetCharPressed();
//     }
//
//     if (IsKeyPressed(KEY_BACKSPACE) && *lettercount > 0) {
//         input[--(*lettercount)] = '\0';
//     }
//
//     if (CheckCollisionPointRec(mousePos, doneButton) &&
//         IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
//         *state = STATE_RESULT;
//     }
//
//     DrawText("ENTER YOUR EXPRESSION", 320, 100, 30, DARKGRAY);
//     DrawRectangleRec(inputBar, LIGHTGRAY);
//     DrawText(input, inputBar.x + 10, inputBar.y + 15, 20, BLACK);
//     bool hover = CheckCollisionPointRec(mousePos, doneButton);
//     DrawRectangleRec(doneButton, hover ? LIME : GRAY);
//     DrawText("SHOW RESULT", doneButton.x + 75, doneButton.y + 15, 20, WHITE);
// }
//
// void updateAndDrawResult(AppState *state, char *infix, double
// calculatedResult,
//                          int treeDepth) {
//     DrawText("INFIX EXPRESSION: ", 100, 200, 20, GRAY);
//     DrawText(infix, 100, 230, 20, BLACK);
//
//     DrawText("FINAL RESULT: ", 100, 300, 20, GRAY);
//     DrawText(TextFormat("%.2f", calculatedResult), 100, 330, 30, MAROON);
//
//     DrawText("TREE DEPTH: ", 100, 400, 20, GRAY);
//     DrawText(TextFormat("%.2d", treeDepth), 100, 430, 40, MAROON);
//
//     DrawText("Click anywhere to go back", 250, 500, 20, DARKGRAY);
//
//     if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
//         *state = STATE_MENU;
//     }
// }

#include "ui.h"
#include "parser.h"
#include "tree.h"
#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Helper to center text easily
void DrawTextCentered(const char *text, int y, int fontSize, Color color) {
    int textWidth = MeasureText(text, fontSize);
    DrawText(text, GetScreenWidth() / 2 - textWidth / 2, y, fontSize, color);
}

void updateAndDrawMenu(AppState *state) {
    int screenWidth = GetScreenWidth();
    Vector2 mousePos = GetMousePosition();

    float btnWidth = 200;
    float btnHeight = 50;
    Rectangle startButton = {screenWidth / 2 - btnWidth / 2, 250, btnWidth,
                             btnHeight};

    if (CheckCollisionPointRec(mousePos, startButton) &&
        IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        *state = STATE_INPUT;
    }

    DrawTextCentered("MAIN MENU", 150, 40, DARKGRAY);

    bool hover = CheckCollisionPointRec(mousePos, startButton);
    DrawRectangleRec(startButton, hover ? SKYBLUE : GRAY);

    int textW = MeasureText("START", 20);
    DrawText("START", startButton.x + (btnWidth / 2 - textW / 2),
             startButton.y + 15, 20, WHITE);
}

void updateAndDrawInput(AppState *state, char *input, int *lettercount) {
    int screenWidth = GetScreenWidth();
    Vector2 mousePos = GetMousePosition();

    Rectangle inputBar = {screenWidth / 2 - 250, 250, 500, 50};
    Rectangle doneButton = {screenWidth / 2 - 100, 350, 200, 50};

    // Input Logic
    int keyPressed = GetCharPressed();
    while (keyPressed > 0) {
        if ((keyPressed >= 32 && keyPressed <= 125) && (*lettercount) < 254) {
            input[(*lettercount)++] = (char)keyPressed;
            input[*lettercount] = '\0';
        }
        keyPressed = GetCharPressed();
    }
    if (IsKeyPressed(KEY_BACKSPACE) && *lettercount > 0) {
        input[--(*lettercount)] = '\0';
    }

    if (CheckCollisionPointRec(mousePos, doneButton) &&
        IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        *state = STATE_RESULT;
    }

    DrawTextCentered("ENTER YOUR EXPRESSION", 150, 30, DARKGRAY);

    // Draw Input Bar & Current Text
    DrawRectangleRec(inputBar, LIGHTGRAY);
    int inputTextW = MeasureText(input, 20);
    DrawText(input, inputBar.x + (inputBar.width / 2 - inputTextW / 2),
             inputBar.y + 15, 20, BLACK);

    // Draw Button
    bool hover = CheckCollisionPointRec(mousePos, doneButton);
    DrawRectangleRec(doneButton, hover ? LIME : GRAY);
    int btnTextW = MeasureText("SHOW RESULT", 20);
    DrawText("SHOW RESULT",
             doneButton.x + (doneButton.width / 2 - btnTextW / 2),
             doneButton.y + 15, 20, WHITE);
}

void updateAndDrawResult(AppState *state, char *infix, double calculatedResult,
                         int treeDepth) {
    DrawTextCentered("INFIX EXPRESSION:", 150, 20, GRAY);
    DrawTextCentered(infix, 185, 25, BLACK);

    DrawTextCentered("FINAL RESULT:", 260, 20, GRAY);
    DrawTextCentered(TextFormat("%.2f", calculatedResult), 300, 40, MAROON);

    DrawTextCentered("TREE DEPTH:", 380, 20, GRAY);
    DrawTextCentered(TextFormat("%d", treeDepth), 415, 30, DARKBLUE);

    DrawTextCentered("Click anywhere to go back", 520, 18, LIGHTGRAY);

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        *state = STATE_MENU;
    }
}
