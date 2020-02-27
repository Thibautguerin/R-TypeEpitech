/*
** EPITECH PROJECT, 2019
** DataToVector.cpp
** File description:
** data to vector for udp communication
*/

#include "DataToVector.hpp"

std::vector<std::string> dataToVector(boost::array<char, 1000> data)
{
	std::vector<std::string> vect;
	std::string datas = data.data();

	boost::split(vect, datas, boost::is_any_of(" "));
	return (vect);
}