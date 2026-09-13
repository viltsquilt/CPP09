#include "PmergeMe.hpp"

// Runs PmergeMe and prints Error if parsing or sorting setup fails.
int	main(int argc, char **argv)
{
	PmergeMe	sorter;

	if (argc < 2)
	{
		std::cerr << "Error" << std::endl;
		return (1);
	}
	try
	{
		sorter.process(argc - 1, argv + 1);
	}
	catch (const std::exception& error)
	{
		(void)error;
		std::cerr << "Error" << std::endl;
		return (1);
	}
	return (0);
}
