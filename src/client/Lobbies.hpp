/*
** EPITECH PROJECT, 2019
** Lobbies.hpp
** File description:
** list of lobbies
*/

#ifndef LOBBIES_HPP
#define LOBBIES_HPP

#include <iostream>
#include <string>
#include "../Lobby.hpp"

#include "SFML/Window/SFMLWindow.hpp"
#include "SFML/Rectangle/SFMLRectangle.hpp"
#include "SFML/Text/SFMLText.hpp"

class Lobbies
{
	public:
		Lobbies(Window *window);
		~Lobbies(void);
		void display(Window *window, std::vector<std::string> datas);
		void nameOnClick(Window *window);
		void nbPlayerOnClick(Window *window);
		void createOnClick(Window *window);
		void join(Window *window, std::string name, int nb_player, int limit_player);
		void setError(bool error);
		
		RectangleSfml _nameCase;
		RectangleSfml _nbPlayerCase;
		RectangleSfml _createCase;
	private:
		std::vector<Lobby> _lobbies;
		std::string _name;
		std::string _nbPlayer;
		Text _nameDisplay;
		Text _nbPlayerDisplay;
		Text _createDisplay;
		Text _title;
		std::string _errorMsg;
		bool _error;
};

#endif