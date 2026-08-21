#include "PmergeMe.hpp"

PmergeMe::PmergeMe()
{

}

PmergeMe::PmergeMe(const PmergeMe& orig) : _vector(orig._vec), _deque(orig._deq)
{

}

PmergeMe&	PmergeMe::operator=(const PmergeMe& orig)
{
	if (this != &orig)
	{
		_vector = orig._vector;
		_deque = orig._deque;
	}
	return (*this);
}

PmergeMe::~PmergeMe()
{

}

void	PmergeMe::parseInput(int argc, char **argv)
{
	for (int i = 0; i < argc; i++)
	{
		size_t		pos;
		std::string	element = argv[i];
		int			num = stoi(element, &pos);
		if (pos != element.size())
			throw std::runtime_error("Error");
		if (num < 0)
			throw std::runtime_error("Error");
		_vector.push_back(num);
		_deque.push_back(num);
	}
}

void	PmergeMe::processVec()
{
	printVec("Before: ");
	const std::clock_t	start = std::clock();
	fordJohnsonVector(_vector);
	const std::clock_t	end = std::clock();
	printVec("After: ");
	processTime(start, end, "vector");
}

void	PmergeMe::processDeq()
{
	printDeq("Before: ");
	const std::clock_t	start = std::clock();
	fordJohnsonDeque(_deque);
	const std::clock_t	end = std::clock();
	printDeq("After: ");
	processTime(start, end, "deque");

}

void	PmergeMe::processTime(std::clock_t start, std::clock_t end, std:::string type)
{
	double	us = (end - start) * 1000000.0 / CLOCKS_PER_SEC;
	if type == _vector
		std::cout << "Time to process a range of " << _vector.size() << " elements with std::" << type << " : " << us << "us\n";
	else
		std::cout << "Time to process a range of " << _deque.size() << " elements with std::" << type << " : " << us << "us\n";

}

void	PmergeMe::printVec(std::string text)
{
	std::cout << text;
	for (std::vector<int>::iterator it = _vector.begin(); it != _vector.end(); it++)
	{
		std::cout << *it << " ";
	}
	std::cout << std::endl;
}

void	PmergeMe::printDeq(std::string text)
{
	std::cout << text;
	for (std::deque<int>::iterator it = _deque.begin(); it != _deque.end(); it++)
	{
		std::cout << *it << " ";
	}
	std::cout << std::endl;
}

void	PmergeMe::fordJohnsonVector(std::vector<int> _vector)
{

}

void	PmergeMe::fordJohnsonDeque(std::deque<int> _deque)
{

}

void	PmergeMe::getJacobstahl()
{

}
