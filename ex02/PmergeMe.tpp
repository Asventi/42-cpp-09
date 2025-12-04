#ifndef PMERGEME_TPP
# define PMERGEME_TPP

#include "PmergeMe.hpp"
#include <algorithm>

template<template<typename, typename> class T>
T<size_t, idx_alloc> jacobsthal(size_t t_n)
{
	T<size_t, idx_alloc>	ctn;
	size_t					next;

	ctn.push_back(3);
	size_t prev = 1;
	size_t curr = 3;
	while (true)
	{
		next = curr + 2 * prev;
		ctn.push_back(next);
		if (next > t_n)
			break;
		prev = curr;
		curr = next;
	}
	return ctn;
}

template<template<typename, typename> class T>
T<size_t, idx_alloc> insertion_order(size_t t_pend_size)
{
	T<size_t, idx_alloc>			order;
	if (t_pend_size == 0)
		return order;
	T<size_t, idx_alloc>			jacob = jacobsthal<T>(t_pend_size);
	T<bool, std::allocator<bool> >	used(t_pend_size, false);
	size_t							jacob_idx;
	size_t							prev_jacob = 0;

	for (size_t i = 0; i < jacob.size(); ++i)
	{
		jacob_idx = jacob[i];
		if (jacob_idx > t_pend_size)
			jacob_idx = t_pend_size;
		for (size_t j = jacob_idx; j > prev_jacob && j > 0; --j)
		{
			order.push_back(j - 1);
			used[j - 1] = true;
		}
		prev_jacob = jacob_idx;
	}
	// for (typename T<size_t, idx_alloc>::iterator it = order.begin(); it != order.end(); ++it)
	// {
	// 	std::cout << *it << " ";
	// }
	// std::cout << "\n";
	return order;
}

template <template<typename, typename> class T>
void mergins(T<int, std::allocator<int> > &t_ctn)
{
	T<std::pair<int, int>, pair_alloc >	pairs;
	T<std::pair<int, int>, pair_alloc >	ctn;
	T<int, int_alloc>					right_els;
	size_t								n = t_ctn.size();
	bool								has_remain = (n % 2 == 1);
	int									remain = 0;

	if (n <= 1)
		return;
	if (has_remain)
		remain = t_ctn[n - 1];
	for (size_t i = 0; i + 1 < n; i += 2)
	{
		if (t_ctn[i] < t_ctn[i + 1])
			pairs.push_back(std::make_pair(t_ctn[i], t_ctn[i + 1]));
		else
			pairs.push_back(std::make_pair(t_ctn[i + 1], t_ctn[i]));
	}
	if (pairs.empty())
		return;
	for (size_t i = 0; i < pairs.size(); ++i)
		right_els.push_back(pairs[i].second);
	mergins<T>(right_els);
	for (size_t i = 0; i < right_els.size(); ++i)
	{
		for (size_t j = 0; j < pairs.size(); ++j)
		{
			if (pairs[j].second == right_els[i])
			{
				ctn.push_back(pairs[j]);
				break;
			}
		}
	}
	T<int, int_alloc> main;
	T<int, int_alloc> pend;

	main.push_back(ctn[0].first);
	main.push_back(ctn[0].second);
	for (size_t i = 1; i < ctn.size(); ++i)
	{
		main.push_back(ctn[i].second);
		pend.push_back(ctn[i].first);
	}
	T<size_t, idx_alloc> insert_order = insertion_order<T>(pend.size());

	for (size_t i = 0; i < insert_order.size(); ++i)
	{
		int value = pend[insert_order[i]];

		main.insert(std::upper_bound(main.begin(), main.end(), value), value);
	}
	if (has_remain)
	{
		main.insert(std::upper_bound(main.begin(), main.end(), remain), remain);
	}
	t_ctn = main;
}

#endif
