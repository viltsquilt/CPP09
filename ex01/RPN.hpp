#pragma once

#include <iostream>
#include <stack>
#include <sstream>

class RPN
{
	private:
		std::stack<long>	_numbers;
	public:
		RPN();
		RPN(const RPN& orig);
		RPN& operator=(const RPN& orig);
		~RPN();
		void	calculateRPN(std::string arg);
};
