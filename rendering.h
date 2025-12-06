#ifndef RENDERING_H
#define RENDERING_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

bool loadFont(sf::Font& font);
bool loadAssets(sf::Texture& mineTexture, sf::Texture& flagTexture, sf::SoundBuffer& winBuffer, sf::SoundBuffer& loseBuffer);
void drawGame(sf::RenderWindow& window, sf::Font& font, const sf::Texture& mineTexture, const sf::Texture& flagTexture);

#endif