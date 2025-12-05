/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjarnac <pjarnac@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 14:38:22 by pjarnac           #+#    #+#             */
/*   Updated: 2025/11/21 14:38:22 by pjarnac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

#include <algorithm>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <cstring>
#include <ctime>
#include <iostream>

std::pair<long int, float> BitcoinExchange::parseLine(std::string const &t_line, std::string const &t_sep, bool t_limit)
{
	std::string				token;
	float					value;
	tm						tm = {};
	time_t					tmT;
	std::string::size_type	tokenPos;

	tokenPos = t_line.find(t_sep);
	if (tokenPos == std::string::npos)
		throw std::logic_error("missing field: " + t_line);
	token = t_line.substr(0, tokenPos);
	if (strptime(token.c_str(), "%Y-%m-%d", &tm) != token.c_str() + tokenPos)
		throw std::logic_error("invalid date format: " + t_line);
	tmT = timegm(&tm);
	token = t_line.substr(tokenPos + t_sep.length());
	if (token.length() == 0)
		throw std::logic_error("missing field: " + t_line);
	std::stringstream	sstr(token);
	sstr >> value;
	if (sstr.fail())
		throw std::logic_error("invalid number: " + t_line);
	if (value < 0 || (t_limit && value > 1000))
		throw std::logic_error("number not allowed: " + t_line);
	if (token.find_first_not_of("0123456789.") != std::string::npos)
		throw std::logic_error("unrecognized character: " + t_line);
	if (token.find('.') != std::string::npos && (token.find('.') != token.rfind('.')))
		throw std::logic_error("invalid number: " + t_line);
	return (std::pair<long int, float>(tmT, value));
}


void	BitcoinExchange::parseCsv(std::string const &t_path)
{
	std::ifstream	file(t_path.c_str());
	std::string		str;

	if (!file.is_open())
		throw std::invalid_argument(t_path + " can't be opened.");
	std::getline(file, str);
	if (str != DB_HEADER)
		throw std::logic_error("invalid db header: " + str);
	while (std::getline(file, str))
	{
		if (str.length() == 0)
			continue ;
		if (!m_data.insert(parseLine(str, ",", false)).second)
			throw std::logic_error("duplicate date: " + str);
	}
	if (m_data.size() < 1)
		throw std::logic_error("no data in csv");
}

void BitcoinExchange::processInput(std::string const &t_path)
{
	std::ifstream				file(t_path.c_str());
	std::string					str;
	std::pair<long int, float>	line;
	std::map<long int, float>::iterator	it;

	if (!file.is_open())
		throw std::invalid_argument(t_path + " can't be opened.");
	std::getline(file, str);
	if (str != INPUT_HEADER)
		throw std::logic_error("invalid input header: " + str);
	while (std::getline(file, str))
	{
		if (str.length() == 0)
			continue ;
		try
		{
			line = parseLine(str, " | ", true);
		}
		catch (std::logic_error &e)
		{
			std::cout << "Error: " << e.what() << "\n";
			continue;
		}
		it = m_data.upper_bound(line.first);
		if (it-- == m_data.begin())
			std::cout << "Error no data available for date: " << str << "\n";
		std::cout << str << " = " << m_data[it->first] * line.second << "\n";
	}
}

BitcoinExchange::BitcoinExchange()
{
	parseCsv(DEFAULT_DB_NAME);
}

BitcoinExchange::BitcoinExchange(std::string const &t_dbPath)
{
	parseCsv(t_dbPath);
}

BitcoinExchange::BitcoinExchange(BitcoinExchange const &t_e): m_data(t_e.m_data)
{}

BitcoinExchange &BitcoinExchange::operator=(BitcoinExchange const &t_e)
{
	if (this == &t_e)
		return (*this);
	m_data = t_e.m_data;
	return (*this);
}

BitcoinExchange::~BitcoinExchange()
{
}
