#include "BitcoinExchange.hpp"

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		std::cerr << "Invalid number of arguments" << std::endl;
	}
	BitcoinExchange b;
	b.loadRates();
	b.processInputFile(argv[1]);
	return 0;
}
