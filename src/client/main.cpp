/*
** EPITECH PROJECT, 2019
** main.cpp
** File description:
** main client
*/

#include "Client.hpp"
#include "Global.hpp"

boost::asio::io_service io_service;
Client client(io_service);

void signal_callback(int signum)
{
	client.signal_callback_handler();
}

void gameLoop(Window *window)
{
	signal(SIGINT, signal_callback);
	std::vector<std::string> stop;
	stop.push_back("STOP");

	std::vector<std::string> quit;
	quit.push_back("QUIT");

	while (window->isOpen()) {

		client.recieve();

		while (window->pollEvent()) {
			if (window->getEventClose()) {
				window->close();
				client.send(quit);
				client.recieve();
				client.send(stop);
				exit(0);
			}
			if (window->getEventKeyPressed()) {
				if (window->getEventKeyEscape()) {
					client.send(quit);
					client.recieve();
					throw (0);
				}
			}
		}

		client.interpreter(window);

		std::vector<std::string> datas = dataToVector(client.getRecv());
		
		window->clear(55, 79, 99);
		window->display();
	}
}

void lobby(Window *window)
{
	signal(SIGINT, signal_callback);
	std::vector<std::string> stop;
	stop.push_back("STOP");

	std::vector<std::string> quit;
	quit.push_back("QUIT");

	DisplayLobby displayLobby(window);

	try {
		while (window->isOpen()) {

			client.recieve();

			std::vector<std::string> datas = dataToVector(client.getRecv());

			if (datas.size() == 2 && datas[0].compare("CREATE") == 0 && datas[1].compare("ko") == 0)
				return;

			while (window->pollEvent()) {
				if (window->getEventClose()) {
					window->close();
					client.send(quit);
					client.recieve();
					client.send(stop);
					exit(0);
				}
				if (window->getEventKeyPressed()) {
					if (window->getEventKeyEscape()) {
						client.send(quit);
						client.recieve();
						return;
					}
				}
				if (window->getEventMouseButtonPressed()) {
					sf::Vector2i mousePos = sf::Mouse::getPosition(window->_window);
					if (displayLobby._readyCase.getGlobalBounds(mousePos.x, mousePos.y)) {
						std::vector<std::string> datas = dataToVector(client.getRecv());
						displayLobby.toggleReady(datas);
					}
				}
			}

			client.interpreter(window);

			displayLobby.display(window, datas);
			window->display();
		}
	} catch (int code) {
		return;
	}
}

void menu(Window *window)
{
	signal(SIGINT, signal_callback);
	std::vector<std::string> stop;
	stop.push_back("STOP");

	Lobbies lobbies(window);

	while (window->isOpen()) {

		client.recieve();
		std::vector<std::string> datas = dataToVector(client.getRecv());

		window->clear(55, 79, 99);

		std::vector<RectangleSfml> joinCases;

		RectangleSfml joinCase(250, 60);
		Text join;
		int x = -105;
		join.setFontSize(50);
		join.setFontColor(0, 0, 0);
		join.setString("Rejoindre");
		for (int i = 1; i < datas.size(); i++) {
			joinCase.setPosition(window->getWidth() / 2 - joinCase.getWidth() / 2 + 380, window->getHeight() / 2 - joinCase.getHeight() + x);
			join.setPosition(window->getWidth() / 2 - join.getWidth() / 2 + 380, window->getHeight() / 2 - join.getHeight() + x - 10);
			window->drawRectangle(joinCase);
			window->drawText(join);
			x = x + 70;
			joinCases.push_back(joinCase);
		}

		while (window->pollEvent()) {
			if (window->getEventClose()) {
				window->close();
				client.send(stop);
				exit(0);
			}
			if (window->getEventKeyPressed()) {
				if (window->getEventKeyEscape()) {
					client.send(stop);
					return;
				}
			}
			if (window->getEventMouseButtonPressed()) {
				sf::Vector2i mousePos = sf::Mouse::getPosition(window->_window);
				if (lobbies._nameCase.getGlobalBounds(mousePos.x, mousePos.y))
					lobbies.nameOnClick(window);
				if (lobbies._nbPlayerCase.getGlobalBounds(mousePos.x, mousePos.y))
					lobbies.nbPlayerOnClick(window);
				if (lobbies._createCase.getGlobalBounds(mousePos.x, mousePos.y))
					lobbies.createOnClick(window);
				for (int i = 0; i < joinCases.size(); i++) {
					if (joinCases[i].getGlobalBounds(mousePos.x, mousePos.y)) {
						std::vector<std::string> tmp;
						boost::split(tmp, datas[i + 1], boost::is_any_of(";"));
						lobbies.join(window, tmp[0], std::stoi(tmp[1]), std::stoi(tmp[2]));
					}

				}
			}
		}

		client.interpreter(window);

		lobbies.display(window, datas);
		window->display();
	}
}

int main()
{
	signal(SIGINT, signal_callback);
		
	Window window(1920, 1080, "R-Type");
	
	Connection connection(&window);

	while (window.isOpen()) {

		connection.display(&window);
		window.display();
		
		while (window.pollEvent()) {

			if (window.getEventClose()) {
				window.close();
				exit(0);
			}
			if (window.getEventKeyPressed()) {
				if (window.getEventKeyEscape()) {
					window.close();
					exit(0);
				}
			}
			if (window.getEventMouseButtonPressed()) {
				sf::Vector2i mousePos = sf::Mouse::getPosition(window._window);
				if (connection._addressCase.getGlobalBounds(mousePos.x, mousePos.y))
					connection.addressOnClick(&window);
				if (connection._portCase.getGlobalBounds(mousePos.x, mousePos.y))
					connection.portOnClick(&window);
				if (connection._pseudoCase.getGlobalBounds(mousePos.x, mousePos.y))
					connection.pseudoOnClick(&window);
				if (connection._buttonCase.getGlobalBounds(mousePos.x, mousePos.y))
					connection.tryConnection(&window);
			}
		}
	}
    return (0);
}