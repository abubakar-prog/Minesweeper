#ifndef GAME_STATE_H
#define GAME_STATE_H
#include <SFML/System.hpp>
#include "constants.h"

extern bool isFirstClick;
extern bool enteringName;
extern char playerName[MAX_NAME_LENGTH];
extern int nameLength;
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
extern int timerSeconds;
extern bool timerStarted;
extern sf::Clock gameClock;
extern bool firstClick;
extern int flagsPlaced;
extern bool winSoundPlayed;
extern bool loseSoundPlayed;
extern float scaleX;
extern float scaleY;
extern float offsetX;
extern float offsetY;
extern int highScores[MAX_HIGH_SCORES];
extern char highScoreNames[MAX_HIGH_SCORES][MAX_NAME_LENGTH];
extern int highScoreTimes[MAX_HIGH_SCORES];
extern int highScoreCount;
extern bool explosion;
void resetGameState();
void setDifficulty(int difficulty);

#endif
