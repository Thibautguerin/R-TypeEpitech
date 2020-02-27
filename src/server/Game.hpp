/*
** EPITECH PROJECT, 2019
** Game.hpp
** File description:
** game for rtype
*/

#ifndef GAME_HPP
#define GAME_HPP

#include <string>
#include <iostream>
#include <vector>
#include <thread>

class Game
{
	public:
		Game(void);
		~Game(void);
	private:
		std::vector<std::string> _datas;
		std::thread _game;
};

#endif