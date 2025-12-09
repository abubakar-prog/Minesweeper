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

    srand((unsigned int)time(0)); //Random for mines

    sf::RenderWindow window(sf::VideoMode({ 1100, 1000 }), "Minesweeper Game");

    sf::Image icon; //icon
    if (icon.loadFromFile("minesweeper_mine.png")) {
        window.setIcon(icon);
    }

	sf::Texture backgroundTexture; //background
    if (!backgroundTexture.loadFromFile("assets/blackwall.jpg")) {
		cout << "Failed to load background image"<<endl;
    }

    sf::Font font; //check fonts
    if (!loadFont(font)) {
        return -1;
    }
    
    //load-ers
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

    while (window.isOpen()) //game loop
    {

        while (const auto event = window.pollEvent()) //events
        {
            if (event->is<sf::Event::Closed>()) //close windows
            {
                window.close();
            }

            if (event->is<sf::Event::MouseButtonPressed>()) //every mouse button
            {
                const auto mouseData = event->getIf<sf::Event::MouseButtonPressed>();
                
                //mouse screen coords
                float x = (float)mouseData->position.x / scaleX;
                float y = (float)mouseData->position.y / scaleY;
				cout << "x: " << x << " y: " << y << endl;
				//left or right, 0 left, 1 right
                int buttonType = (mouseData->button == sf::Mouse::Button::Left) ? 0 : 1;
                
                //gamestate
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
            if (event->is<sf::Event::TextEntered>()) {
                if (currentScreen == SCREEN_GAME_OVER && enteringName) {
                    const auto textData = event->getIf<sf::Event::TextEntered>();
                    if (textData->unicode == 8 && nameLength > 0) {
                        nameLength--;
                        playerName[nameLength] = '\0';
                    }
                    else if (textData->unicode == 13) {
                        if (nameLength > 0) {
                            addHighScore(playerScore, playerName, timerSeconds);
                            saveHighScores();
                            enteringName = false;
                        }
                    }
                    else if (textData->unicode >= 32 && textData->unicode < 127 && nameLength < MAX_NAME_LENGTH - 1) {
                        playerName[nameLength] = static_cast<char>(textData->unicode);
                        nameLength++;
                        playerName[nameLength] = '\0';
                    }
                }
            }
        }
        //play win sound
        if (gameWon && !winSoundPlayed) {
            winSound.play();
            winSoundPlayed = true;
        }
        //play lose sound
        if (gameOver && !gameWon && !loseSoundPlayed) {
            loseSound.play();
            loseSoundPlayed = true;
        }
        //timer
        if (timerStarted && !gameOver && !gameWon) {
            timerSeconds = (int)gameClock.getElapsedTime().asSeconds();
        }
		//dark background
        window.clear(sf::Color(40, 40, 40));
		//reload wallpaper each frame
        const sf::Texture backgroundTexture("assets/blackwall.jpg");
        sf::Sprite bgSprite(backgroundTexture);
        window.draw(bgSprite);

		//draw based on gamestate
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
        //draw all frame
        window.display();
    }

    return 0;
}
