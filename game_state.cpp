#include <SFML/System.hpp>
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
int timerSeconds = 0;
bool timerStarted = false;
sf::Clock gameClock;
bool winSoundPlayed = false;
bool loseSoundPlayed = false;
bool firstClick = true;
bool enteringName = false;
char playerName[MAX_NAME_LENGTH] = "";
int nameLength = 0;
int highScores[MAX_HIGH_SCORES];
char highScoreNames[MAX_HIGH_SCORES][MAX_NAME_LENGTH];
int highScoreCount = 0;
int highScoreTimes[MAX_HIGH_SCORES];
float scaleX = 1.0f;
float scaleY = 1.0f;
float offsetX = 0.0f;
float offsetY = 0.0f;
void resetGameState() {
	for (int i = 0; i < MAX_GRID_SIZE; i++) {
		for (int j = 0; j < MAX_GRID_SIZE; j++) {
			grid[i][j] = 0;
			revealed[i][j] = false;
			flagged[i][j] = false;
		}
	}
	enteringName = false;
	nameLength = 0;
	for (int i = 0; i < MAX_NAME_LENGTH; i++) {
		playerName[i] = '\0';
	}
	explosion = false;
	gameOver = false;
	gameWon = false;
	cellsRevealed = 0;
	flagsPlaced = 0;
	playerScore = 0;
	winSoundPlayed = false;
	loseSoundPlayed = false;
	firstClick=true;
	timerSeconds = 0;
	timerStarted = false;
	gameClock.restart();
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
