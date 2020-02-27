/*
** EPITECH PROJECT, 2019
** Server.cpp
** File description:
** server for rtype
*/

#include "Server.hpp"

Server::Server(boost::asio::io_service &io_service) try:
_socket(io_service, boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), 1234))
{} catch (std::exception &e) {
	std::cerr << e.what() << std::endl;
	exit(0);
}

Server::~Server(void)
{}

// void Server::debugModeLobbies(void)
// {
// 	Lobby new_lobby("TTESTTTTTTTT", 2);
// 	boost::asio::ip::udp::endpoint testend;
// 	Player test("Mario", testend);
// 	test.toggleReady();
// 	new_lobby.addPlayer(test);
// 	_lobbies.push_back(new_lobby);
// }

void Server::receive(void)
{
	boost::system::error_code error;
	boost::array<char, 1000> empty = {""};
	_recv = empty;
	size_t len = _socket.receive_from(boost::asio::buffer(_recv), _endpoint, 0, error);

	// std::cout << _recv.data() << std::endl;

	if (error && error != boost::asio::error::message_size)
		throw boost::system::system_error(error);
}

void Server::interpreter(void)
{
	std::vector<std::string> cmd = dataToVector(_recv);
	std::vector<std::string> to_send;

	if (cmd[0].compare("CONNECT") == 0) {
		if (Server::getPlayerExist(_endpoint)) {
			to_send.push_back("CONNECT");
			to_send.push_back("ko1");
			Server::send(to_send);
		} else {
			if (Server::pseudoExist(cmd[1])) {
				to_send.push_back("CONNECT");
				to_send.push_back("ko");
				Server::send(to_send);
				return;
			}
			std::cout << cmd[1] << " s'est connecté! [" << _endpoint << "]\n" << std::endl;
			
			Player player(cmd[1], _endpoint);
			_players.push_back(player);

			displayClientList();
			to_send.push_back("CONNECT");
			to_send.push_back("ok");
			Server::send(to_send);
		}
	} else if (cmd[0].compare("STOP") == 0) {
		for (int i = 0; i < _players.size(); i++) {
			if (_endpoint.port() == _players[i].getPort() && _endpoint.address() == _players[i].getAddress()) {
				_players.erase(_players.begin() + i);
				std::cout << _players[i].getName() << " s'est déconnecté! [" << _endpoint << "]\n" << std::endl;
				displayClientList();
			}
		}
	} else if (cmd[0].compare("MENU") == 0) {
		to_send.push_back("MENU");
		for (int i = 0; i < _lobbies.size(); i++)
			to_send.push_back(_lobbies[i].getName() + ";" + std::to_string(_lobbies[i].getNbPlayer()) + ";" + std::to_string(_lobbies[i].getPlayerLimit()));
		Server::send(to_send);
	} else if (cmd[0].compare("CREATE") == 0) {
		if (!Server::getLobbyExist(cmd[1])) {
			Lobby new_lobby(cmd[1], std::stoi(cmd[2]));
			new_lobby.addPlayer(Server::getPlayer());
			_lobbies.push_back(new_lobby);

			to_send.push_back("LOBBY");
			to_send.push_back(Server::getLobby(cmd[1]).getName());
			to_send.push_back(std::to_string(Server::getLobby(cmd[1]).getNbPlayer()));
			to_send.push_back(std::to_string(Server::getLobby(cmd[1]).getPlayerLimit()));
			for (int i = 0; i < Server::getLobby(cmd[1]).getNbPlayer(); i++)
				to_send.push_back(Server::getLobby(cmd[1]).getPlayer(i).getName() + ";" + std::to_string(Server::getLobby(cmd[1]).getPlayer(i).getReady()));
			Server::send(to_send);
			std::cout << "Création du lobby " << cmd[1] << " par " << Server::getPlayer().getName() << "!\n" << std::endl;
			displayClientList();
		} else {
			to_send.push_back("CREATE");
			to_send.push_back("ko");
			Server::send(to_send);
		}
	} else if (cmd[0].compare("JOIN") == 0) {
		if (Server::getLobbyExist(cmd[1])) {
			_lobbies[Server::getLobbyPos(cmd[1])].addPlayer(Server::getPlayer());

			to_send.push_back("LOBBY");
			to_send.push_back(Server::getLobby(cmd[1]).getName());
			to_send.push_back(std::to_string(Server::getLobby(cmd[1]).getNbPlayer()));
			to_send.push_back(std::to_string(Server::getLobby(cmd[1]).getPlayerLimit()));
			for (int i = 0; i < Server::getLobby(cmd[1]).getNbPlayer(); i++)
				to_send.push_back(Server::getLobby(cmd[1]).getPlayer(i).getName() + ";" + std::to_string(Server::getLobby(cmd[1]).getPlayer(i).getReady()));
			Server::send(to_send);
			std::cout << Server::getPlayer().getName() << " a rejoint le lobby " << cmd[1] << "!\n" << std::endl;
			displayClientList();
		} else {
			to_send.push_back("JOIN");
			to_send.push_back("ko");
			Server::send(to_send);
		}
	} else if (cmd[0].compare("QUIT") == 0) {
		Server::quitLobby();

		to_send.push_back("MENU");
		for (int i = 0; i < _lobbies.size(); i++)
			to_send.push_back(_lobbies[i].getName() + ";" + std::to_string(_lobbies[i].getNbPlayer()) + ";" + std::to_string(_lobbies[i].getPlayerLimit()));
		Server::send(to_send);
	} else if (cmd[0].compare("LOBBY") == 0) {
		if (Server::lobbyIsReady(cmd[1])) {
			// start new game -> new thread
			to_send.push_back("STARTGAME");
			to_send.push_back(cmd[1]);
		} else {
			to_send.push_back("LOBBY");

			to_send.push_back(Server::getLobby(cmd[1]).getName());
			to_send.push_back(std::to_string(Server::getLobby(cmd[1]).getNbPlayer()));
			to_send.push_back(std::to_string(Server::getLobby(cmd[1]).getPlayerLimit()));
			for (int i = 0; i < Server::getLobby(cmd[1]).getNbPlayer(); i++)
				to_send.push_back(Server::getLobby(cmd[1]).getPlayer(i).getName() + ";" + std::to_string(Server::getLobby(cmd[1]).getPlayer(i).getReady()));
		}
		Server::send(to_send);
	} else if (cmd[0].compare("READY") == 0) {
		for (int i = 0; i < Server::getLobby(cmd[1]).getNbPlayer(); i++) {
			if (Server::getLobby(cmd[1]).getPlayer(i).getEndpoint() == _endpoint)
				_lobbies[Server::getLobbyPos(cmd[1])].toggleReady(i);
		}
		to_send.push_back("LOBBY");

		to_send.push_back(Server::getLobby(cmd[1]).getName());
		to_send.push_back(std::to_string(Server::getLobby(cmd[1]).getNbPlayer()));
		to_send.push_back(std::to_string(Server::getLobby(cmd[1]).getPlayerLimit()));
		for (int i = 0; i < Server::getLobby(cmd[1]).getNbPlayer(); i++)
			to_send.push_back(Server::getLobby(cmd[1]).getPlayer(i).getName() + ";" + std::to_string(Server::getLobby(cmd[1]).getPlayer(i).getReady()));
		Server::send(to_send);
	} else if (cmd[0].compare("GAME") == 0) {
		to_send.push_back("GAME");
		to_send.push_back(cmd[1]);
		Server::send(to_send);
	} else {
		to_send.push_back("CONNECT");
		Server::send(to_send);
	}
}

void Server::send(std::vector<std::string> to_send)
{
	// std::cout << "enter in send" << std::endl;
	boost::array<char, 1000> msg = vectorToData(to_send);

	// std::cout << "send: " << msg.data() << std::endl;

	boost::system::error_code error;
	if (strcmp(msg.data(), "STOP") == 0) {
		for (std::vector<int>::size_type i = 0; i < (_players).size(); i = i + 1)
			_socket.send_to(boost::asio::buffer(msg), _players[i].getEndpoint(), 0, error);
	} else
		_socket.send_to(boost::asio::buffer(msg), _endpoint, 0, error);
}

void Server::displayClientList(void) const
{
	std::cout << "##############################" << std::endl;
	std::cout << "#      Clients connectés      " << std::endl;
	std::cout << "##############################" << std::endl;

	if ((_players).size() == 0)
		std::cout << "## Aucun Clients!    " << std::endl;
	else {
		for (std::vector<int>::size_type i = 0; i < (_players).size(); i = i + 1)
			std::cout << "## " << _players[i].getName() << " [" << _players[i].getAddress() << "]" << std::endl;
	}
	std::cout << "##############################\n" << std::endl;

	std::cout << "##############################" << std::endl;
	std::cout << "#           Lobbies           " << std::endl;
	std::cout << "##############################" << std::endl;
	if ((_lobbies).size() == 0)
		std::cout << "## Aucun Lobbies!    " << std::endl;
	else {
		for (int i = 0; i < _lobbies.size(); i++) {
			std::cout << "## " << _lobbies[i].getName() << std::endl;
			for (std::vector<int>::size_type j = 0; j < _lobbies[i].getNbPlayer(); j++)
				std::cout << "### " << _lobbies[i].getPlayer(j).getName() << std::endl;
		}
	}
	std::cout << "##############################\n" << std::endl;
}

bool Server::getPlayerExist(boost::asio::ip::udp::endpoint address) const
{
	for (std::vector<int>::size_type i = 0; i < (_players).size(); i = i + 1) {
		if (_players[i].getAddress() == address.address())
			return (true);
	}
	return (false);
}

bool Server::pseudoExist(std::string pseudo) const
{
	for (std::vector<int>::size_type i = 0; i < (_players).size(); i = i + 1) {
		if (_players[i].getName() == pseudo)
			return (true);
	}
	return (false);
}

bool Server::getLobbyExist(std::string name) const
{
	for (std::vector<int>::size_type i = 0; i < (_lobbies).size(); i = i + 1) {
		if (_lobbies[i].getName() == name)
			return (true);
	}
	return (false);
}

int Server::getLobbyPos(std::string name) const
{
	for (std::vector<int>::size_type i = 0; i < (_lobbies).size(); i = i + 1) {
		if (_lobbies[i].getName() == name)
			return (i);
	}
}

Lobby Server::getLobby(std::string name) const
{
	for (std::vector<int>::size_type i = 0; i < (_lobbies).size(); i = i + 1) {
		if (_lobbies[i].getName() == name)
			return (_lobbies[i]);
	}
}

Player Server::getPlayer(void) const
{
	for (std::vector<int>::size_type i = 0; i < (_players).size(); i = i + 1) {
		if (_players[i].getEndpoint() == _endpoint)
			return (_players[i]);
	}
}

void Server::quitLobby(void)
{
	for (int i = 0; i < _lobbies.size(); i++) {
		for (int j = 0; j < _lobbies[i].getNbPlayer(); j++) {
			if (_lobbies[i].getPlayer(j).getEndpoint() == _endpoint) {
				std::cout << Server::getPlayer().getName() << " a quitté le lobby " << _lobbies[i].getName() << "!\n" << std::endl;
				_lobbies[i].removePlayer(_lobbies[i].getPlayer(j).getName());
				displayClientList();
			}
		}
	}
	for (int i = 0; i < _lobbies.size(); i++) {
		if (_lobbies[i].getNbPlayer() == 0) {
			std::cout << "Le lobby " << _lobbies[i].getName() << " a été supprimé car il n'y a plus aucun joueur!\n" << std::endl;
			_lobbies.erase(_lobbies.begin() + i);
		}
	}
}

bool Server::lobbyIsReady(std::string name) const
{
	if (Server::getLobby(name).getPlayerLimit() > 1 && Server::getLobby(name).getNbPlayer() == 1)
		return (false);
	for (int i = 0; i < Server::getLobby(name).getNbPlayer(); i++) {
		if (Server::getLobby(name).getPlayer(i).getReady() == false)
			return (false);
	}
	return (true);
}

void Server::signal_callback_handler(void)
{
	std::vector<std::string> to_send;
	to_send.push_back("STOP");
	Server::send(to_send);
	exit(0);
}