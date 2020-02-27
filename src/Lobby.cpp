/*
** EPITECH PROJECT, 2019
** Lobby.cpp
** File description:
** lobby class
*/

#include "Lobby.hpp"

Lobby::Lobby(std::string name, int player_limit)
{
	_name = name;
	_player_limit = player_limit;
}

Lobby::~Lobby(void)
{}

bool Lobby::allReady(void) const
{
	for (int i = 0; i < _players.size(); i++) {
		if (!_players[i].getReady())
			return (false);
	}
	return (true);
}

void Lobby::addPlayer(Player player)
{
	_players.push_back(player);
}

void Lobby::removePlayer(std::string name)
{
	for (int i = 0; i < _players.size(); i++) {
		if (_players[i].getName().compare(name) == 0)
			_players.erase(_players.begin() + i);
	}
}

Player Lobby::getPlayer(int i) const
{
	return (_players[i]);
}

int Lobby::getNbPlayer(void) const
{
	return (_players.size());
}

int Lobby::getPlayerLimit(void) const
{
	return (_player_limit);
}

void Lobby::setPlayerLimit(int player_limit)
{
	_player_limit = player_limit;
}

std::string Lobby::getName(void) const
{
	return (_name);
}

void Lobby::setName(std::string name)
{
	_name = name;
}

void Lobby::toggleReady(int i)
{
	_players[i].toggleReady();
}