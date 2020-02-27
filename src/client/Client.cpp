/*
** EPITECH PROJECT, 2019
** Client.cpp
** File description:
** client for rtype
*/

#include "Client.hpp"
#include "Global.hpp"

Client::Client(boost::asio::io_service &io_service):
_socket(io_service)
{
	_socket.open(boost::asio::ip::udp::v4());
}

Client::~Client(void)
{
}

void Client::setEndPoint(std::string address, int port)
{
	boost::asio::ip::udp::endpoint test(boost::asio::ip::address::from_string(address), port);
	_endpoint = test;
	_socket.connect(_endpoint);
}

void Client::recieve(void)
{
	boost::asio::ip::udp::endpoint sender_endpoint;
	boost::array<char, 1000> empty;
	_recv = empty;
	size_t len = _socket.receive_from(boost::asio::buffer(_recv), sender_endpoint);
	// std::cout << _recv.data() << std::endl;
}

void Client::interpreter(Window *window)
{
	std::vector<std::string> cmd = dataToVector(_recv);
	std::vector<std::string> to_send;

	// for (int i = 0; i < cmd.size(); i++)
	// 	std::cout << cmd[i] << " ";
	// std::cout << std::endl;
	if (cmd[0].compare("CONNECT") == 0 && cmd.size() == 2) {
		if (cmd[1].compare("ok") == 0) {
			std::cout << "Vous êtes bien connecté au serveur!" << std::endl;
			to_send.push_back("MENU");
			Client::send(to_send);	
		} else if (cmd[1].compare("ko") == 0) {
			std::cout << "Le pseudo est déjà pris!" << std::endl;
			throw (0);
		} else if (cmd[1].compare("ko1") == 0) {
			std::cout << "Une session est déjà ouverte sur ce pc!" << std::endl;
			throw (1);
		}

	} else if (cmd[0].compare("STOP") == 0) {
		std::cout << "Le serveur est fermé!" << std::endl;
	} else if (cmd[0].compare("MENU") == 0) {
		to_send.push_back("MENU");
		Client::send(to_send);
	} else if (cmd[0].compare("LOBBY") == 0) {
		to_send.push_back("LOBBY");
		to_send.push_back(cmd[1]);
		Client::send(to_send);
	} else if (cmd[0].compare("CREATE") == 0 && cmd[1].compare("ko") == 0) {
		to_send.push_back("MENU");
		Client::send(to_send);
	} else if (cmd[0].compare("STARTGAME") == 0) {
		to_send.push_back("GAME");
		to_send.push_back(cmd[1]);
		Client::send(to_send);
		gameLoop(window);
	} else if (cmd[0].compare("GAME") == 0) {
		to_send.push_back("GAME");
		to_send.push_back(cmd[1]);
		Client::send(to_send);
	} else {
		to_send.push_back("CONNECT");
		Client::send(to_send);
	}
}

void Client::send(std::vector<std::string> to_send)
{
	boost::array<char, 1000> msg = vectorToData(to_send);

	// std::cout << "send: " << msg.data() << std::endl;

	boost::system::error_code error;
	_socket.send_to(boost::asio::buffer(msg), _endpoint, 0, error);
}

boost::array<char, 1000> Client::getRecv(void)
{
	return (_recv);
}

void Client::setPseudo(std::string pseudo)
{
	_pseudo = pseudo;
}

std::string Client::getPseudo(void) const
{
	return (_pseudo);
}

void Client::signal_callback_handler(void)
{
	std::vector<std::string> stop;
	stop.push_back("STOP");
	std::vector<std::string> quit;
	quit.push_back("QUIT");
	Client::send(quit);
	Client::recieve();
	Client::send(stop);
	exit(0);
}