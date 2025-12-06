#ifndef GAME_STATE_H
#define GAME_STATE_H

#include "constants.h"

extern int currentScreen;
extern int grid[MAX_GRID_SIZE][MAX_GRID_SIZE];
extern bool revealed[MAX_GRID_SIZE][MAX_GRID_SIZE];
extern bool flagged[MAX_GRID_SIZE][MAX_GRID_SIZE];
extern bool gameOver;
extern bool gameWon;
extern int currentGridSize;
extern int currentMineCount;
extern int currentDifficulty;
extern int playerScore;
extern int cellsRevealed;
extern int flagsPlaced;
extern bool winSoundPlayed;
extern bool loseSoundPlayed;
extern int highScores[MAX_HIGH_SCORES];
extern char highScoreNames[MAX_HIGH_SCORES][MAX_NAME_LENGTH];
extern int highScoreCount;
extern bool explosion;
void resetGameState();
void setDifficulty(int difficulty);

#endif
