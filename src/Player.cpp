/*
** EPITECH PROJECT, 2019
** Player.cpp
** File description:
** player class
*/

#include "Player.hpp"

Player::Player(std::string name, boost::asio::ip::udp::endpoint endpoint)
{
	_name = name;
	_endpoint = endpoint;
}

Player::~Player(void)
{
}

std::string Player::getName(void) const
{
	return (_name);
}

void Player::setName(std::string name)
{
	_name = name;
}

boost::asio::ip::udp::endpoint Player::getEndpoint(void) const
{
	return (_endpoint);
}

boost::asio::ip::address Player::getAddress(void) const
{
	return (_endpoint.address());
}

unsigned short Player::getPort(void) const
{
	return (_endpoint.port());
}

bool Player::getReady(void) const
{
	return (_ready);
}

void Player::toggleReady(void)
{
	if (_ready == false)
		_ready = true;
	else
		_ready = false;
}