#ifndef FILE_HANDLER_H
#define FILE_HANDLER_H

void saveGame();
void loadGame();
void saveHighScores();
void loadHighScores();
void addHighScore(int score, char name[], int time);
void saveSettings();
void loadSettings();

#endif
