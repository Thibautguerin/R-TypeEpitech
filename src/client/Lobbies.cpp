/*
** EPITECH PROJECT, 2019
** Lobbies.cpp
** File description:
** list of lobbies
*/

#include "Lobbies.hpp"
#include "Global.hpp"

Lobbies::Lobbies(Window *window):
_nameCase(400, 80),
_nbPlayerCase(300, 80),
_createCase(400, 80)
{
	_nbPlayer = "4";
	_nbPlayerDisplay.setString(_nbPlayer);

	_nameCase.setPosition(window->getWidth() / 2 - 580, window->getHeight() - window->getHeight() / 6 - _nameCase.getHeight() / 2);
	_nbPlayerCase.setPosition(window->getWidth() / 2 - 150, window->getHeight() - window->getHeight() / 6 - _nbPlayerCase.getHeight() / 2);
	_createCase.setPosition(window->getWidth() / 2 + 180, window->getHeight() - window->getHeight() / 6 - _createCase.getHeight() / 2);

	_nameDisplay.setFontSize(50);
	_nameDisplay.setFontColor(0, 0, 0);
	_nameDisplay.setPosition(_nameCase.getPosX(), _nameCase.getPosY());

	_nbPlayerDisplay.setFontSize(50);
	_nbPlayerDisplay.setFontColor(0, 0, 0);
	_nbPlayerDisplay.setPosition(_nbPlayerCase.getPosX(), _nbPlayerCase.getPosY());
	
	_createDisplay.setFontSize(50);
	_createDisplay.setFontColor(0, 0, 0);
	_createDisplay.setPosition(_createCase.getPosX(), _createCase.getPosY());
	_createDisplay.setString("Creer");

	_title.setFontSize(100);
	_title.setString("Lobbies");
	_title.setFontColor(0, 0, 0);
	_title.setPosition(window->getWidth() / 2 - _title.getWidth() / 2, window->getHeight() / 4 - _title.getHeight());
	
	_error = false;
}

Lobbies::~Lobbies(void)
{
}

void Lobbies::display(Window *window, std::vector<std::string> datas)
{
	if (_name.size() == 0)
		_nameDisplay.setString("Nom");
	if (_nbPlayer.size() == 0)
		_nbPlayerDisplay.setString("Nb joueur");
	window->drawText(_title);
	window->drawRectangle(_nameCase);
	window->drawText(_nameDisplay);
	window->drawRectangle(_nbPlayerCase);
	window->drawText(_nbPlayerDisplay);
	window->drawRectangle(_createCase);
	window->drawText(_createDisplay);

	if (_error == true) {
		Text error;
		error.setFontSize(30);
		error.setFontColor(255, 0, 0);
		error.setString(_errorMsg);
		error.setPosition(window->getWidth() / 2 - error.getWidth() / 2, window->getHeight() / 2 - error.getHeight() + 210);
		window->drawText(error);
	}

	Text l;
	std::vector<std::string> tmp;
	int x = -105;
	l.setFontSize(50);
	l.setFontColor(0, 0, 0);
	for (int i = 1; i < datas.size() ; i++) {
		boost::split(tmp, datas[i], boost::is_any_of(";"));
		l.setString(tmp[0] + " [" + tmp[1] + "/" + tmp[2] + "]");
		l.setPosition(window->getWidth() / 2 - l.getWidth() / 2, window->getHeight() / 2 - l.getHeight() + x);
		
		window->drawText(l);
		x = x + 70;
	}
}

void Lobbies::nameOnClick(Window *window)
{
	std::vector<std::string> stop;
	stop.push_back("STOP");

	std::vector<std::string> msg;
	msg.push_back("MENU");

	client.send(msg);

	_error = false;
	_nameCase.setColor(168, 168, 168);
	while (1) {

		client.recieve();

		while (window->pollEvent()) {

			if (window->getEventClose()) {
				window->close();
				client.send(stop);
				exit(0);
			}
			if (window->getEventKeyPressed()) {
				if (window->getEventKeyEscape()) {
					_nameCase.setColor(255, 255, 255);
					return;
				}
				if (window->getEventKeyReturn()) {
					_nameCase.setColor(255, 255, 255);
					return;
				}
			}
			if (window->getEventTextEntered()) {
				if (_name.size() < 12 && (window->getUnicode() >= 33 && window->getUnicode() <= 126)) {
					_name += window->getUnicode();
					_nameDisplay.setString(_name);
				} else if (window->getUnicode() == 8 && _name.size() > 0) {
					_name.erase(_name.size() - 1);
					_nameDisplay.setString(_name);
				}
			}
			if (window->getEventMouseButtonPressed()) {
				sf::Vector2i mousePos = sf::Mouse::getPosition(window->_window);
				if (_nbPlayerCase.getGlobalBounds(mousePos.x, mousePos.y)) {
					_nameCase.setColor(255, 255, 255);
					return (Lobbies::nbPlayerOnClick(window));
				} else if (_createCase.getGlobalBounds(mousePos.x, mousePos.y)) {
					_nameCase.setColor(255, 255, 255);
					return (Lobbies::createOnClick(window));
				} else if (!_nameCase.getGlobalBounds(mousePos.x, mousePos.y)) {
					_nameCase.setColor(255, 255, 255);
					return;
				}
			}
		}

		client.interpreter(window);

		std::vector<std::string> datas = dataToVector(client.getRecv());
		Lobbies::display(window, datas);
		window->display();
	}
}

void Lobbies::nbPlayerOnClick(Window *window)
{
	std::vector<std::string> stop;
	stop.push_back("STOP");

	std::vector<std::string> msg;
	msg.push_back("MENU");

	client.send(msg);

	_error = false;
	_nbPlayerCase.setColor(168, 168, 168);
	while (1) {

		client.recieve();

		while (window->pollEvent()) {

			if (window->getEventClose()) {
				window->close();
				client.send(stop);
				exit(0);
			}
			if (window->getEventKeyPressed()) {
				if (window->getEventKeyEscape()) {
					_nbPlayerCase.setColor(255, 255, 255);
					return;
				}
				if (window->getEventKeyReturn()) {
					_nbPlayerCase.setColor(255, 255, 255);
					return;
				}
			}
			if (window->getEventTextEntered()) {
				if (_nbPlayer.size() < 1 && (window->getUnicode() >= 49 && window->getUnicode() <= 52)) {
					_nbPlayer += window->getUnicode();
					_nbPlayerDisplay.setString(_nbPlayer);
				} else if (window->getUnicode() == 8 && _nbPlayer.size() > 0) {
					_nbPlayer.erase(_nbPlayer.size() - 1);
					_nbPlayerDisplay.setString(_nbPlayer);
				}
			}
			if (window->getEventMouseButtonPressed()) {
				sf::Vector2i mousePos = sf::Mouse::getPosition(window->_window);
				if (_nameCase.getGlobalBounds(mousePos.x, mousePos.y)) {
					_nbPlayerCase.setColor(255, 255, 255);
					return (Lobbies::nameOnClick(window));
				} else if (_createCase.getGlobalBounds(mousePos.x, mousePos.y)) {
					_nbPlayerCase.setColor(255, 255, 255);
					return (Lobbies::createOnClick(window));
				} else if (!_nbPlayerCase.getGlobalBounds(mousePos.x, mousePos.y)) {
					_nbPlayerCase.setColor(255, 255, 255);
					return;
				}
			}
		}

		client.interpreter(window);

		std::vector<std::string> datas = dataToVector(client.getRecv());
		Lobbies::display(window, datas);
		window->display();
	}
}

void Lobbies::createOnClick(Window *window)
{
	if (_name.size() == 0) {
		_error = true;
		_errorMsg = "Le nom du lobby ne peut pas etre vide!";
		return;
	}
	std::vector<std::string> msg;
	msg.push_back("CREATE");
	msg.push_back(_name);
	msg.push_back(_nbPlayer);

	client.send(msg);

	lobby(window);
}

void Lobbies::join(Window *window, std::string name, int nb_player, int limit_player)
{
	if (nb_player >= limit_player) {
		_error = true;
		_errorMsg = "Le lobby est plein!";
		return;
	}
	std::vector<std::string> msg;
	msg.push_back("JOIN");
	msg.push_back(name);

	client.send(msg);

	lobby(window);
}

void Lobbies::setError(bool error)
{
	_error = error;
}