#include "rendering.h"
#include "game_state.h"
#include "constants.h"
#include <iostream>

bool loadFont(sf::Font& font) {
    if (font.openFromFile("arial.ttf")) return true;
    if (font.openFromFile("Minesweeper\ARIAL.TTF")) return true;
    if (font.openFromFile("C:\\Windows\\Fonts\\arial.ttf")) return true;
    if (font.openFromFile("/System/Library/Fonts/Supplemental/Arial.ttf")) return true;
    return false;
}

bool loadAssets(sf::Texture& mineTexture, sf::Texture& flagTexture, sf::SoundBuffer& winBuffer, sf::SoundBuffer& loseBuffer) {
    bool allLoaded = true;
    if (!mineTexture.loadFromFile(MINE_IMAGE_PATH)) {
        std::cerr << "Failed to load mine image\n";
        allLoaded = false;
    }
    if (!flagTexture.loadFromFile(FLAG_IMAGE_PATH)) {
        std::cerr << "Failed to load flag image\n";
        allLoaded = false;
    }
    if (!winBuffer.loadFromFile(WIN_SOUND_PATH)) {
        std::cerr << "Failed to load win sound\n";
        allLoaded = false;
    }
    if (!loseBuffer.loadFromFile(LOSE_SOUND_PATH)) {
        std::cerr << "Failed to load lose sound\n";
        allLoaded = false;
    }
    return allLoaded;
}

void drawGame(sf::RenderWindow& window, sf::Font& font, const sf::Texture& mineTexture, const sf::Texture& flagTexture) {
    sf::RectangleShape titleBar;
    titleBar.setSize(sf::Vector2f(800.0f, 80.0f));
    titleBar.setPosition(sf::Vector2f(0.0f, 0.0f));
    titleBar.setFillColor(sf::Color(30, 30, 30));
    window.draw(titleBar);
    sf::Text title(font);
    title.setString("MINESWEEPER");
    title.setCharacterSize(32);
    title.setFillColor(sf::Color(255, 255, 255));
    title.setStyle(sf::Text::Bold);
    title.setPosition(sf::Vector2f(20.0f, 20.0f));
    window.draw(title);
    char mineCountBuffer[50];
    int remainingMines = currentMineCount - flagsPlaced;
    int idx = 0;
    mineCountBuffer[idx++] = 'M';
    mineCountBuffer[idx++] = 'i';
    mineCountBuffer[idx++] = 'n';
    mineCountBuffer[idx++] = 'e';
    mineCountBuffer[idx++] = 's';
    mineCountBuffer[idx++] = ':';
    mineCountBuffer[idx++] = ' ';
    if (remainingMines < 0) {
        mineCountBuffer[idx++] = '-';
        remainingMines = -remainingMines;
    }
    if (remainingMines >= 10) {
        mineCountBuffer[idx++] = '0' + (remainingMines / 10);
    }
    mineCountBuffer[idx++] = '0' + (remainingMines % 10);
    mineCountBuffer[idx] = '\0';
    sf::Text mineCounter(font);
    mineCounter.setString(mineCountBuffer);
    mineCounter.setCharacterSize(20);
    mineCounter.setFillColor(sf::Color(255, 255, 0));
    mineCounter.setPosition(sf::Vector2f(480.0f, 17.0f));
    window.draw(mineCounter);
    char cellsBuffer[50];
    idx = 0;
    cellsBuffer[idx++] = 'C';
    cellsBuffer[idx++] = 'e';
    cellsBuffer[idx++] = 'l';
    cellsBuffer[idx++] = 'l';
    cellsBuffer[idx++] = 's';
    cellsBuffer[idx++] = ':';
    cellsBuffer[idx++] = ' ';
    int tempCells = cellsRevealed;
    if (tempCells >= 100) {
        cellsBuffer[idx++] = '0' + (tempCells / 100);
        tempCells %= 100;
    }
    if (cellsRevealed >= 10 || cellsRevealed >= 100) {
        cellsBuffer[idx++] = '0' + (tempCells / 10);
    }
    cellsBuffer[idx++] = '0' + (tempCells % 10);
    cellsBuffer[idx] = '\0';
    sf::Text scoreText(font);
    scoreText.setString(cellsBuffer);
    scoreText.setCharacterSize(20);
    scoreText.setFillColor(sf::Color(255, 255, 0));
    scoreText.setPosition(sf::Vector2f(480.0f, 42.0f));
    window.draw(scoreText);
    sf::RectangleShape pauseButton;
    pauseButton.setSize(sf::Vector2f(73.0f, 30.0f));
    pauseButton.setPosition(sf::Vector2f(640.0f, 15.0f));
    pauseButton.setFillColor(sf::Color(100, 100, 150));
    pauseButton.setOutlineThickness(2.0f);
    pauseButton.setOutlineColor(sf::Color(200, 200, 200));
    window.draw(pauseButton);
    sf::Text pauseText(font);
    pauseText.setString("Pause");
    pauseText.setCharacterSize(20);
    pauseText.setFillColor(sf::Color(255, 255, 255));
    pauseText.setPosition(sf::Vector2f(645.0f, 18.0f));
    window.draw(pauseText);
    sf::RectangleShape menuButton;
    menuButton.setSize(sf::Vector2f(60.0f, 30.0f));
    menuButton.setPosition(sf::Vector2f(720.0f, 15.0f));
    menuButton.setFillColor(sf::Color(150, 100, 100));
    menuButton.setOutlineThickness(2.0f);
    menuButton.setOutlineColor(sf::Color(200, 200, 200));
    window.draw(menuButton);
    sf::Text menuText(font);
    menuText.setString("Menu");
    menuText.setCharacterSize(20);
    menuText.setFillColor(sf::Color(255, 255, 255));
    menuText.setPosition(sf::Vector2f(727.0f, 18.0f));
    window.draw(menuText);
    int gridPixelSize = currentGridSize * 50;
    int offsetX = (800 - gridPixelSize) / 2;
    for (int i = 0; i < currentGridSize; i++) {
        for (int j = 0; j < currentGridSize; j++) {
            float cellX = offsetX + j * 50 + 1.0f;
            float cellY = 100 + i * 50 + 1.0f;
            sf::RectangleShape cell;
            cell.setSize(sf::Vector2f(48.0f, 48.0f));
            cell.setPosition(sf::Vector2f(cellX, cellY));
            if (revealed[i][j]) {
                if (grid[i][j] == -1) {
                    cell.setFillColor(sf::Color(255, 255,255));
                }
                else {
                    cell.setFillColor(sf::Color(170, 170, 170));
                }
            }
            else {
                cell.setFillColor(sf::Color(255, 255, 255));
            }
            cell.setOutlineThickness(1.0f);
            cell.setOutlineColor(sf::Color(50, 50, 50));
            window.draw(cell);
            if (flagged[i][j] && !revealed[i][j]) {
                sf::Sprite flagSprite(flagTexture);
                float scale = 42.0f / flagTexture.getSize().x;
                flagSprite.setScale(sf::Vector2f(scale, scale));
                flagSprite.setPosition(sf::Vector2f(cellX + 3.2f, cellY + 3.2f));
                window.draw(flagSprite);
            }
            if (revealed[i][j]) {
                if (grid[i][j] == -1) {
                    sf::Sprite mineSprite(mineTexture);
                    float scale = 42.0f / mineTexture.getSize().x;
                    mineSprite.setScale(sf::Vector2f(scale, scale));
                    mineSprite.setPosition(sf::Vector2f(cellX +3.2f , cellY+3.2f ));
                    window.draw(mineSprite);
                }
                else if (grid[i][j] > 0) {
                    sf::Text text(font);
                    char numBuffer[2];
                    numBuffer[0] = '0' + grid[i][j];
                    numBuffer[1] = '\0';
                    text.setString(numBuffer);
                    text.setCharacterSize(26);
                    text.setStyle(sf::Text::Bold);
                    text.setPosition(sf::Vector2f(cellX + 14.0f, cellY + 10.0f));
                    if (grid[i][j] == 1) text.setFillColor(sf::Color(0, 0, 255));
                    else if (grid[i][j] == 2) text.setFillColor(sf::Color(0, 255, 0));
                    else if (grid[i][j] == 3) text.setFillColor(sf::Color(255, 0, 0));
                    else if (grid[i][j] == 4) text.setFillColor(sf::Color(128, 0, 128));
                    else if (grid[i][j] == 5) text.setFillColor(sf::Color(128, 0, 0));
                    else text.setFillColor(sf::Color(0, 0, 0));
                    window.draw(text);
                }
            }
        }
    }
}
