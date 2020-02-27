/*
** EPITECH PROJECT, 2019
** SFMLText.cpp
** File description:
** text in sfml
*/

#include "SFMLText.hpp"

Text::Text(void)
{
}

Text::~Text(void)
{
}

float Text::getWidth(void)
{
	sf::Font font;
	font.loadFromFile("../../src/Fonts/SupersonicRocketship.ttf");
	_text.setFont(font);
	return (_text.getLocalBounds().width);
}

float Text::getHeight(void)
{
	sf::Font font;
	font.loadFromFile("../../src/Fonts/SupersonicRocketship.ttf");
	_text.setFont(font);
	return (_text.getLocalBounds().height);
}

size_t Text::getPosX(void) const
{
	return (_text.getPosition().x);
}

size_t Text::getPosY(void) const
{
	return (_text.getPosition().y);
}

void Text::setString(std::string str)
{
	_text.setString(str);
}

void Text::setPosition(size_t x, size_t y)
{
	_text.setPosition(x, y);
}

void Text::setFontSize(size_t size)
{
	_text.setCharacterSize(size);
}

void Text::setFontColor(size_t r, size_t g, size_t b)
{
	sf::Color fontColor(r, g, b);
	_text.setFillColor(fontColor);
}