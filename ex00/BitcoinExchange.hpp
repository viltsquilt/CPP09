#pragma once

#include <iostream>
#include <cmath>
#include <map>
#include <regex>
#include <fstream>
#include <limits>

class BitcoinExchange
{
	private:
		std::map<std::string, double>	_data;
	public:
		BitcoinExchange();
		BitcoinExchange(const BitcoinExchange& orig);
		BitcoinExchange& operator=(const BitcoinExchange& orig);
		~BitcoinExchange();

		void	loadRates();
		void	loadDates();
		void	convertBitcoinValue(std::string date, double value);
		void	processInputfile(const std::string &arg);
		void	validRate(double rate);
		void	validDate(std::string date);
};
