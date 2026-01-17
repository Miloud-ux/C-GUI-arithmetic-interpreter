# C-GUI-arithmetic-interpreter
**Program to parse arithmetic expressions using recursive descent algorithm.**

- - - 
## Files
**main.c** : contains the main loop for the raylib program using state machine (3 states) for the starting menu, input and for showing results.
**parser.c** : contains the parsing functions and implementation of recursive descent
**tree.c** : contains tree creattion functions, printing infix function and calculate depth function
**ui.c** : contains the function used for raylib interface (draw_start_menu, draw_input, draw_result)
- - - 
**How to compile?** 
`gcc -o interpreter main.c parser.c ui.c tree.c -lraylib` (no make file)
- - - 
## Images : 
### Start menu: 
<img width="800" height="605" alt="image" src="https://github.com/user-attachments/assets/44792cf6-bcff-4779-a9c8-157aa3e4ebd3" />

### Input menu: 
<img width="798" height="599" alt="image" src="https://github.com/user-attachments/assets/2595c2ee-1cd7-4071-958c-3662f21f0347" />

### Result menu: 
<img width="807" height="601" alt="image" src="https://github.com/user-attachments/assets/59653456-43af-47a2-897b-4954b244fad7" />

