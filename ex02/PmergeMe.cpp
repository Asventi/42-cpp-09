#include "PmergeMe.hpp"
#include <iostream>
#include <algorithm>

static std::vector<size_t> generateJacobsthalSequence(size_t t_n)
{
	std::vector<size_t> vct;
	vct.push_back(1);
	if (t_n == 1)
		return vct;
	vct.push_back(3);
	size_t prev = 1;
	size_t curr = 3;
	while (true)
	{
		size_t next = curr + 2 * prev;
		if (next > t_n)
			break;
		vct.push_back(next);
		prev = curr;
		curr = next;
	}
	return vct;
}

static std::vector<size_t> createInsertionOrder(size_t t_pendSize)
{
	std::vector<size_t> order;
	if (t_pendSize == 0)
		return order;
	std::vector<size_t> jacobsthal = generateJacobsthalSequence(t_pendSize);
	std::vector<bool> used(t_pendSize, false);

	size_t prevJacob = 0;
	for (size_t i = 0; i < jacobsthal.size(); ++i)
	{
		size_t jacobIdx = jacobsthal[i];
		if (jacobIdx > t_pendSize)
			jacobIdx = t_pendSize;
		for (size_t j = jacobIdx; j > prevJacob && j > 0; --j)
		{
			if (!used[j - 1])
			{
				order.push_back(j - 1);
				used[j - 1] = true;
			}
		}
		prevJacob = jacobIdx;
	}
	for (size_t i = 0; i < t_pendSize; ++i)
	{
		if (!used[i])
			order.push_back(i);
	}

	return order;
}

void merginsVct(std::vector<int> &t_vct)
{
	std::vector<std::pair<int, int> >	pairs;
	std::vector<std::pair<int, int> >	vct;
	std::vector<int>					right_els;
	size_t								n = t_vct.size();
	bool								has_remain = (n % 2 == 1);
	int									remain = 0;

	if (n <= 1)
		return;
	if (has_remain)
		remain = t_vct[n - 1];
	for (size_t i = 0; i + 1 < n; i += 2)
	{
		if (t_vct[i] < t_vct[i + 1])
			pairs.push_back(std::make_pair(t_vct[i], t_vct[i + 1]));
		else
			pairs.push_back(std::make_pair(t_vct[i + 1], t_vct[i]));
	}
	if (pairs.empty())
		return;
	for (size_t i = 0; i < pairs.size(); ++i)
		right_els.push_back(pairs[i].second);
	merginsVct(right_els);
	for (size_t i = 0; i < right_els.size(); ++i)
	{
		for (size_t j = 0; j < pairs.size(); ++j)
		{
			if (pairs[j].second == right_els[i])
			{
				vct.push_back(pairs[j]);
				break;
			}
		}
	}
	std::vector<int> main;
	std::vector<int> pend;

	main.push_back(vct[0].first);
	main.push_back(vct[0].second);
	for (size_t i = 1; i < vct.size(); ++i)
	{
		main.push_back(vct[i].second);
		pend.push_back(vct[i].first);
	}
	std::vector<size_t> insert_order = createInsertionOrder(pend.size());

	for (size_t i = 0; i < insert_order.size(); ++i)
	{
		int value = pend[insert_order[i]];

		main.insert(std::upper_bound(main.begin(), main.end(), value), value);
	}
	if (has_remain)
	{
		main.insert(std::upper_bound(main.begin(), main.end(), remain), remain);
	}
	for (std::vector<int>::iterator it = main.begin(); it != main.end(); ++it)
	{
		std::cout << *it << " ";
	}
	std::cout << "\n" << std::endl;
	t_vct = main;
}
