/*
** EPITECH PROJECT, 2019
** DataToVector.hpp
** File description:
** data to vector for udp communication
*/

#ifndef DATATOVECTOR_HPP
#define DATATOVECTOR_HPP

#include <string>
#include <iostream>
#include <boost/array.hpp>
#include <boost/algorithm/string.hpp>
#include <vector>

std::vector<std::string> dataToVector(boost::array<char, 1000> data);

#endif