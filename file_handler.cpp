#include "file_handler.h"
#include "game_state.h"
#include "constants.h"
#include <fstream>

using namespace std;
using namespace sf;

void saveGame() {
    std::ofstream file("savegame.txt");
    if (!file.is_open()) return;
    file << currentGridSize << endl;
    file << currentMineCount << endl;
    file << currentDifficulty << endl;
    file << cellsRevealed << endl;
    file << flagsPlaced << endl;
    file << playerScore << endl;
    file << gameOver << endl;
    file << gameWon << endl;
    for (int i = 0; i < MAX_GRID_SIZE; i++) {
        for (int j = 0; j < MAX_GRID_SIZE; j++) {
            file << grid[i][j] << " ";
        }
        file << endl;
    }
    for (int i = 0; i < MAX_GRID_SIZE; i++) {
        for (int j = 0; j < MAX_GRID_SIZE; j++) {
            file << revealed[i][j] << " ";
        }
        file << endl;
    }
    for (int i = 0; i < MAX_GRID_SIZE; i++) {
        for (int j = 0; j < MAX_GRID_SIZE; j++) {
            file << flagged[i][j] << " ";
        }
        file << endl;
    }
    file.close();
}

void loadGame() {
    std::ifstream file("savegame.txt");
    if (!file.is_open()) return;
    file >> currentGridSize;
    file >> currentMineCount;
    file >> currentDifficulty;
    file >> cellsRevealed;
    file >> flagsPlaced;
    file >> playerScore;
    file >> gameOver;
    file >> gameWon;
    for (int i = 0; i < MAX_GRID_SIZE; i++) {
        for (int j = 0; j < MAX_GRID_SIZE; j++) {
            file >> grid[i][j];
        }
    }
    for (int i = 0; i < MAX_GRID_SIZE; i++) {
        for (int j = 0; j < MAX_GRID_SIZE; j++) {
            file >> revealed[i][j];
        }
    }
    for (int i = 0; i < MAX_GRID_SIZE; i++) {
        for (int j = 0; j < MAX_GRID_SIZE; j++) {
            file >> flagged[i][j];
        }
    }
    file.close();
}

void saveHighScores() 
{
    std::ofstream file("highscores.txt");
    if (!file.is_open()) return;
    file << highScoreCount << "\n";
    for (int i = 0; i < highScoreCount; i++) {
        file << highScores[i] << "\n";
        file << highScoreNames[i] << "\n";
        file << highScoreTimes[i] << "\n";
    }
}

void loadHighScores() {
    std::ifstream file("highscores.txt");
    if (!file.is_open()) {
        highScoreCount = 0;
        return;
    }
    file >> highScoreCount;
    file.ignore();

    for (int i = 0; i < highScoreCount; i++) {
        file >> highScores[i];
        file.ignore();
        file.getline(highScoreNames[i], MAX_NAME_LENGTH);

        if (file >> highScoreTimes[i]) {
            file.ignore();
        }
        else {
            highScoreTimes[i] = 0;
            file.clear();
        }
    }
    file.close();
}

void addHighScore(int score, char name[], int time) 
{
    int position = -1;
    for (int i = 0; i < highScoreCount; i++) {
        if (score > highScores[i]) {
            position = i;
            break;
        }
    }
    if (position == -1 && highScoreCount >= MAX_HIGH_SCORES) {
        return;
    }
    if (position == -1) {
        position = highScoreCount;
        highScores[position] = score;
        highScoreTimes[position] = time;
        int j = 0;
        while (j < MAX_NAME_LENGTH - 1 && name[j] != '\0') {
            highScoreNames[position][j] = name[j];
            j++;
        }
        highScoreNames[position][j] = '\0';
        highScoreCount++;
        saveHighScores();
        return;
    }
    for (int i = MAX_HIGH_SCORES - 1; i > position; i--) {
        if (i - 1 < highScoreCount) {
            highScores[i] = highScores[i - 1];
            highScoreTimes[i] = highScoreTimes[i - 1];
            for (int j = 0; j < MAX_NAME_LENGTH; j++) {
                highScoreNames[i][j] = highScoreNames[i - 1][j];
            }
        }
    }
    highScores[position] = score;
    highScoreTimes[position] = time;
    int j = 0;
    while (j < MAX_NAME_LENGTH - 1 && name[j] != '\0') {
        highScoreNames[position][j] = name[j];
        j++;
    }
    highScoreNames[position][j] = '\0';
    if (highScoreCount < MAX_HIGH_SCORES) {
        highScoreCount++;
    }
    saveHighScores();
}

void saveSettings() {
    std::ofstream file("settings.txt");
    if (!file.is_open()) return;
    file << currentDifficulty << endl;
    file << currentGridSize << endl;
    file << currentMineCount << endl;
    file.close();
}

void loadSettings() {
    std::ifstream file("settings.txt");
    if (!file.is_open()) {
        setDifficulty(DIFFICULTY_EASY);
        return;
    }
    file >> currentDifficulty;
    file >> currentGridSize;
    file >> currentMineCount;
    file.close();
}
