/*
** EPITECH PROJECT, 2019
** Server.hpp
** File description:
** server for rtype
*/

#ifndef SERVER_HPP
#define SERVER_HPP

#include <string>
#include <iostream>
#include <boost/asio.hpp>
#include <boost/array.hpp>

#include "../Player.hpp"
#include "../Lobby.hpp"
#include "Game.hpp"
#include "../VectorToData.hpp"
#include "../DataToVector.hpp"

class Server
{
	public:
		Server(boost::asio::io_service &io_service);
		~Server(void);
		// void debugModeLobbies(void);
		void receive(void);
		void interpreter(void);
		void send(std::vector<std::string> to_send);
		void displayClientList(void) const;
		void signal_callback_handler(void);
		bool getPlayerExist(boost::asio::ip::udp::endpoint address) const;
		bool pseudoExist(std::string pseudo) const;
		bool getLobbyExist(std::string name) const;
		int getLobbyPos(std::string name) const;
		Lobby getLobby(std::string name) const;
		Player getPlayer(void) const;
		void quitLobby(void);
		bool lobbyIsReady(std::string name) const;

	private:
		boost::asio::ip::udp::socket _socket;
	    boost::asio::ip::udp::endpoint _endpoint;
	    boost::array<char, 1000> _recv;
	    std::vector<Player> _players;
	    std::vector<Lobby> _lobbies;
	    std::vector<Game> _games;
};

#endif