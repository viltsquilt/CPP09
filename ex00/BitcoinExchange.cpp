#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange()
{

}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& orig) : _data(orig._data)
{

}

BitcoinExchange&	BitcoinExchange::operator=(const BitcoinExchange& orig)
{
	if (this != &orig)
	{
		_data = orig._data;
	}
	return (*this);
}

BitcoinExchange::~BitcoinExchange()
{

}

void	BitcoinExchange::loadRates()
{
	std::ifstream	data("data.csv");
	if (!data)
	{
		std::cerr << "Error: could not open data.csv file\n";
		return ;
	}
	std::string	line;
	std::getline(data, line);
	while (std::getline(data, line))
	{
		std::string	date;
		double	rate;
		size_t	pos = line.find(',');
		if (pos == std::string::npos)
		{
			std::cerr << "missing comma on data.csv\n";
			data.close();
			return ;
		}
		try
		{
			date = line.substr(0, pos);
			validDate(date);
			rate = std::stod(line.substr(pos + 1));
			validRate(rate);
		}
		catch (std::exception &e)
		{
			std::cerr << e.what() << "\n";
			data.close();
			return ;
		}
		_data.insert({date, rate});
	}
	data.close();
}

void	BitcoinExchange::convertBitcoinValue(std::string date, double value)
{
	double	rate;
	std::map<std::string, double>::iterator it = _data.upper_bound(date);
	if(it == _data.begin())
		throw std::runtime_error("Error: bad input => " + date);
	it--;
	rate = it->second;
	std::cout << date << " => " << value << " = " << rate * value << std::endl;
}

void	BitcoinExchange::processInputFile(const std::string &arg)
{
	std::ifstream	file(arg);
	if (!file)
	{
		std::cerr << "Error: could not open input file\n";
		return ;
	}
	std::string	line;
	std::getline(file, line);
	while (std::getline(file, line))
	{
		std::string	date;
		double	rate;
		size_t	pos = line.find('|');
		if (pos == std::string::npos)
		{
			std::cerr << "Error: bad input => " + line + "\n";
			continue;
		}
		try
		{
			date = line.substr(0, pos - 1);
			if (pos + 1 == line.length())
				throw std::runtime_error("Error: bad input => " + line);
			validDate(date);
			rate = std::stod(line.substr(pos + 2));
			validRate(rate);
			if (rate > 1000)
				throw std::runtime_error("Error: number too large");
			convertBitcoinValue(date, rate);
		}
		catch (std::exception &e)
		{
			std::cerr << e.what() << "\n";
		}
	}
	file.close();

}

void	BitcoinExchange::validRate(double rate)
{
	if (rate < 0)
		throw std::runtime_error("Error: not a positive number");
	if (rate > std::numeric_limits<double>::max())
		throw std::runtime_error("Error: number too large");

}

void	BitcoinExchange::validDate(std::string date)
{
	std::regex	regex("\\d{4}\\-\\d{2}\\-\\d{2}");
	if(!std::regex_match(date, regex))
		throw std::runtime_error("Error: bad input => " + date);
	int	year = stoi(date.substr(0, 4));
	int	month = stoi(date.substr(5, 2));
	int	day = stoi(date.substr(8, 2));
	if (month < 1 || month > 12 || day < 1 || day > 31)
		throw std::runtime_error("Error: bad input => " + date);
	if (month == 2)
	{
		if (day == 29)
		{
			if ((year % 4 != 0 || year % 100 == 0) &&(year % 400 != 0))
				throw std::runtime_error("Error: bad input => " + date);
		}
		if (day > 29)
			throw std::runtime_error("Error: bad input => " + date);
	}
	if ((month == 4 || month == 6 || month == 9 || month == 11) && (day == 31))
			throw std::runtime_error("Error: bad input => " + date);
}
