/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjarnac <pjarnac@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 14:38:22 by pjarnac           #+#    #+#             */
/*   Updated: 2025/11/21 14:38:22 by pjarnac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

# define DEFAULT_DB_NAME "data.csv"
# define DB_HEADER "date,exchange_rate"
# define INPUT_HEADER "date | value"
# include <map>
#include <stdexcept>
# include <string>

class BitcoinExchange
{
private:
	std::map<long int, float>	m_data;
private:
	void	parseCsv(std::string const &t_path);

	static std::pair<long int, float>	parseLine(std::string const &t_line,
		                                           std::string const &t_sep);
public:
	void	processInput(std::string const &t_path);
	BitcoinExchange();
	explicit BitcoinExchange(std::string const &t_dbPath);
	BitcoinExchange(BitcoinExchange const &t_e);
	BitcoinExchange	&operator=(BitcoinExchange const &t_e);
	~BitcoinExchange();
};

#endif
