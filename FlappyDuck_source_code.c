
//Flappy Duck Source Code//

#define _WIN32_WINNT 0x0A00 //Enable modern Windows features

#include <windows.h>   // Windows API functions (Sleep, GetAsyncKeyState, console settings, etc.)
#include <wincon.h>    // Extra Windows console control features (cursor info, console modes)
#include <stdio.h>     // Standard input/output functions (printf, sprintf, fopen, etc.)
#include <stdlib.h>    // General utilities (rand, srand, system, memory functions)
#include <time.h>      // Time functions (time for srand seed)
#include <string.h>    // String manipulation (strcpy, strcat, sprintf helper)

// Enable ANSI terminal escape codes in Windows console
#ifndef ENABLE_VIRTUAL_TERMINAL_PROCESSING
#define ENABLE_VIRTUAL_TERMINAL_PROCESSING 0x0004
#endif

// Game field dimensions
#define xSize       32
#define ySize       16
#define pipeCount   3
#define qKey        0x51  // 'Q' key ASCII code

// ANSI color definitions
#define GREEN       "\x1b[32m"
#define YELLOW      "\x1b[33m"
#define CYAN        "\x1b[36m"
#define MAGENTA     "\x1b[35m"
#define BLUE_BG     "\x1b[44m"
#define NC          "\x1b[0m" // Reset color

// Structure for bird/pipes (position + scored flag)
typedef struct {
    int x;
    int y;
    int scored;
} PIX;

PIX bird;                // Player "duck"
PIX pipes[pipeCount];   // Array of pipe objects

//Initialize score variables
int score = 0;
int highScore = 0;

// Function declarations
void EnableANSI();
void HideCursor(int visible);
void Draw();
void Pipes();
void HitTest();
void UpdateScore();
void LoadHighScore();
void SaveHighScore();
void ShowStartScreen();
void ResetGame();
void GameOver();


// Enable ANSI escape codes for color + cursor control
void EnableANSI() {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE); // Get console handle
    DWORD dwMode = 0;
    if (GetConsoleMode(hOut, &dwMode)) {         // Read current console mode
        dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING; // Enable VT processing
        SetConsoleMode(hOut, dwMode);            // Apply modified settings
    } 
}

// Show or hide text cursor in console
void HideCursor(int visible) {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cci;
    GetConsoleCursorInfo(hOut, &cci);
    cci.bVisible = visible;
    SetConsoleCursorInfo(hOut, &cci);
}


//Draw entire game frame into buffer, then print at once 
void Draw() {
    char buff[7000];         // Big buffer for full screen text
    strcpy(buff, "\x1b[H"); // Move cursor to top (no flicker clear)

    //Add score information
    char scoreInfo[100];
    sprintf(scoreInfo, CYAN "Score: %d   High Score: %d\n" NC, score, highScore);
    strcat(buff, scoreInfo);

    // Loop through every row/column of game area
    for (int y = 0; y <= ySize; y++) {
        for (int x = 0; x <= xSize; x++) {
            // Draw walls/borders
            if (y == 0 || y == ySize || x == 0 || x == xSize) {
                strcat(buff, NC "[]");
                continue;
            }

            int printed = 0;

            // Draw pipes if at correct location
            for (int i = 0; i < pipeCount; i++) {
                if ((pipes[i].x >= x-1 && pipes[i].x <= x+1 &&
                     (pipes[i].y == y+3 || pipes[i].y == y-3)) ||
                    (pipes[i].x == x && (pipes[i].y <= y-4 || pipes[i].y >= y+4))) {
                    strcat(buff, GREEN "[]" NC);
                    printed = 1;
                    break;
                }
            }

            // Draw bird or blue background if not a pipe
            if (!printed) {
                if (bird.y == y && bird.x == x)
                    strcat(buff, BLUE_BG YELLOW ")>" NC);  // Bird head
                else if (bird.y == y && bird.x == x + 1)
                    strcat(buff, BLUE_BG YELLOW "_(" NC);  // Bird body
                else if (bird.y == y && bird.x == x + 2)
                    strcat(buff, BLUE_BG YELLOW " _" NC);  // Bird tail
                else
                    strcat(buff, BLUE_BG "  " NC);  // Blue background for empty air
            }
        }
        strcat(buff, "\n");  // New ROW
    }

    printf("%s", buff);    // Print entire frame
}


//To keep regenerating pipes
void Pipes() {
    for (int i = 0; i < pipeCount; i++) {

        //Pipe reached left edge => reposition to right
        if (pipes[i].x == -1) {
            // Determine next pipe spawn position
            (i == 0) ? (pipes[i].x = pipes[2].x + 15) : (pipes[i].x = pipes[i-1].x + 15);
            // Random height of the gap
            pipes[i].y = (rand() % 7) + 5;
            pipes[i].scored = 0;  // Reset score flag
        }
    }
}

// Update score when passing pipes
void UpdateScore() {
    for (int i = 0; i < pipeCount; i++) {
        if (pipes[i].x + 2 < bird.x && pipes[i].scored == 0) {
            pipes[i].scored = 1;
            score++;
            // Update high score
            if (score > highScore)
                highScore = score;
        }
    }
}

// Load saved high score from file
void LoadHighScore() {
    FILE *f = fopen("highscore.txt", "r");
    if (f) { fscanf(f, "%d", &highScore); fclose(f); }
}

// Save high score to file
void SaveHighScore() {
    FILE *f = fopen("highscore.txt", "w");
    if (f) { fprintf(f, "%d", highScore); fclose(f); }
}

// Initialize bird + pipes for a new game
void ResetGame() {
    score = 0;
    bird.x = 10;
    bird.y = 10;

    // Position pipes spaced at intervals
    for (int i = 0; i < pipeCount; i++) {
        pipes[i].x = 25 + 15 * i;
        pipes[i].y = (rand() % 7) + 5;
        pipes[i].scored = 0;
    }
    
     // Clear Screen 
    for (int i = 0; i <= ySize; i++) printf("\n");
    Draw();
    system("pause>nul");
}

// Starting screen before game begins
void ShowStartScreen() {
    system("cls");    // Clear console
    Beep(1000, 5);
    printf(MAGENTA
        "============================================================\n" NC);
    Sleep(750);
    printf(MAGENTA  "                    WELCOME TO FLAPPY DUCK!\n" NC);
    Sleep(800);
    printf(MAGENTA "============================================================\n" NC);
    Beep(1000, 5);
    Sleep(850);
       
    printf(CYAN "   Controls:\n" NC);
    Beep(1000, 5);
     Sleep(850); 
    
    printf("   - UP arrow or W key to flap\n");
    Beep(1000, 5);
     Sleep(850);
     
    printf("   - Avoid pipes\n");
    Beep(1000, 5);
     Sleep(850);
     
    printf("   - Q to quit anytime\n");
    Beep(1000, 5);
     Sleep(850);
     
    printf(YELLOW "\n   Press any key to start playing!!!\n\n" NC);
     Sleep(850);

    printf("\n============================================================\n");
    system("pause>nul");  //Wait for input
    system("cls");   // Clear console 
}


// Game over screen + replay menu
void GameOver() {
    system("cls");
    printf(YELLOW "\n\n   !!!" NC);
    Sleep(100);
    printf(YELLOW "G" NC);
    Sleep(100); 
    printf(YELLOW "A" NC);
    Sleep(100); 
    printf(YELLOW "M" NC);
    Sleep(100); 
    printf(YELLOW "E " NC);
    Sleep(100); 
    printf(YELLOW " " NC);
    Sleep(100); 
    printf(YELLOW "O" NC); 
    Sleep(100);  
    printf(YELLOW "V" NC);
    Sleep(100); 
    printf(YELLOW "E" NC);
    Sleep(100); 
    printf(YELLOW "R" NC);
    Sleep(100);
    printf(YELLOW "!!!\n" NC);
    Sleep(200);

    printf(CYAN "   Final Score: " NC );
    Sleep(200);
    printf(CYAN "%d\n" NC , score);
    Sleep(200);
    printf(CYAN "   High Score:" NC );
    Sleep(200);
    printf(CYAN " %d\n" NC , highScore);
    Sleep(200);
           
    
    if (score == highScore) {
        
        highScore = score;
        SaveHighScore();
        printf(GREEN "\n  NEW HIGH SCORE ACHIEVED!\n" NC);
    } 
    else {
        SaveHighScore();
    }
    
    // Wait for Y or N input
    printf("\n   Play again? (Y/N)\n");
    while (1) {
        if (GetAsyncKeyState('Y') & 0x8000) {
            system("cls");
            ResetGame();
            return;
        } else if (GetAsyncKeyState('N') & 0x8000) {
            HideCursor(1); // show cursor before exit
            exit(0);
        }
        Sleep(100);   // Avoid CPU overload
    }
}


// Detect collisions with pipes and borders
void HitTest() {
     // Hit ceiling or floor
    if (bird.y >= ySize || bird.y <= 0)
        GameOver();
    // Hit a pipe
    for (int i = 0; i < pipeCount; i++) {
        if ((bird.x - 2 < pipes[i].x + 2) && (bird.x > pipes[i].x - 2) &&
            ((bird.y < pipes[i].y - 2) || (bird.y > pipes[i].y + 2))) {
            GameOver();
        }
    }
}

int main() {
    srand(time(NULL));                                  // Random seed for pipe gaps
    system("title Flappy Duck - Blue Sky Edition");     // Set console title


    EnableANSI();                                       // Enable ANSI escape codes
    HideCursor(0);                                      // Hide blinking cursor
    LoadHighScore();                                    // Load score from file
    ShowStartScreen();                                  // Show intro screen
    ResetGame();                                        // Start new game by resetting variables and screen

    int frame = 0;

    while (1) {
        //Bird flap (UP arrow or W key)
        if (GetAsyncKeyState(VK_UP)|| (GetAsyncKeyState('W') & 0x8000))
            bird.y -= 2;
        // Quit with Q key
        if (GetAsyncKeyState(qKey)) {
            SaveHighScore();
            HideCursor(1); // Show cursor before quitting
            break;
        }
        // Gravity + pipe movement every few frames 
        if (frame == 2) {
            bird.y++;                                 // Gravity pulls down
            for (int i = 0; i < pipeCount; i++)      
                pipes[i].x--;                         // Move pipes left
            frame = 0;
        }

        HitTest();                                    // Check collisions
        UpdateScore();                                // Update score if passed pipes
        Draw();                                       // Draw screen
        Pipes();                                      // Handle pipe respawn (updating pipe positions)

        frame++;                                     // Count frames 
        Sleep(100);                                  // Control game speed
    }

    return 0;
}