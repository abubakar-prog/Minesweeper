#include "rendering.h"
#include "game_state.h"
#include "constants.h"
#include <iostream>
using namespace sf;
using namespace std;


bool loadFont(sf::Font& font) //load fonts
{
    if (font.openFromFile("assets/VIDEOPHREAK.ttf")) return true;
    if (font.openFromFile("Minesweeper/ARIAL.TTF")) return true;
    if (font.openFromFile("C:\\Windows\\Fonts\\arial.ttf")) return true;
    if (font.openFromFile("/System/Library/Fonts/Supplemental/Arial.ttf")) return true;
    return false;
}

bool loadAssets(sf::Texture& mineTexture, sf::Texture& flagTexture, sf::SoundBuffer& winBuffer, sf::SoundBuffer& loseBuffer) //check assets
{
    bool allLoaded = true;
    if (!mineTexture.loadFromFile(MINE_IMAGE_PATH)) {
        std::cerr << "Failed to load mine image"<<endl;
        allLoaded = false;
    }
    if (!flagTexture.loadFromFile(FLAG_IMAGE_PATH)) {
        std::cerr << "Failed to load flag image"<<endl;
        allLoaded = false;
    }
    if (!winBuffer.loadFromFile(WIN_SOUND_PATH)) {
        std::cerr << "Failed to load win sound"<<endl;
        allLoaded = false;
    }
    if (!loseBuffer.loadFromFile(LOSE_SOUND_PATH)) {
        std::cerr << "Failed to load lose sound"<<endl;
        allLoaded = false;
    }
    return allLoaded;
}

void drawGame(sf::RenderWindow& window, sf::Font& font, const sf::Texture& mineTexture, const sf::Texture& flagTexture) 
{
    //Title
    sf::RectangleShape titleBar;
    titleBar.setSize(sf::Vector2f (1100.0f, 80.0f));
    titleBar.setPosition(sf::Vector2f (0.0f, 0.0f));
    titleBar.setFillColor(sf::Color(30,30,30,255));
    window.draw(titleBar);

    //Title text
    sf::Text title(font, "MINESWEEPER", 32);
    title.setFillColor(sf::Color::White);
    title.setStyle(sf::Text::Bold);
    title.setPosition(sf::Vector2f(20.0f, 20.0f));
    window.draw(title);

    //Mine counter
    int remainingMines = currentMineCount - flagsPlaced;
    char mineText[50] = "Mines: ";
    int idx = 7;
    if (remainingMines < 0) {
        mineText[idx++] = '-';
        remainingMines = -remainingMines;
    }
    if (remainingMines >= 10) {
        mineText[idx++] = '0' + (remainingMines / 10);
    }
    mineText[idx++] = '0' + (remainingMines % 10);
    mineText[idx] = '\0';

    sf::Text mineCounter(font, mineText, 20);
    mineCounter.setFillColor(sf::Color::Yellow);
    mineCounter.setPosition(sf::Vector2f(480.0f, 17.0f));
    window.draw(mineCounter);

    //Cells revealed counter
    char cellText[50] = "Cells: ";
    int idx2 = 7;
    int tempCells = cellsRevealed;
    if (tempCells >= 100) {
        cellText[idx2++] = '0' + (tempCells / 100);
        tempCells %= 100;
    }
    if (cellsRevealed >= 10) {
        cellText[idx2++] = '0' + (tempCells / 10);
    }
    cellText[idx2++] = '0' + (tempCells % 10);
    cellText[idx2] = '\0';

    sf::Text scoreText(font, cellText, 20);
    scoreText.setFillColor(sf::Color::Yellow);
    sf::Vector2f scorePos;
    scorePos.x = 480.0f;
    scorePos.y = 42.0f;
    scoreText.setPosition(scorePos);
    window.draw(scoreText);

    //Timer
    char timeText[50] = "Time: ";
    int idx3 = 6;
    int tempTime = timerSeconds;
    if (tempTime >= 100) {
        timeText[idx3++] = '0' + (tempTime / 100);
        tempTime %= 100;
    }
    if (timerSeconds >= 10) {
        timeText[idx3++] = '0' + (tempTime / 10);
    }
    timeText[idx3++] = '0' + (tempTime % 10);
    timeText[idx3++] = 's';
    timeText[idx3] = '\0';

    //timer text drawn
    sf::Text timerText(font, timeText, 20);
    timerText.setFillColor(sf::Color::Yellow);
    timerText.setPosition(sf::Vector2f(680.0f, 17.0f));
    window.draw(timerText);


    //pause button
    sf::RectangleShape pauseButton;
    sf::Vector2f pauseSize;
    pauseSize.x = 73.0f;
    pauseSize.y = 30.0f;
    pauseButton.setSize(pauseSize);
    sf::Vector2f pausePos;
    pausePos.x = 840.0f;
    pausePos.y = 15.0f;
    pauseButton.setPosition(pausePos);
    sf::Color pauseColor;
    pauseColor.r = 100;
    pauseColor.g = 100;
    pauseColor.b = 150;
    pauseColor.a = 255;
    pauseButton.setFillColor(pauseColor);
    //pauseButton.setOutlineThickness(2.0f);
    sf::Color lightGray;
    lightGray.r = 200;
    lightGray.g = 200;
    lightGray.b = 200;
    lightGray.a = 255;
    //pauseButton.setOutlineColor(lightGray);
    window.draw(pauseButton);


    //pause text
    sf::Text pauseText(font,"Pause",20);
    pauseText.setFillColor(sf::Color::White);
    sf::Vector2f pauseTextPos;
    pauseTextPos.x = 845.0f;
    pauseTextPos.y = 18.0f;
    pauseText.setPosition(pauseTextPos);
    window.draw(pauseText);

    //menu button
    sf::RectangleShape menuButton;
    sf::Vector2f menuSize;
    menuSize.x = 75.0f;
    menuSize.y = 30.0f;
    menuButton.setSize(menuSize);
    sf::Vector2f menuPos;
    menuPos.x = 920.0f;
    menuPos.y = 15.0f;
    menuButton.setPosition(menuPos);
    sf::Color menuColor;
    menuColor.r = 150;
    menuColor.g = 100;
    menuColor.b = 100;
    menuColor.a = 255;
    menuButton.setFillColor(menuColor);
    //menuButton.setOutlineThickness(2.0f);
    //menuButton.setOutlineColor(lightGray);
    window.draw(menuButton);

    //menu text
    sf::Text menuText(font,"Menu",20);
    menuText.setFillColor(sf::Color::White);
    sf::Vector2f menuTextPos;
    menuTextPos.x = 927.0f;
    menuTextPos.y = 18.0f;
    menuText.setPosition(menuTextPos);
    window.draw(menuText);

    //grid
    int gridPixelSize = currentGridSize * 50;
    int offsetX = (1100 - gridPixelSize) / 2;

    //drawing cell
    for (int i = 0; i < currentGridSize; i++) {
        for (int j = 0; j < currentGridSize; j++) {
            float cellX = offsetX + j * 50 + 1.0f;
            float cellY = 100 + i * 50 + 1.0f;

            //cell background
            sf::RectangleShape cell;
            sf::Vector2f cellSize;
            cellSize.x = 48.0f;
            cellSize.y = 48.0f;
            cell.setSize(cellSize);
            sf::Vector2f cellPos;
            cellPos.x = cellX;
            cellPos.y = cellY;
            cell.setPosition(cellPos);

            //change color
            if (revealed[i][j]) {
                if (grid[i][j] == -1) {
                    cell.setFillColor(sf::Color::White);
                }
                else {
                    sf::Color gray;
                    gray.r = 170;
                    gray.g = 170;
                    gray.b = 170;
                    gray.a = 255;
                    cell.setFillColor(gray);
                }
            }
            else {
                cell.setFillColor(sf::Color::White);
            }

            //cell.setOutlineThickness(1.0f);
            //sf::Color darkOutline;
            //darkOutline.r = 50;
            //darkOutline.g = 50;
            //darkOutline.b = 50;
            //darkOutline.a = 255;
            //cell.setOutlineColor(darkOutline);
            window.draw(cell);

            //Draw flag
            if (flagged[i][j] && !revealed[i][j]) {
                sf::Sprite flagSprite(flagTexture);
                float scale = 42.0f / flagTexture.getSize().x;
                sf::Vector2f flagScale;
                flagScale.x = scale;
                flagScale.y = scale;
                flagSprite.setScale(flagScale);
                sf::Vector2f flagPos;
                flagPos.x = cellX + 3.2f;
                flagPos.y = cellY + 3.2f;
                flagSprite.setPosition(flagPos);
                window.draw(flagSprite);
            }

            //Draw revealed content
            if (revealed[i][j]) {
                if (grid[i][j] == -1) //Draw if mine
                {
                    Sprite mineSprite(mineTexture);
                    float scale = 42.0f / mineTexture.getSize().x;
                    Vector2f mineScale;
                    mineScale.x = scale;
                    mineScale.y = scale;
                    mineSprite.setScale(mineScale);
                    Vector2f minePos;
                    minePos.x = cellX + 3.2f;
                    minePos.y = cellY + 3.2f;
                    mineSprite.setPosition(minePos);
                    window.draw(mineSprite);
                }
                else if (grid[i][j] > 0) 
                {
                    //Draw number
                    char numText[2];
                    numText[0] = '0' + grid[i][j];
                    numText[1] = '\0';

                    Text text(font, numText, 26);
                    text.setStyle(sf::Text::Bold);
                    sf::Vector2f textPos;
                    textPos.x = cellX + 14.0f;
                    textPos.y = cellY + 10.0f;
                    text.setPosition(textPos);

                    //color of number to draw
                    Color numColor;
                    numColor.a = 255;
                    if (grid[i][j] == 1) {
                        numColor.r = 0; numColor.g = 0; numColor.b = 255;
                    }
                    else if (grid[i][j] == 2) {
                        numColor.r = 0; numColor.g = 255; numColor.b = 0;
                    }
                    else if (grid[i][j] == 3) {
                        numColor.r = 255; numColor.g = 0; numColor.b = 0;
                    }
                    else if (grid[i][j] == 4) {
                        numColor.r = 128; numColor.g = 0; numColor.b = 128;
                    }
                    else if (grid[i][j] == 5) {
                        numColor.r = 128; numColor.g = 0; numColor.b = 0;
                    }
                    else {
                        numColor.r = 0; numColor.g = 0; numColor.b = 0;
                    }
                    text.setFillColor(numColor);
                    window.draw(text);
                }
            }
        }
    }
}
