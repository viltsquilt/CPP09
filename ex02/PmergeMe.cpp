#include "PmergeMe.hpp"

PmergeMe::PmergeMe()
{

}

PmergeMe::PmergeMe(const PmergeMe& orig) : _vec(orig._vec), _deq(orig._deq), _elements(orig._elements)
{

}

PmergeMe&	PmergeMe::operator=(const PmergeMe& orig)
{
	if (this != &orig)
	{
		_vec = orig._vec;
		_deq = orig._deq;
		_elements = orig._elements;
	}
	return (*this);
}

PmergeMe::~PmergeMe()
{

}

void	PmergeMe::createJacobstahl()
{

}
