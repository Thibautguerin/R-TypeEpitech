/*
** EPITECH PROJECT, 2019
** Lobby.hpp
** File description:
** lobby class
*/

#ifndef LOBBY_HPP
#define LOBBY_HPP

#include <string>
#include <iostream>
#include <boost/array.hpp>

#include "Player.hpp"

class Lobby
{
	public:
		Lobby(std::string name, int player_limit);
		~Lobby(void);
		bool allReady(void) const;
		void addPlayer(Player player);
		void removePlayer(std::string name);
		Player getPlayer(int i) const;
		int getNbPlayer(void) const;
		int getPlayerLimit(void) const;
		void setPlayerLimit(int player_limit);
		std::string getName(void) const;
		void setName(std::string name);
		void toggleReady(int i);
	private:
		std::string _name;
		int _player_limit;
		std::vector<Player> _players;
};

#endif