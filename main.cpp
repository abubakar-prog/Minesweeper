#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cstdlib>
#include <ctime>
#include "constants.h"
#include "game_state.h"
#include "game_logic.h"
#include "rendering.h"
#include "menu.h"
#include "file_handler.h"
using namespace std;
using namespace sf;

int main() {
    srand((unsigned int)time(0));
    sf::RenderWindow window(sf::VideoMode({ 800, 700 }), "Minesweeper Game");
    sf::Image icon;
    if (icon.loadFromFile("minesweeper_mine.png")) {
        window.setIcon(icon);
    }
    sf::Font font;
    if (!loadFont(font)) {
        return -1;
    }
    sf::Texture mineTexture;
    sf::Texture flagTexture;
    sf::SoundBuffer winSoundBuffer;
    sf::SoundBuffer loseSoundBuffer;
    loadAssets(mineTexture, flagTexture, winSoundBuffer, loseSoundBuffer);
    sf::Sound winSound(winSoundBuffer);
    sf::Sound loseSound(loseSoundBuffer);
    initializeMenuState();
    loadHighScores();
    loadSettings();

    while (window.isOpen()) {

        while (const auto event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }

            if (event->is<sf::Event::MouseButtonPressed>()) {
                const auto mouseData = event->getIf<sf::Event::MouseButtonPressed>();
                float x = (float)mouseData->position.x;
                float y = (float)mouseData->position.y;
				cout << "x: " << x << " y: " << y << endl;
                int buttonType = (mouseData->button == sf::Mouse::Button::Left) ? 0 : 1;
                if (currentScreen == SCREEN_MENU) {
                    if (buttonType == 0) handleMenuInput(x, y, font);
                }
                else if (currentScreen == SCREEN_GAME) {
                    handleGameInput(x, y, buttonType);
                }
                else if (currentScreen == SCREEN_PAUSE) {
                    if (buttonType == 0) handlePauseInput(x, y);
                }
                else if (currentScreen == SCREEN_GAME_OVER) {
                    if (buttonType == 0) handleGameOverInput(x, y);
                }
                else if (currentScreen == SCREEN_SCORES) {
                    if (buttonType == 0) handleScoresInput(x, y);
                }
                else if (currentScreen == SCREEN_SETTINGS) {
                    if (buttonType == 0) handleSettingsInput(x, y);
                }
            }
        }
        if (gameWon && !winSoundPlayed) {
            winSound.play();
            winSoundPlayed = true;
        }
        if (gameOver && !gameWon && !loseSoundPlayed) {
            loseSound.play();
            loseSoundPlayed = true;
        }
        window.clear(sf::Color(40, 40, 40));
        if (currentScreen == SCREEN_MENU) {
            drawMainMenu(window, font);
        }
        else if (currentScreen == SCREEN_GAME) {
            drawGame(window, font, mineTexture, flagTexture);
        }
        else if (currentScreen == SCREEN_PAUSE) {
            drawPauseMenu(window, font);
        }
        else if (currentScreen == SCREEN_GAME_OVER) {
            drawGameOverScreen(window, font, mineTexture, flagTexture);
        }
        else if (currentScreen == SCREEN_SCORES) {
            drawHighScores(window, font);
        }
        else if (currentScreen == SCREEN_SETTINGS) {
            drawSettings(window, font);
        }

        window.display();
    }

    return 0;
}
