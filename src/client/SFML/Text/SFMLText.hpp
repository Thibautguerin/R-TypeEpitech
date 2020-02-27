/*
** EPITECH PROJECT, 2019
** SFMLText.hpp
** File description:
** text in sfml
*/

#ifndef SFMLTEXT_HPP
#define SFMLTEXT_HPP

#include <SFML/Graphics.hpp>
#include "../../Interfaces/IText.hpp"

class Text : public IText
{
	public:
		Text(void);
		~Text(void) override;
		float getWidth(void) override;
		float getHeight(void) override;
		size_t getPosX(void) const override;
		size_t getPosY(void) const override;
		void setString(std::string str) override;
		void setPosition(size_t x, size_t y) override;
		void setFontSize(size_t size) override;
		void setFontColor(size_t r, size_t g, size_t b) override;
		sf::Text _text;
};

#endif