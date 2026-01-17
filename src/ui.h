#ifndef UI_H
#define UI_H
typedef enum { STATE_MENU, STATE_INPUT, STATE_RESULT } AppState;
#include "raylib.h"
void updateAndDrawMenu(AppState *state);
void updateAndDrawInput(AppState *state, char *input, int *lettercount);
void updateAndDrawResult(AppState *state, char *infix, double calculatedResult,
                         int treeDepth);

#endif // !UI_H
