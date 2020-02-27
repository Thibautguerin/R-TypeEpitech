/*
** EPITECH PROJECT, 2019
** main.cpp
** File description:
** ${FILEDESCRIPTION}
*/

#include "Server.hpp"

boost::asio::io_service io_service;
Server server(io_service);

void signal_callback(int signum)
{
	server.signal_callback_handler();
}

int main()
{
	try {
	    signal(SIGINT, signal_callback);
	    // server.debugModeLobbies();
	    while (1) {
	    	server.receive();
	    	server.interpreter();
	    }
    } catch (std::exception &e) {
    	std::cerr << e.what() << std::endl;
    }
    return (0);
}