#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H

void initializeGame();
void revealCell(int x, int y);
void toggleFlag(int x, int y);
void checkWin();
void calculateScore();
void revealAllMines();
void moveMineFromCell(int x, int y);
#endif
