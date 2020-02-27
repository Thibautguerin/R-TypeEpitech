/*
** EPITECH PROJECT, 2019
** IWindow.hpp
** File description:
** interface for window
*/

#ifndef IWINDOW_HPP
#define IWINDOW_HPP

#include <cstddef>
#include <string>
#include <vector>

#include "../SFML/Text/SFMLText.hpp"
#include "../SFML/Rectangle/SFMLRectangle.hpp"

class IWindow
{
	public:
		virtual ~IWindow(void) = default;
		virtual size_t getWidth(void) const = 0;
		virtual size_t getHeight(void) const = 0;
		virtual bool isOpen(void) const = 0;
		virtual void clear(int r, int g, int b) = 0;
		virtual void display(void) = 0;
		virtual void close(void) = 0;
		virtual bool pollEvent(void) = 0;
		virtual bool getEventClose(void) const = 0;
		virtual bool getEventKeyPressed(void) const = 0;
		virtual bool getEventKeyEscape(void) const = 0;
		virtual bool getEventKeyReturn(void) const = 0;
		virtual bool getEventMouseButtonPressed(void) const = 0;
		virtual bool getEventTextEntered(void) const = 0;
		virtual char getUnicode(void) const = 0;
		virtual void drawRectangle(RectangleSfml rect) = 0;
		virtual void drawText(Text text) = 0;
};

#endif