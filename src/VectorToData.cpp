/*
** EPITECH PROJECT, 2019
** VectorToData.cpp
** File description:
** vector to data for udp communication
*/

#include "VectorToData.hpp"

boost::array<char, 1000> vectorToData(std::vector<std::string> vect)
{
	std::string tmp = boost::algorithm::join(vect, " ");
	boost::array<char, 1000> data;
	int i = 0;

	while (i < (tmp).size()) {
		data[i] = tmp[i];
		i++;
	}
	data[i] = '\0';
	return (data);
}