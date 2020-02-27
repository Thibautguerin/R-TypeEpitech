/*
** EPITECH PROJECT, 2019
** Player.hpp
** File description:
** player class
*/

#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <string>
#include <iostream>
#include <boost/asio.hpp>
#include <boost/array.hpp>

class Player
{
	public:
		Player(std::string name, boost::asio::ip::udp::endpoint endpoint);
		~Player(void);
		std::string getName(void) const;
		void setName(std::string name);
		boost::asio::ip::udp::endpoint getEndpoint(void) const;
		boost::asio::ip::address getAddress(void) const;
		unsigned short getPort(void) const;
		bool getReady(void) const;
		void toggleReady(void);
	private:
		std::string _name;
		boost::asio::ip::udp::endpoint _endpoint;
		bool _ready = false;
};

#endif