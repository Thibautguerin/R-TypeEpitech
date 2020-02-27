/*
** EPITECH PROJECT, 2019
** IText.hpp
** File description:
** interface for text
*/

#ifndef ITEXT_HPP
#define ITEXT_HPP

#include <string>
#include <vector>

class IText
{
	public:
		virtual ~IText(void) = default;
		virtual float getWidth(void) = 0;
		virtual float getHeight(void) = 0;
		virtual size_t getPosX(void) const = 0;
		virtual size_t getPosY(void) const = 0;
		virtual void setString(std::string str) = 0;
		virtual void setPosition(size_t x, size_t y) = 0;
		virtual void setFontSize(size_t size) = 0;
		virtual void setFontColor(size_t r, size_t g, size_t b) = 0;
};

#endif