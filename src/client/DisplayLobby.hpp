/*
** EPITECH PROJECT, 2019
** DisplayLobby.hpp
** File description:
** display the lobby
*/

#ifndef DISPLAYLOBBY_HPP
#define DISPLAYLOBBY_HPP

#include <iostream>
#include <string>

#include "SFML/Window/SFMLWindow.hpp"
#include "SFML/Rectangle/SFMLRectangle.hpp"
#include "SFML/Text/SFMLText.hpp"

class DisplayLobby
{
	public:
		DisplayLobby(Window *window);
		~DisplayLobby(void);
		void display(Window *window, std::vector<std::string> datas);
		void toggleReady(std::vector<std::string> datas);
		
		RectangleSfml _readyCase;
	private:
		Text _readyDisplay;
		Text _title;
};

#endif