/*
** EPITECH PROJECT, 2019
** SFMLRectangle.cpp
** File description:
** rectangle in sfml
*/

#include "SFMLRectangle.hpp"

RectangleSfml::RectangleSfml(size_t width, size_t height):
_rect(sf::Vector2f(width, height))
{
}

RectangleSfml::~RectangleSfml(void)
{
}

size_t RectangleSfml::getWidth(void) const
{
	return (_rect.getSize().x);
}

size_t RectangleSfml::getHeight(void) const
{
	return (_rect.getSize().y);
}

size_t RectangleSfml::getPosX(void) const
{
	return (_rect.getPosition().x);
}

size_t RectangleSfml::getPosY(void) const
{
	return (_rect.getPosition().y);
}

void RectangleSfml::setColor(size_t r, size_t g, size_t b)
{
	_rect.setFillColor(sf::Color(r, g, b));
}

void RectangleSfml::setPosition(size_t x, size_t y)
{
	_rect.setPosition(x, y);
}

void RectangleSfml::setSize(size_t width, size_t height)
{
	_rect.setSize(sf::Vector2f(width, height));
}

bool RectangleSfml::getGlobalBounds(size_t mouse_x, size_t mouse_y) const
{
	sf::Vector2f mousePosF(static_cast<float>(mouse_x), static_cast<float>(mouse_y));
	return (_rect.getGlobalBounds().contains(mousePosF));
}

sf::RectangleShape RectangleSfml::getRect(void)
{
	return (_rect);
}