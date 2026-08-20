#include "RPN.hpp"

RPN::RPN()
{

}

RPN::RPN(const RPN& orig) : _numbers(orig._numbers)
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
	std::istringstream	stream(arg);
	std::string			token;

	while(stream >> token)
	{
		if (token.length() == 1 && isdigit(token[0]))
			_numbers.push(std::stol(token));
		else if (token.length() == 1 && !isdigit(token[0]))
		{
			if (_numbers.size() >= 2)
			{
				long	second = _numbers.top();
				_numbers.pop();
				long	first = _numbers.top();
				_numbers.pop();
				long	res;

				switch (token[0])
				{
					case '+':
						res = first + second;
						break;
					case '-':
						res = first - second;
						break;
					case '*':
						res = first * second;
						break;
					case '/':
						if (second == 0)
							throw std::runtime_error("Error");
						res = first / second;
						break;
					default :
						throw std::runtime_error("Error");
				}
				_numbers.push(res);
			}
			else
				throw std::runtime_error("Error");
		}
		else
			throw std::runtime_error("Error");
	}
	if (_numbers.size() != 1)
		throw std::runtime_error("Error");
	else
		std::cout << _numbers.top() << std::endl;
}
