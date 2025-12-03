/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjarnac <pjarnac@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 17:50:02 by pjarnac           #+#    #+#             */
/*   Updated: 2025/11/24 17:50:02 by pjarnac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "RPN.hpp"

int	main(int t_c, char **t_args)
{
	if (t_c != 2)
	{
		std::cerr << "Invalid arguments, usage: rpn expression";
		return (1);
	}
	try
	{
		std::cout << rpn(t_args[1]) << "\n";
	}
	catch (std::logic_error &e)
	{
		std::cerr << "Error: " << e.what() << "\n";
	}
	return (0);
}
