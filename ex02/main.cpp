
#include <cstdio>
#include <cstdlib>
#include <deque>
#include <iostream>
#include <list>
#include <sstream>
#include <vector>

#include "PmergeMe.hpp"
int main(int c, char **args)
{
	if (c < 2)
		return (0);
	int					buf;
	std::deque<int>		deq;
	std::vector<int>	vct;
	double				start;
	double				end;

	for (int i = 1; i < c; i++)
	{
		std::string	n(args[i]);
		if (n.find_first_not_of("0123456789") != std::string::npos)
		{
			std::cerr << "Error\n";
			return (0);
		}
		if (sscanf(args[i], "%d", &buf) == EOF)
		{
			std::cerr << "Error\n";
			return (0);
		}
		deq.push_back(buf);
		vct.push_back(buf);
	}
	start = static_cast<double>(clock());
	mergins<std::deque>(deq);
	end = static_cast<double>(clock());
	std::cout << "Time took with deque in ms: " << (end - start) / CLOCKS_PER_SEC * 1000 << "ms\n";
	start = static_cast<double>(clock());
	mergins<std::vector>(vct);
	end = static_cast<double>(clock());
	std::cout << "Time took with vector in ms: " << (end - start) / CLOCKS_PER_SEC * 1000 << "ms\n";
	if (std::adjacent_find(deq.begin(), deq.end(), std::greater<int>())
			== deq.end())
		std::cout << "Container is sorted.\n";
	else
		std::cerr << "Container is not sorted.\n";
}
