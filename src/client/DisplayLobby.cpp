/*
** EPITECH PROJECT, 2019
** DisplayLobby.cpp
** File description:
** display the lobby
*/

#include "DisplayLobby.hpp"
#include "Global.hpp"

DisplayLobby::DisplayLobby(Window *window):
_readyCase(300, 80)
{
	_readyCase.setPosition(window->getWidth() / 2 - _readyCase.getWidth() / 2, window->getHeight() - window->getHeight() / 5 - _readyCase.getHeight());

	_readyDisplay.setFontSize(50);
	_readyDisplay.setFontColor(0, 0, 0);
	
	_title.setFontSize(100);
	_title.setFontColor(0, 0, 0);
}

DisplayLobby::~DisplayLobby(void)
{}

void DisplayLobby::display(Window *window, std::vector<std::string> datas)
{
	window->clear(55, 79, 99);

	_title.setString(datas[1] + " [" + datas[2] + "/" + datas[3] + "]");
	_title.setPosition(window->getWidth() / 2 - _title.getWidth() / 2, window->getHeight() / 4 - _title.getHeight());
	window->drawText(_title);

	std::vector<std::string> p;
	int x = -105;

	for (int i = 4; i < datas.size(); i++) {
		boost::split(p, datas[i], boost::is_any_of(";"));
		Text player;
		player.setFontSize(50);
		if (p[1].compare("1") == 0)
			player.setString(p[0] + " [pret]");
		else
			player.setString(p[0] + " [pas pret]");
		player.setFontColor(0, 0, 0);
		player.setPosition(window->getWidth() / 2 - player.getWidth() / 2, window->getHeight() / 2 - player.getHeight() + x);
		
		x = x + 70;

		window->drawText(player);

		if (p[0].compare(client.getPseudo()) == 0) {
			if (p[1].compare("0") == 0) {
				_readyDisplay.setString("Pret");
			} else {
				_readyDisplay.setString("Annuler");
			}
		}
	}

	_readyDisplay.setPosition(window->getWidth() / 2 - _readyDisplay.getWidth() / 2, _readyCase.getPosY());

	window->drawRectangle(_readyCase);
	window->drawText(_readyDisplay);
}

void DisplayLobby::toggleReady(std::vector<std::string> datas)
{
	std::vector<std::string> msg;
	msg.push_back("READY");
	msg.push_back(datas[1]);
	client.send(msg);
	client.recieve();
}