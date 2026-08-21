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
		std::vector<int>	_vector;
		std::deque<int>		_deque;
		
	public:
		PmergeMe();
		PmergeMe(const PmergeMe& orig);
		PmergeMe&	operator=(const PmergeMe& orig);
		~PmergeMe();
		void	parseInput(int argc, char **argv);
		void	getJacobstahl();
		void	processVec();
		void	processDeq();
		void	printVec(std::string text);
		void	printDeq(std::string text);

}
