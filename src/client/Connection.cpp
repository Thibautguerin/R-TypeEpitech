/*
** EPITECH PROJECT, 2019
** Connection.cpp
** File description:
** class for connection
*/

#include "Connection.hpp"
#include "Global.hpp"

Connection::Connection(Window *window):
_addressCase(400, 80),
_portCase(180, 80),
_pseudoCase(400, 80),
_buttonCase(350, 80)
{
	_address = "127.0.0.1";
	_port = "1234";
	_addressDisplay.setString(_address);
	_portDisplay.setString(_port);

	_addressCase.setPosition(int(window->getWidth() / 2 - 320), int(window->getHeight() / 2 - _addressCase.getHeight() / 2));
	_portCase.setPosition(int(window->getWidth() / 2 + 140), int(window->getHeight() / 2 - _portCase.getHeight() / 2));
	_pseudoCase.setPosition(int(window->getWidth() / 2 - 200), int(window->getHeight() / 2 - _pseudoCase.getHeight() / 2 - 110));
	_buttonCase.setPosition(int(window->getWidth() / 2 - 175), int(window->getHeight() / 2 - _buttonCase.getHeight() / 2 + 110));

	_pseudoDisplay.setFontSize(50);
	_pseudoDisplay.setFontColor(0, 0, 0);
	_pseudoDisplay.setPosition(_pseudoCase.getPosX(), _pseudoCase.getPosY());

	_addressDisplay.setFontSize(50);
	_addressDisplay.setFontColor(0, 0, 0);
	_addressDisplay.setPosition(_addressCase.getPosX(), _addressCase.getPosY());

	_portDisplay.setFontSize(50);
	_portDisplay.setFontColor(0, 0, 0);
	_portDisplay.setPosition(_portCase.getPosX(), _portCase.getPosY());
	
	_buttonDisplay.setFontSize(50);
	_buttonDisplay.setFontColor(0, 0, 0);
	_buttonDisplay.setPosition(_buttonCase.getPosX(), _buttonCase.getPosY());
	_buttonDisplay.setString("Se Connecter");

	_title.setFontSize(100);
	_title.setString("R-Type");
	_title.setFontColor(0, 0, 0);
	_title.setPosition(window->getWidth() / 2 - _title.getWidth() / 2, window->getHeight() / 4 - _title.getHeight());
	_error = false;
}

Connection::~Connection(void)
{}

void Connection::display(Window *window)
{
	window->clear(55, 79, 99);

	if (_pseudo.size() == 0)
		_pseudoDisplay.setString("Pseudo");
	if (_address.size() == 0)
		_addressDisplay.setString("Adresse");
	if (_port.size() == 0)
		_portDisplay.setString("Port");
	window->drawText(_title);
	window->drawRectangle(_pseudoCase);
	window->drawText(_pseudoDisplay);
	window->drawRectangle(_addressCase);
	window->drawText(_addressDisplay);
	window->drawRectangle(_portCase);
	window->drawText(_portDisplay);
	window->drawRectangle(_buttonCase);
	window->drawText(_buttonDisplay);

	if (_error == true) {
		Text error;
		error.setFontColor(255, 0, 0);
		error.setFontSize(30);
		error.setString(_errorMsg);
		error.setPosition(window->getWidth() / 2 - error.getWidth() / 2, window->getHeight() / 2 - error.getHeight() + 210);
		window->drawText(error);
	}
}

void Connection::pseudoOnClick(Window *window)
{
	_error = false;
	_pseudoCase.setColor(168, 168, 168);
	while (1) {
		while (window->pollEvent()) {

			if (window->getEventClose()) {
				window->close();
				exit(0);
			}
			if (window->getEventKeyPressed()) {
				if (window->getEventKeyEscape()) {
					window->close();
					exit(0);
				}
				if (window->getEventKeyReturn()) {
					_pseudoCase.setColor(255, 255, 255);
					return;
				}
			}
			if (window->getEventTextEntered()) {
				if (_pseudo.size() < 12 && (window->getUnicode() >= 33 && window->getUnicode() <= 126)) {
					_pseudo += window->getUnicode();
					_pseudoDisplay.setString(_pseudo);
				} else if (window->getUnicode() == 8 && _pseudo.size() > 0) {
					_pseudo.erase(_pseudo.size() - 1);
					_pseudoDisplay.setString(_pseudo);
				}

			}
			if (window->getEventMouseButtonPressed()) {
				sf::Vector2i mousePos = sf::Mouse::getPosition(window->_window);
				if (_portCase.getGlobalBounds(mousePos.x, mousePos.y)) {
					_pseudoCase.setColor(255, 255, 255);
					return (Connection::portOnClick(window));
				} else if (_addressCase.getGlobalBounds(mousePos.x, mousePos.y)) {
					_pseudoCase.setColor(255, 255, 255);
					return (Connection::addressOnClick(window));
				} else if (_buttonCase.getGlobalBounds(mousePos.x, mousePos.y)) {
					_pseudoCase.setColor(255, 255, 255);
					return (Connection::tryConnection(window));
				} else if (!_pseudoCase.getGlobalBounds(mousePos.x, mousePos.y)) {
					_pseudoCase.setColor(255, 255, 255);
					return;
				}
			}
		}
		Connection::display(window);
		window->display();
	}
}

void Connection::addressOnClick(Window *window)
{
	_error = false;
	_addressCase.setColor(168, 168, 168);
	while (1) {
		while (window->pollEvent()) {

			if (window->getEventClose()) {
				window->close();
				exit(0);
			}
			if (window->getEventKeyPressed()) {
				if (window->getEventKeyEscape()) {
					window->close();
					exit(0);
				}
				if (window->getEventKeyReturn()) {
					_addressCase.setColor(255, 255, 255);
					return;
				}
			}
			if (window->getEventTextEntered()) {
				if (_address.size() < 15 && ((window->getUnicode() >= 48 && window->getUnicode() <= 57) || window->getUnicode() == 46)) {
					_address += window->getUnicode();
					_addressDisplay.setString(_address);
				} else if (window->getUnicode() == 8 && _address.size() > 0) {
					_address.erase(_address.size() - 1);
					_addressDisplay.setString(_address);
				}

			}
			if (window->getEventMouseButtonPressed()) {
				sf::Vector2i mousePos = sf::Mouse::getPosition(window->_window);
				if (_portCase.getGlobalBounds(mousePos.x, mousePos.y)) {
					_addressCase.setColor(255, 255, 255);
					return (Connection::portOnClick(window));
				} else if (_pseudoCase.getGlobalBounds(mousePos.x, mousePos.y)) {
					_addressCase.setColor(255, 255, 255);
					return (Connection::pseudoOnClick(window));
				} else if (_buttonCase.getGlobalBounds(mousePos.x, mousePos.y)) {
					_addressCase.setColor(255, 255, 255);
					return (Connection::tryConnection(window));
				} else if (!_addressCase.getGlobalBounds(mousePos.x, mousePos.y)) {
					_addressCase.setColor(255, 255, 255);
					return;
				}
			}
		}
		Connection::display(window);
		window->display();
	}
}

void Connection::portOnClick(Window *window)
{
	_error = false;
	_portCase.setColor(168, 168, 168);
	while (1) {
		while (window->pollEvent()) {

			if (window->getEventClose()) {
				window->close();
				exit(0);
			}
			if (window->getEventKeyPressed()) {
				if (window->getEventKeyEscape()) {
					window->close();
					exit(0);
				}
				if (window->getEventKeyReturn()) {
					_portCase.setColor(255, 255, 255);
					return;
				}
			}
			if (window->getEventTextEntered()) {
				if (_port.size() < 6 && (window->getUnicode() >= 48 && window->getUnicode() <= 57)) {
					_port += window->getUnicode();
					_portDisplay.setString(_port);
				} else if (window->getUnicode() == 8 && _port.size() > 0) {
					_port.erase(_port.size() - 1);
					_portDisplay.setString(_port);
				}
			}
			if (window->getEventMouseButtonPressed()) {
				sf::Vector2i mousePos = sf::Mouse::getPosition(window->_window);
				if (_addressCase.getGlobalBounds(mousePos.x, mousePos.y)) {
					_portCase.setColor(255, 255, 255);
					return (Connection::addressOnClick(window));
				} else if (_pseudoCase.getGlobalBounds(mousePos.x, mousePos.y)) {
					_portCase.setColor(255, 255, 255);
					return (Connection::pseudoOnClick(window));
				} else if (_buttonCase.getGlobalBounds(mousePos.x, mousePos.y)) {
					_portCase.setColor(255, 255, 255);
					return (Connection::tryConnection(window));
				} else if (!_portCase.getGlobalBounds(mousePos.x, mousePos.y)) {
					_portCase.setColor(255, 255, 255);
					return;
				}
			}
		}
		Connection::display(window);
		window->display();
	}
}

void Connection::tryConnection(Window *window)
{
	_error = false;
	try {
		if (_pseudo.size() == 0) {
			_errorMsg = "Vous n'avez pas renseigner votre pseudo!";
			_error = true;
			return;
		}
		std::cout << "Connexion au serveur ..." << std::endl;
		client.setEndPoint(_address, std::stoi(_port));
		
		std::vector<std::string> msg;
		msg.push_back("CONNECT");
		msg.push_back(_pseudo);

		client.send(msg);
		client.recieve();
		client.interpreter(window);
		client.setPseudo(_pseudo);

		menu(window);

	} catch (int code) {
		if (code == 0) {
			std::cout << "Ce pseudo est deja pris!" << std::endl;
			_errorMsg = "Ce pseudo est deja pris!";
		}
		if (code == 1) {
			std::cout << "Vous ne pouvez pas lancer 2 clients sur le meme pc!" << std::endl;
			_errorMsg = "Vous ne pouvez pas lancer 2 clients sur le meme pc!";
		}
		_error = true;
	} catch (std::exception &e) {
		if (strcmp(e.what(), "receive_from: Connection refused") == 0)
    		std::cout << "Problème de connection avec le serveur!" << std::endl;
    	else
    		std::cerr << e.what() << std::endl;
    	_error = true;
    	_errorMsg = "Le serveur n'a pas ete trouve ou tous les champs n'ont pas ete correctement remplis!";
    }
}

void Connection::setError(bool error)
{
	_error = error;
}