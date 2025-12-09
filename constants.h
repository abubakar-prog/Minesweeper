#ifndef CONSTANTS_H
#define CONSTANTS_H

const char MINE_IMAGE_PATH[] = "assets/minesweeper_mine.png";
const char FLAG_IMAGE_PATH[] = "assets/minesweeper_flag.png";
const char WIN_SOUND_PATH[] = "assets/win.wav";
const char LOSE_SOUND_PATH[] = "assets/lose.wav";
//const char LOSE_SOUND_PATH[] = "assets/laugh.wav";
//const char LOSE_SOUND_PATH[] = "assets/aag.wav";

const int MAX_GRID_SIZE = 10;
const int CELL_SIZE = 50;
const int WINDOW_WIDTH = 1100;
const int WINDOW_HEIGHT = 1000;
const int GAME_AREA_OFFSET_Y = 100;
const int MAX_HIGH_SCORES = 10;
const int MAX_NAME_LENGTH = 20;

const int EASY_SIZE = 6;
const int EASY_MINES = 3;
const int MEDIUM_SIZE = 8;
const int MEDIUM_MINES = 8;
const int HARD_SIZE = 10;
const int HARD_MINES = 12;

const int SCREEN_MENU = 0;
const int SCREEN_GAME = 1;
const int SCREEN_PAUSE = 2;
const int SCREEN_GAME_OVER = 3;
const int SCREEN_SCORES = 4;
const int SCREEN_SETTINGS = 5;

const int DIFFICULTY_EASY = 0;
const int DIFFICULTY_MEDIUM = 1;
const int DIFFICULTY_HARD = 2;

#endif
