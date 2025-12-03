
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <cstdio>

#include "PmergeMe.hpp"
int main(int c, char **args)
{
	if (c < 2)
		return (0);
	int	buf;
	std::vector<int>	test;

	for (int i = 1; i < c; i++)
	{
		sscanf(args[i], "%d", &buf);
		test.push_back(buf);
	}
	merginsVct(test);
	for (std::vector<int>::iterator it = test.begin(); it != test.end(); ++it)
	{
		std::cout << *it << " ";
	}
}
