/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjarnac <pjarnac@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 16:38:12 by pjarnac           #+#    #+#             */
/*   Updated: 2025/11/20 16:38:12 by pjarnac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdexcept>

#include <iostream>

#include "BitcoinExchange.hpp"

int	main(int t_c, char **t_args)
{
	if (t_c != 2)
	{
		std::cerr << "Invalid arguments, usage: btc file_path\n";
		return (1);
	}
	try
	{
		BitcoinExchange	btc;
		btc.processInput(t_args[1]);
	}
	catch (std::exception &e)
	{
		std::cerr << "Error: " << e.what() << "\n";
	}
}
