/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjarnac <pjarnac@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 17:50:11 by pjarnac           #+#    #+#             */
/*   Updated: 2025/11/24 17:50:11 by pjarnac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

#include <stack>
#include <iostream>
#include <sstream>

static int	tpop(std::stack<int> &t_stack)
{
	if (t_stack.size() < 1)
		throw std::logic_error("no enough number in stack");
	int	buf = t_stack.top();
	t_stack.pop();
	return (buf);
}

int rpn(std::string const &t_str)
{
	std::stringstream	sstr(t_str);
	std::stack<int>		stack;
	char				token;
	int					buf;

	while ((sstr >> token))
	{
		if (std::isdigit(token))
			stack.push(token - '0');
		else if (std::string("+/*-").find(token) == std::string::npos)
			throw std::logic_error("invalid expression character");
		else if (token == '+')
			stack.push(tpop(stack) + tpop(stack));
		else if (token == '-')
		{
			buf = tpop(stack);
			stack.push(tpop(stack) - buf);
		}
		else if (token == '*')
		{
			stack.push(tpop(stack) * tpop(stack));
		}
		else if (token == '/')
		{
			buf = tpop(stack);
			if (buf == 0)
				throw std::logic_error("division by zero not allowed");
			stack.push(tpop(stack) / buf);
		}
	}
	return (stack.top());
}
