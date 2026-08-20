#pragma once

#include <iostream>
#include <deque>
#include <vector>
#include <ctime>
#include <utility>
#include <algorithm>

class PmergeMe
{
	private:
		std::vector<int>	_vec;
		std::deque<int>		_deq;
		size_t				_elements;
	public:
		PmergeMe();
		PmergeMe(const PmergeMe& orig);
		PmergeMe&	operator=(const PmergeMe& orig);
		~PmergeMe();
		void	createJacobstahl();
}
