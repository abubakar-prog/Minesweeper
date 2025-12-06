#include "game_state.h"
#include "constants.h"

int currentScreen = SCREEN_MENU;
int grid[MAX_GRID_SIZE][MAX_GRID_SIZE];
bool revealed[MAX_GRID_SIZE][MAX_GRID_SIZE];
bool flagged[MAX_GRID_SIZE][MAX_GRID_SIZE];
bool explosion = false;
bool gameOver = false;
bool gameWon = false;
int currentGridSize = EASY_SIZE;
int currentMineCount = EASY_MINES;
int currentDifficulty = DIFFICULTY_EASY;
int playerScore = 0;
int cellsRevealed = 0;
int flagsPlaced = 0;
bool winSoundPlayed = false;
bool loseSoundPlayed = false;
int highScores[MAX_HIGH_SCORES];
char highScoreNames[MAX_HIGH_SCORES][MAX_NAME_LENGTH];
int highScoreCount = 0;

void resetGameState() {
    for (int i = 0; i < MAX_GRID_SIZE; i++) {
        for (int j = 0; j < MAX_GRID_SIZE; j++) {
            grid[i][j] = 0;
            revealed[i][j] = false;
            flagged[i][j] = false;
        }
    }
	explosion = false;
    gameOver = false;
    gameWon = false;
    cellsRevealed = 0;
    flagsPlaced = 0;
    playerScore = 0;
    winSoundPlayed = false;
    loseSoundPlayed = false;
}

void setDifficulty(int difficulty) {
    currentDifficulty = difficulty;
    if (difficulty == DIFFICULTY_EASY) {
        currentGridSize = EASY_SIZE;
        currentMineCount = EASY_MINES;
    }
    else if (difficulty == DIFFICULTY_MEDIUM) {
        currentGridSize = MEDIUM_SIZE;
        currentMineCount = MEDIUM_MINES;
    }
    else if (difficulty == DIFFICULTY_HARD) {
        currentGridSize = HARD_SIZE;
        currentMineCount = HARD_MINES;
    }
}
