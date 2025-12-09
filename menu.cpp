#include "menu.h"
#include "game_state.h"
#include "game_logic.h"
#include "rendering.h"
#include "file_handler.h"
#include "constants.h"
#include <cstdlib>
using namespace std;
using namespace sf;

void drawButton(sf::RenderWindow& window, sf::Font& font, float x, float y, float width, float height, const char text[], int bgR, int bgG, int bgB, int textR, int textG, int textB) {
    sf::RectangleShape button;
    button.setSize(sf::Vector2f(width, height));
    button.setPosition(sf::Vector2f(x, y));
    button.setFillColor(sf::Color(bgR, bgG, bgB));
    //button.setOutlineThickness(2.0f);
    //button.setOutlineColor(sf::Color(200, 200, 200));
    window.draw(button);
    sf::Text buttonText(font);
    buttonText.setString(text);
    buttonText.setCharacterSize(20);
    buttonText.setFillColor(sf::Color(textR, textG, textB));
    sf::FloatRect textBounds = buttonText.getLocalBounds();
    buttonText.setPosition(sf::Vector2f(x + (width - textBounds.size.x) / 2.0f, y + (height - textBounds.size.y) / 2.0f - 5.0f));
    window.draw(buttonText);
}

void initializeMenuState() {
    currentScreen = SCREEN_MENU;
}

bool isButtonClicked(float mouseX, float mouseY, float btnX, float btnY, float width, float height) {
    return mouseX >= btnX && mouseX <= btnX + width && mouseY >= btnY && mouseY <= btnY + height;
}

void drawMainMenu(sf::RenderWindow& window, sf::Font& font) {
    sf::Text title(font);
    title.setString("MINESWEEPER");
    title.setCharacterSize(60);
    title.setFillColor(sf::Color(255, 255, 255));
    title.setStyle(sf::Text::Bold);
    title.setPosition(sf::Vector2f(350.0f, 50.0f));
    window.draw(title);
    drawButton(window, font, 450.0f, 180.0f, 200.0f, 50.0f, "Start New Game", 70, 130, 70, 255, 255, 255);
    drawButton(window, font, 450.0f, 250.0f, 200.0f, 50.0f, "Load Game", 70, 100, 180, 255, 255, 255);
    drawButton(window, font, 450.0f, 320.0f, 200.0f, 50.0f, "High Scores", 180, 130, 70, 255, 255, 255);
    drawButton(window, font, 450.0f, 390.0f, 200.0f, 50.0f, "Settings", 130, 70, 180, 255, 255, 255);
    drawButton(window, font, 450.0f, 460.0f, 200.0f, 50.0f, "Exit", 180, 70, 70, 255, 255, 255);
    //sf::Text instructions(font);
    //instructions.setString("Left Click: Reveal | Right Click: Flag");
    //instructions.setCharacterSize(18);
    //instructions.setFillColor(sf::Color(200, 200, 200));
    //instructions.setPosition(sf::Vector2f(240.0f, 580.0f));
    //window.draw(instructions);
}

void drawPauseMenu(sf::RenderWindow& window, sf::Font& font) {
    sf::RectangleShape overlay;
    overlay.setSize(sf::Vector2f(1100.0f, 1000.0f));
    overlay.setFillColor(sf::Color(0, 0, 0, 180));
    window.draw(overlay);
    sf::Text pauseText(font);
    pauseText.setString("GAME PAUSED");
    pauseText.setCharacterSize(50);
    pauseText.setFillColor(sf::Color(255, 255, 255));
    pauseText.setStyle(sf::Text::Bold);
    pauseText.setPosition(sf::Vector2f(400.0f, 150.0f));
    window.draw(pauseText);
    drawButton(window, font, 450.0f, 280.0f, 200.0f, 50.0f, "Resume", 70, 130, 70, 255, 255, 255);
    drawButton(window, font, 450.0f, 350.0f, 200.0f, 50.0f, "Save Game", 70, 100, 180, 255, 255, 255);
    drawButton(window, font, 450.0f, 420.0f, 200.0f, 50.0f, "Main Menu", 180, 70, 70, 255, 255, 255);
}
void drawGameOverScreen(sf::RenderWindow& window, sf::Font& font, const sf::Texture& mineTexture, const sf::Texture& flagTexture) {
    drawGame(window, font, mineTexture, flagTexture);
    sf::RectangleShape overlay;
    overlay.setSize(sf::Vector2f(1100.0f, 1000.0f));
    overlay.setFillColor(sf::Color(0, 0, 0, 180));
    window.draw(overlay);
    if (enteringName) {
        sf::Text namePrompt(font);
        namePrompt.setString("Enter Your Name:");
        namePrompt.setCharacterSize(24);
        namePrompt.setFillColor(sf::Color(255, 255, 255));
        namePrompt.setPosition(sf::Vector2f(420.0f, 330.0f));
        window.draw(namePrompt);

        sf::RectangleShape nameBox;
        nameBox.setSize(sf::Vector2f(250.0f, 40.0f));
        nameBox.setPosition(sf::Vector2f(425.0f, 370.0f));
        nameBox.setFillColor(sf::Color(50, 50, 50));
        nameBox.setOutlineThickness(2.0f);
        nameBox.setOutlineColor(sf::Color(200, 200, 200));
        window.draw(nameBox);

        sf::Text nameInput(font);
        nameInput.setString(playerName);
        nameInput.setCharacterSize(24);
        nameInput.setFillColor(sf::Color(255, 255, 255));
        nameInput.setPosition(sf::Vector2f(435.0f, 375.0f));
        window.draw(nameInput);

        drawButton(window, font, 450.0f, 430.0f, 200.0f, 50.0f, "Submit", 70, 130, 70, 255, 255, 255);
        return;
    }
    sf::Text message(font);
    message.setCharacterSize(50);
    message.setStyle(sf::Text::Bold);

    if (gameWon) {
        message.setString("YOU WIN!");
        message.setFillColor(sf::Color(0, 255, 0));
        message.setPosition(sf::Vector2f(430.0f, 200.0f));
        window.draw(message);
        char scoreBuffer[50];
        int idx = 0;
        scoreBuffer[idx++] = 'S';
        scoreBuffer[idx++] = 'c';
        scoreBuffer[idx++] = 'o';
        scoreBuffer[idx++] = 'r';
        scoreBuffer[idx++] = 'e';
        scoreBuffer[idx++] = ':';
        scoreBuffer[idx++] = ' ';
        int tempScore = playerScore;
        if (tempScore >= 1000) {
            scoreBuffer[idx++] = '0' + (tempScore / 1000);
            tempScore %= 1000;
        }
        if (playerScore >= 100 || playerScore >= 1000) {
            scoreBuffer[idx++] = '0' + (tempScore / 100);
            tempScore %= 100;
        }
        if (playerScore >= 10 || playerScore >= 100 || playerScore >= 1000) {
            scoreBuffer[idx++] = '0' + (tempScore / 10);
        }

        scoreBuffer[idx++] = '0' + (tempScore % 10);
        scoreBuffer[idx] = '\0';
        sf::Text scoreText(font);
        scoreText.setString(scoreBuffer);
        scoreText.setCharacterSize(30);
        scoreText.setFillColor(sf::Color(255, 255, 0));
        scoreText.setPosition(sf::Vector2f(470.0f, 270.0f));
        window.draw(scoreText);
    }
    else {
        message.setString("GAME OVER!");
        message.setFillColor(sf::Color(255, 0, 0));
        message.setPosition(sf::Vector2f(390.0f, 200.0f));
        window.draw(message);
    }
    drawButton(window, font, 450.0f, 350.0f, 200.0f, 50.0f, "New Game", 70, 130, 70, 255, 255, 255);
    drawButton(window, font, 450.0f, 420.0f, 200.0f, 50.0f, "Main Menu", 180, 70, 70, 255, 255, 255);
}
void drawHighScores(sf::RenderWindow& window, sf::Font& font) {
    sf::Text title(font);
    title.setString("HIGH SCORES");
    title.setCharacterSize(50);
    title.setFillColor(sf::Color(255, 255, 0));
    title.setStyle(sf::Text::Bold);
    title.setPosition(sf::Vector2f(390.0f, 50.0f));
    window.draw(title);
    for (int i = 0; i < highScoreCount; i++) {
        char buffer[100];
        int idx = 0;
        buffer[idx++] = '0' + (i + 1);
        buffer[idx++] = '.';
        buffer[idx++] = ' ';
        int j = 0;
        while (highScoreNames[i][j] != '\0' && j < MAX_NAME_LENGTH) {
            buffer[idx++] = highScoreNames[i][j];
            j++;
        }
        buffer[idx++] = ' ';
        buffer[idx++] = '-';
        buffer[idx++] = ' ';
        int tempScore = highScores[i];
        if (tempScore >= 1000) {
            buffer[idx++] = '0' + (tempScore / 1000);
            tempScore %= 1000;
        }
        if (highScores[i] >= 100 || highScores[i] >= 1000) {
            buffer[idx++] = '0' + (tempScore / 100);
            tempScore %= 100;
        }
        if (highScores[i] >= 10 || highScores[i] >= 100 || highScores[i] >= 1000) {
            buffer[idx++] = '0' + (tempScore / 10);
        }
        buffer[idx++] = '0' + (tempScore % 10);
        buffer[idx] = '\0';
        sf::Text scoreText(font);
        scoreText.setString(buffer);
        scoreText.setCharacterSize(24);
        scoreText.setFillColor(sf::Color(255, 255, 255));
        scoreText.setPosition(sf::Vector2f(400.0f, 150.0f + i * 40.0f));
        window.draw(scoreText);
    }
    if (highScoreCount == 0) {
        sf::Text noScores(font);
        noScores.setString("No high scores yet!");
        noScores.setCharacterSize(24);
        noScores.setFillColor(sf::Color(150, 150, 150));
        noScores.setPosition(sf::Vector2f(430.0f, 200.0f));
        window.draw(noScores);
    }
    drawButton(window, font, 450.0f, 880.0f, 200.0f, 50.0f, "Back", 100, 100, 100, 255, 255, 255);
}
void drawSettings(sf::RenderWindow& window, sf::Font& font) {
    sf::Text title(font);
    title.setString("SETTINGS");
    title.setCharacterSize(50);
    title.setFillColor(sf::Color(0, 255, 255));
    title.setStyle(sf::Text::Bold);
    title.setPosition(sf::Vector2f(430.0f, 50.0f));
    window.draw(title);
    sf::Text diffLabel(font);
    diffLabel.setString("Difficulty Level:");
    diffLabel.setCharacterSize(28);
    diffLabel.setFillColor(sf::Color(255, 255, 255));
    diffLabel.setPosition(sf::Vector2f(400.0f, 180.0f));
    window.draw(diffLabel);
    int easyR = (currentDifficulty == DIFFICULTY_EASY) ? 100 : 70;
    int easyG = (currentDifficulty == DIFFICULTY_EASY) ? 200 : 130;
    int easyB = (currentDifficulty == DIFFICULTY_EASY) ? 100 : 70;
    int medR = (currentDifficulty == DIFFICULTY_MEDIUM) ? 200 : 180;
    int medG = (currentDifficulty == DIFFICULTY_MEDIUM) ? 180 : 130;
    int medB = (currentDifficulty == DIFFICULTY_MEDIUM) ? 100 : 70;
    int hardR = (currentDifficulty == DIFFICULTY_HARD) ? 200 : 180;
    int hardG = (currentDifficulty == DIFFICULTY_HARD) ? 100 : 70;
    int hardB = (currentDifficulty == DIFFICULTY_HARD) ? 100 : 70;
    drawButton(window, font, 350.0f, 250.0f, 150.0f, 50.0f, "Easy (6x6)", easyR, easyG, easyB, 255, 255, 255);
    drawButton(window, font, 520.0f, 250.0f, 160.0f, 50.0f, "Medium (8x8)", medR, medG, medB, 255, 255, 255);
    drawButton(window, font, 350.0f, 320.0f, 330.0f, 50.0f, "Hard (10x10)", hardR, hardG, hardB, 255, 255, 255);
    char infoText[100];
    int idx = 0;
    infoText[idx++] = 'M';
    infoText[idx++] = 'i';
    infoText[idx++] = 'n';
    infoText[idx++] = 'e';
    infoText[idx++] = 's';
    infoText[idx++] = ':';
    infoText[idx++] = ' ';
    if (currentMineCount >= 10) {
        infoText[idx++] = '0' + (currentMineCount / 10);
    }
    infoText[idx++] = '0' + (currentMineCount % 10);
    infoText[idx] = '\0';
    sf::Text info(font);
    info.setString(infoText);
    info.setCharacterSize(20);
    info.setFillColor(sf::Color(200, 200, 200));
    info.setPosition(sf::Vector2f(370.0f, 420.0f));
    window.draw(info);
    drawButton(window, font, 450.0f, 850.0f, 200.0f, 50.0f, "Back", 100, 100, 100, 255, 255, 255);
}
void handleMenuInput(float mouseX, float mouseY, sf::Font& font) {
    if (isButtonClicked(mouseX, mouseY, 450.0f, 180.0f, 200.0f, 50.0f)) {
        initializeGame();
        currentScreen = SCREEN_GAME;
    }
    else if (isButtonClicked(mouseX, mouseY, 450.0f, 250.0f, 200.0f, 50.0f)) {
        loadGame();
        if (cellsRevealed > 0) {
            currentScreen = SCREEN_GAME;
        }
    }
    else if (isButtonClicked(mouseX, mouseY, 450.0f, 320.0f, 200.0f, 50.0f)) {
        currentScreen = SCREEN_SCORES;
    }
    else if (isButtonClicked(mouseX, mouseY, 450.0f, 390.0f, 200.0f, 50.0f)) {
        currentScreen = SCREEN_SETTINGS;
    }
    else if (isButtonClicked(mouseX, mouseY, 450.0f, 460.0f, 200.0f, 50.0f)) {
        exit(0);
    }
}
void handleGameInput(float mouseX, float mouseY, int button) {
    if (isButtonClicked(mouseX, mouseY, 840.0f, 15.0f, 73.0f, 30.0f)) {
        currentScreen = SCREEN_PAUSE;
        return;
    }
    if (isButtonClicked(mouseX, mouseY, 920.0f, 15.0f, 60.0f, 30.0f)) {
        currentScreen = SCREEN_MENU;
        return;
    }
    if (!gameOver && !gameWon) {
        int gridPixelSize = currentGridSize * 50;
        int offsetX = (1100 - gridPixelSize) / 2;
        int gridX = ((int)mouseY - 100) / 50;
        int gridY = ((int)mouseX - offsetX) / 50;
        if (gridX >= 0 && gridX < currentGridSize && gridY >= 0 && gridY < currentGridSize) {
            if (button == 0) {
                revealCell(gridX, gridY);
                checkWin();
                if (gameWon) {
                    enteringName = true;
                    nameLength = 0;
                    for (int i = 0; i < MAX_NAME_LENGTH; i++) {
                        playerName[i] = '\0';
                    }
                    currentScreen = SCREEN_GAME_OVER;
                }
                else if (gameOver) {
                    currentScreen = SCREEN_GAME_OVER;
                }
            }
            else if (button == 1) {
                toggleFlag(gridX, gridY);
            }
        }
    }
}
void handlePauseInput(float mouseX, float mouseY) {
    if (isButtonClicked(mouseX, mouseY, 450.0f, 280.0f, 200.0f, 50.0f)) {
        currentScreen = SCREEN_GAME;
    }
    else if (isButtonClicked(mouseX, mouseY, 450.0f, 350.0f, 200.0f, 50.0f)) {
        saveGame();
        currentScreen = SCREEN_GAME;
    }
    else if (isButtonClicked(mouseX, mouseY, 450.0f, 420.0f, 200.0f, 50.0f)) {
        currentScreen = SCREEN_MENU;
    }
}
void handleGameOverInput(float mouseX, float mouseY) {
    if (enteringName) {
        if (isButtonClicked(mouseX, mouseY, 450.0f, 430.0f, 200.0f, 50.0f)) {
            if (nameLength > 0) {
                addHighScore(playerScore, playerName, timerSeconds);
                saveHighScores();
                enteringName = false;
            }
        }
    }
    else {
        if (isButtonClicked(mouseX, mouseY, 450.0f, 350.0f, 200.0f, 50.0f)) {
            initializeGame();
            currentScreen = SCREEN_GAME;
        }
        else if (isButtonClicked(mouseX, mouseY, 450.0f, 420.0f, 200.0f, 50.0f)) {
            currentScreen = SCREEN_MENU;
        }
    }
}
void handleScoresInput(float mouseX, float mouseY) {
    if (isButtonClicked(mouseX, mouseY, 450.0f, 880.0f, 200.0f, 50.0f)) {
        currentScreen = SCREEN_MENU;
    }
}
void handleSettingsInput(float mouseX, float mouseY) {
    if (isButtonClicked(mouseX, mouseY, 350.0f, 250.0f, 150.0f, 50.0f)) {
        setDifficulty(DIFFICULTY_EASY);
        saveSettings();
    }
    else if (isButtonClicked(mouseX, mouseY, 520.0f, 250.0f, 160.0f, 50.0f)) {
        setDifficulty(DIFFICULTY_MEDIUM);
        saveSettings();
    }
    else if (isButtonClicked(mouseX, mouseY, 350.0f, 320.0f, 330.0f, 50.0f)) {
        setDifficulty(DIFFICULTY_HARD);
        saveSettings();
    }
    else if (isButtonClicked(mouseX, mouseY, 450.0f, 850.0f, 200.0f, 50.0f)) {
        currentScreen = SCREEN_MENU;
    }
}
