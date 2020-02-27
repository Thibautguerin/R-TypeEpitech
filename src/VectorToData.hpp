/*
** EPITECH PROJECT, 2019
** VectorToData.hpp
** File description:
** vector to data for udp communication
*/

#ifndef VECTORTODATA_HPP
#define VECTORTODATA_HPP

#include <string>
#include <iostream>
#include <boost/array.hpp>
#include <boost/algorithm/string.hpp>
#include <vector>

boost::array<char, 1000> vectorToData(std::vector<std::string> vect);

#endif