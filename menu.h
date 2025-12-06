#ifndef MENU_H
#define MENU_H

#include <SFML/Graphics.hpp>

void drawButton(sf::RenderWindow& window, sf::Font& font, float x, float y, float width, float height, const char text[], int bgR, int bgG, int bgB, int textR, int textG, int textB);
void initializeMenuState();
void drawMainMenu(sf::RenderWindow& window, sf::Font& font);
void drawPauseMenu(sf::RenderWindow& window, sf::Font& font);
void drawGameOverScreen(sf::RenderWindow& window, sf::Font& font, const sf::Texture& mineTexture, const sf::Texture& flagTexture);
void drawHighScores(sf::RenderWindow& window, sf::Font& font);
void drawSettings(sf::RenderWindow& window, sf::Font& font);
void handleMenuInput(float mouseX, float mouseY, sf::Font& font);
void handleGameInput(float mouseX, float mouseY, int button);
void handlePauseInput(float mouseX, float mouseY);
void handleGameOverInput(float mouseX, float mouseY);
void handleScoresInput(float mouseX, float mouseY);
void handleSettingsInput(float mouseX, float mouseY);
bool isButtonClicked(float mouseX, float mouseY, float btnX, float btnY, float width, float height);

#endif