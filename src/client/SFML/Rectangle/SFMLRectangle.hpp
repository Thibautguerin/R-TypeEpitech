/*
** EPITECH PROJECT, 2019
** SFMLRectangle.hpp
** File description:
** rectangle in sfml
*/

#ifndef SFMLRECTANGLE_HPP
#define SFMLRECTANGLE_HPP

#include <SFML/Graphics.hpp>
#include "../../Interfaces/IRectangle.hpp"

class RectangleSfml : public IRectangle
{
	public:
		RectangleSfml(size_t width, size_t height);
		~RectangleSfml(void) override;
		size_t getWidth(void) const override;
		size_t getHeight(void) const override;
		size_t getPosX(void) const override;
		size_t getPosY(void) const override;
		void setColor(size_t r, size_t g, size_t b) override;
		void setPosition(size_t x, size_t y) override;
		void setSize(size_t width, size_t height) override;
		bool getGlobalBounds(size_t mouse_x, size_t mouse_y) const override;
		sf::RectangleShape getRect(void);

	private:
		sf::RectangleShape _rect;
};

#endif