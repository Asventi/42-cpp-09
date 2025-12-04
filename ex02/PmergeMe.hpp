/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjarnac <pjarnac@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 16:52:05 by pjarnac           #+#    #+#             */
/*   Updated: 2025/11/26 16:52:05 by pjarnac          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
# define PMERGEME_HPP

typedef std::allocator<int>						int_alloc;
typedef std::allocator<std::pair<int, int> >	pair_alloc;
typedef std::allocator<size_t>					idx_alloc;

template <template<typename, typename> class T>
void	mergins(T<int, int_alloc > &t_ctn);

# include "PmergeMe.tpp"

#endif
