#include "RPN.hpp"

RPN::RPN()
{

}

RPN::RPN(const RPN& orig) : _nummbers(orig._numbers)
{

}

RPN&	RPN::operator=(const RPN& orig)
{
	if (this != &orig)
	{
		_numbers = orig._numbers;
	}
	return (*this);
}

RPN::~RPN()
{

}

void	RPN::calculateRPN(std::string arg)
{

}
