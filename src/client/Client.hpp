/*
** EPITECH PROJECT, 2019
** Client.hpp
** File description:
** client for rtype
*/

#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <iostream>
#include <string>
#include <boost/array.hpp>
#include <boost/asio.hpp>

#include "SFML/Window/SFMLWindow.hpp"

#include "Connection.hpp"
#include "Lobbies.hpp"
#include "DisplayLobby.hpp"

#include "../DataToVector.hpp"
#include "../VectorToData.hpp"

class Client
{
	public:
		Client(boost::asio::io_service &io_service);
		~Client(void);
		void setEndPoint(std::string address, int port);
		void recieve(void);
		void interpreter(Window *window);
		void send(std::vector<std::string> to_send);
		void signal_callback_handler(void);
		boost::array<char, 1000> getRecv(void);
		void setPseudo(std::string pseudo);
		std::string getPseudo(void) const;

	private:
		boost::asio::ip::udp::socket _socket;
		boost::asio::ip::udp::endpoint _endpoint;
		boost::array<char, 1000> _recv;
		std::string _pseudo;
};

#endif