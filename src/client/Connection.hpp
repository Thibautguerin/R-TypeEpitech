/*
** EPITECH PROJECT, 2019
** Connection.hpp
** File description:
** class for connection
*/

#ifndef CONNECTION_HPP
#define CONNECTION_HPP

#include <iostream>
#include <string>

#include "SFML/Window/SFMLWindow.hpp"
#include "SFML/Rectangle/SFMLRectangle.hpp"
#include "SFML/Text/SFMLText.hpp"

class Connection
{
	public:
		Connection(Window *window);
		~Connection(void);
		void display(Window *window);
		void pseudoOnClick(Window *window);
		void addressOnClick(Window *window);
		void portOnClick(Window *window);
		void tryConnection(Window *window);
		void setError(bool error);

		RectangleSfml _pseudoCase;
		RectangleSfml _addressCase;
		RectangleSfml _portCase;
		RectangleSfml _buttonCase;
	private:
		std::string _pseudo;
		std::string _address;
		std::string _port;
		Text _pseudoDisplay;
		Text _addressDisplay;
		Text _portDisplay;
		Text _buttonDisplay;
		Text _title;
		std::string _errorMsg;
		bool _error;
};

#endif