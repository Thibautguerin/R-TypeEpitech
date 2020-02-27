/*
** EPITECH PROJECT, 2019
** IRectangle.hpp
** File description:
** interface for rectangle
*/

#ifndef IRECTANGLE_HPP
#define IRECTANGLE_HPP

#include <string>
#include <vector>

class IRectangle
{
	public:
		virtual ~IRectangle(void) = default;
		virtual size_t getWidth(void) const = 0;
		virtual size_t getHeight(void) const = 0;
		virtual size_t getPosX(void) const = 0;
		virtual size_t getPosY(void) const = 0;
		virtual void setColor(size_t r, size_t g, size_t b) = 0;
		virtual void setPosition(size_t x, size_t y) = 0;
		virtual void setSize(size_t width, size_t height) = 0;
		virtual bool getGlobalBounds(size_t mouse_x, size_t mouse_y) const = 0;
};

#endif