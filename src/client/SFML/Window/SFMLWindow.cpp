/*
** EPITECH PROJECT, 2019
** SFMLWindow.cpp
** File description:
** window in sfml
*/

#include "SFMLWindow.hpp"

Window::Window(size_t width, size_t height, std::string name):
_window(sf::VideoMode(static_cast<unsigned int>(width), static_cast<unsigned int>(height)), name)
{
}

Window::~Window(void)
{
}

size_t Window::getWidth(void) const
{
	return (_window.getSize().x);
}

size_t Window::getHeight(void) const
{
	return (_window.getSize().y);
}

bool Window::isOpen(void) const
{
	return (_window.isOpen());
}

void Window::clear(int r, int g, int b)
{
	_window.clear(sf::Color(r, g, b));
}

void Window::display(void)
{
	_window.display();
}

void Window::close(void)
{
	_window.close();
}

bool Window::pollEvent(void)
{
	return (_window.pollEvent(_event));
}

bool Window::getEventClose(void) const
{
	if (_event.type == sf::Event::Closed)
		return (true);
	return (false);
}

bool Window::getEventKeyPressed(void) const
{
	if (_event.type == sf::Event::KeyPressed)
		return (true);
	return (false);
}

bool Window::getEventKeyEscape(void) const
{
	if (_event.key.code == sf::Keyboard::Escape)
		return (true);
	return (false);
}

bool Window::getEventKeyReturn(void) const
{
	if (_event.key.code == sf::Keyboard::Return)
		return (true);
	return (false);
}

bool Window::getEventMouseButtonPressed(void) const
{
	if (_event.type == sf::Event::MouseButtonPressed)
		return (true);
	return (false);
}

bool Window::getEventTextEntered(void) const
{
	if (_event.type == sf::Event::TextEntered)
		return (true);
	return (false);
}

char Window::getUnicode(void) const
{
	return (_event.text.unicode);
}

void Window::drawRectangle(RectangleSfml rect)
{
	_window.draw(rect.getRect());
}

void Window::drawText(Text text)
{
	sf::Font font;
	font.loadFromFile("../../src/Fonts/SupersonicRocketship.ttf");
	text._text.setFont(font);
	_window.draw(text._text);
}