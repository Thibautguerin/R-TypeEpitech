/*
** EPITECH PROJECT, 2019
** SFMLWindow.hpp
** File description:
** window in sfml
*/

#ifndef SFMLWINDOW_HPP
#define SFMLWINDOW_HPP

#include <SFML/Graphics.hpp>
#include "../../Interfaces/IWindow.hpp"

class Window : public IWindow
{
	public:
		Window(size_t width, size_t height, std::string name);
		~Window(void) override;
		size_t getWidth(void) const override;
		size_t getHeight(void) const override;
		bool isOpen(void) const override;
		void clear(int r, int g, int b) override;
		void display(void) override;
		void close(void) override;
		bool pollEvent(void) override;
		bool getEventClose(void) const override;
		bool getEventKeyPressed(void) const override;
		bool getEventKeyEscape(void) const override;
		bool getEventKeyReturn(void) const override;
		bool getEventMouseButtonPressed(void) const override;
		bool getEventTextEntered(void) const override;
		char getUnicode(void) const override;
		void drawRectangle(RectangleSfml rect) override;
		void drawText(Text text) override;

		sf::RenderWindow _window;
	private:
		sf::Event _event;
};

#endif