#include "PmergeMe.hpp"

#include <cerrno>
#include <climits>
#include <cstdlib>
#include <iomanip>

// Creates an empty sorter object.
PmergeMe::PmergeMe() : _vectorTime(0.0), _dequeTime(0.0)
{
}

// Copies all stored results and timing values.
PmergeMe::PmergeMe(const PmergeMe& orig)
	: _original(orig._original),
	  _vectorResult(orig._vectorResult),
	  _dequeResult(orig._dequeResult),
	  _vectorTime(orig._vectorTime),
	  _dequeTime(orig._dequeTime)
{
}

// Assigns all stored results and timing values.
PmergeMe&	PmergeMe::operator=(const PmergeMe& orig)
{
	if (this != &orig)
	{
		_original = orig._original;
		_vectorResult = orig._vectorResult;
		_dequeResult = orig._dequeResult;
		_vectorTime = orig._vectorTime;
		_dequeTime = orig._dequeTime;
	}
	return (*this);
}

// Destroys the sorter object.
PmergeMe::~PmergeMe()
{
}

// Parses one argument as a strictly positive integer.
int	PmergeMe::parseNumber(const std::string& text)
{
	char	*end;
	long	value;

	if (text.empty())
		throw std::runtime_error("Error");
	for (std::size_t i = 0; i < text.size(); ++i)
	{
		if (text[i] < '0' || text[i] > '9')
			throw std::runtime_error("Error");
	}
	errno = 0;
	value = std::strtol(text.c_str(), &end, 10);
	if (*end != '\0' || errno == ERANGE || value <= 0 || value > INT_MAX)
		throw std::runtime_error("Error");
	return (static_cast<int>(value));
}

// Parses argv into a vector.
std::vector<int>	PmergeMe::parseVector(int argc, char **argv)
{
	std::vector<int>	values;

	for (int i = 0; i < argc; ++i)
		values.push_back(parseNumber(argv[i]));
	return (values);
}

// Parses argv into a deque.
std::deque<int>	PmergeMe::parseDeque(int argc, char **argv)
{
	std::deque<int>	values;

	for (int i = 0; i < argc; ++i)
		values.push_back(parseNumber(argv[i]));
	return (values);
}

// Builds the Jacobsthal insertion order for pending elements.
std::vector<int>	PmergeMe::jacobsthalOrder(std::size_t size)
{
	std::vector<int>	order;
	std::size_t		prev;
	std::size_t		jacob;
	std::size_t		next;

	if (size == 0)
		return (order);
	order.push_back(0);
	prev = 1;
	jacob = 3;
	while (prev < size)
	{
		std::size_t last = jacob;
		if (last > size)
			last = size;
		for (std::size_t i = last; i > prev; --i)
			order.push_back(static_cast<int>(i - 1));
		next = jacob + 2 * prev;
		prev = jacob;
		jacob = next;
	}
	return (order);
}

// Converts vector integers into items with stable ids.
std::vector<PmergeMe::Item>	PmergeMe::makeVectorItems(const std::vector<int>& input)
{
	std::vector<Item>	items;

	for (std::size_t i = 0; i < input.size(); ++i)
	{
		Item item;
		item.value = input[i];
		item.id = i;
		items.push_back(item);
	}
	return (items);
}

// Converts deque integers into items with stable ids.
std::deque<PmergeMe::Item>	PmergeMe::makeDequeItems(const std::deque<int>& input)
{
	std::deque<Item>	items;

	for (std::size_t i = 0; i < input.size(); ++i)
	{
		Item item;
		item.value = input[i];
		item.id = i;
		items.push_back(item);
	}
	return (items);
}

// Converts sorted vector items back to integers.
std::vector<int>	PmergeMe::toIntVector(const std::vector<Item>& items)
{
	std::vector<int>	values;

	for (std::size_t i = 0; i < items.size(); ++i)
		values.push_back(items[i].value);
	return (values);
}

// Converts sorted deque items back to integers.
std::deque<int>	PmergeMe::toIntDeque(const std::deque<Item>& items)
{
	std::deque<int>	values;

	for (std::size_t i = 0; i < items.size(); ++i)
		values.push_back(items[i].value);
	return (values);
}

// Finds an item by id inside a vector.
std::size_t	PmergeMe::findVectorItem(const std::vector<Item>& items, std::size_t id)
{
	for (std::size_t i = 0; i < items.size(); ++i)
	{
		if (items[i].id == id)
			return (i);
	}
	return (items.size());
}

// Finds an item by id inside a deque.
std::size_t	PmergeMe::findDequeItem(const std::deque<Item>& items, std::size_t id)
{
	for (std::size_t i = 0; i < items.size(); ++i)
	{
		if (items[i].id == id)
			return (i);
	}
	return (items.size());
}

// Finds where a value belongs in a sorted vector prefix.
std::size_t	PmergeMe::vectorInsertPosition(const std::vector<Item>& items,
	int value, std::size_t limit)
{
	std::size_t	left;
	std::size_t	right;

	left = 0;
	right = limit;
	while (left < right)
	{
		std::size_t mid = left + (right - left) / 2;
		if (value < items[mid].value)
			right = mid;
		else
			left = mid + 1;
	}
	return (left);
}

// Finds where a value belongs in a sorted deque prefix.
std::size_t	PmergeMe::dequeInsertPosition(const std::deque<Item>& items,
	int value, std::size_t limit)
{
	std::size_t	left;
	std::size_t	right;

	left = 0;
	right = limit;
	while (left < right)
	{
		std::size_t mid = left + (right - left) / 2;
		if (value < items[mid].value)
			right = mid;
		else
			left = mid + 1;
	}
	return (left);
}

// Sorts vector items with the Ford-Johnson merge-insert method.
std::vector<PmergeMe::Item>	PmergeMe::fordJohnsonVector(std::vector<Item> items)
{
	std::vector<Pair>	pairs;
	std::vector<Item>	winners;
	std::vector<Item>	mainChain;
	std::vector<Pair>	orderedPairs;
	std::vector<int>	order;
	Item				odd;
	bool				hasOdd;

	if (items.size() <= 1)
		return (items);
	hasOdd = (items.size() % 2 != 0);
	for (std::size_t i = 0; i + 1 < items.size(); i += 2)
	{
		Pair pair;
		if (items[i].value < items[i + 1].value)
		{
			pair.loser = items[i];
			pair.winner = items[i + 1];
		}
		else
		{
			pair.loser = items[i + 1];
			pair.winner = items[i];
		}
		pairs.push_back(pair);
		winners.push_back(pair.winner);
	}
	if (hasOdd)
		odd = items[items.size() - 1];
	mainChain = fordJohnsonVector(winners);
	for (std::size_t i = 0; i < mainChain.size(); ++i)
	{
		for (std::size_t j = 0; j < pairs.size(); ++j)
		{
			if (pairs[j].winner.id == mainChain[i].id)
				orderedPairs.push_back(pairs[j]);
		}
	}
	order = jacobsthalOrder(orderedPairs.size());
	for (std::size_t i = 0; i < order.size(); ++i)
	{
		Pair pair = orderedPairs[order[i]];
		std::size_t winnerPos = findVectorItem(mainChain, pair.winner.id);
		std::size_t pos = vectorInsertPosition(mainChain, pair.loser.value, winnerPos);
		mainChain.insert(mainChain.begin() + pos, pair.loser);
	}
	if (hasOdd)
	{
		std::size_t pos = vectorInsertPosition(mainChain, odd.value, mainChain.size());
		mainChain.insert(mainChain.begin() + pos, odd);
	}
	return (mainChain);
}

// Sorts deque items with the Ford-Johnson merge-insert method.
std::deque<PmergeMe::Item>	PmergeMe::fordJohnsonDeque(std::deque<Item> items)
{
	std::deque<Pair>	pairs;
	std::deque<Item>	winners;
	std::deque<Item>	mainChain;
	std::deque<Pair>	orderedPairs;
	std::vector<int>	order;
	Item			odd;
	bool			hasOdd;

	if (items.size() <= 1)
		return (items);
	hasOdd = (items.size() % 2 != 0);
	for (std::size_t i = 0; i + 1 < items.size(); i += 2)
	{
		Pair pair;
		if (items[i].value < items[i + 1].value)
		{
			pair.loser = items[i];
			pair.winner = items[i + 1];
		}
		else
		{
			pair.loser = items[i + 1];
			pair.winner = items[i];
		}
		pairs.push_back(pair);
		winners.push_back(pair.winner);
	}
	if (hasOdd)
		odd = items[items.size() - 1];
	mainChain = fordJohnsonDeque(winners);
	for (std::size_t i = 0; i < mainChain.size(); ++i)
	{
		for (std::size_t j = 0; j < pairs.size(); ++j)
		{
			if (pairs[j].winner.id == mainChain[i].id)
				orderedPairs.push_back(pairs[j]);
		}
	}
	order = jacobsthalOrder(orderedPairs.size());
	for (std::size_t i = 0; i < order.size(); ++i)
	{
		Pair pair = orderedPairs[order[i]];
		std::size_t winnerPos = findDequeItem(mainChain, pair.winner.id);
		std::size_t pos = dequeInsertPosition(mainChain, pair.loser.value, winnerPos);
		mainChain.insert(mainChain.begin() + pos, pair.loser);
	}
	if (hasOdd)
	{
		std::size_t pos = dequeInsertPosition(mainChain, odd.value, mainChain.size());
		mainChain.insert(mainChain.begin() + pos, odd);
	}
	return (mainChain);
}

// Prints a vector on one line with a label.
void	PmergeMe::printVector(const std::string& text, const std::vector<int>& values)
{
	std::cout << text;
	for (std::size_t i = 0; i < values.size(); ++i)
	{
		if (i != 0)
			std::cout << " ";
		std::cout << values[i];
	}
	std::cout << std::endl;
}

// Prints a deque on one line with a label.
void	PmergeMe::printDeque(const std::string& text, const std::deque<int>& values)
{
	std::cout << text;
	for (std::size_t i = 0; i < values.size(); ++i)
	{
		if (i != 0)
			std::cout << " ";
		std::cout << values[i];
	}
	std::cout << std::endl;
}

// Prints the measured processing time for one container.
void	PmergeMe::printTime(std::size_t size, const std::string& container, double us)
{
	std::cout << "Time to process a range of " << size
			  << " elements with std::" << container << " : "
			  << std::fixed << std::setprecision(5) << us << " us" << std::endl;
}

// Parses, sorts, times, and prints the full exercise output.
void	PmergeMe::process(int argc, char **argv)
{
	std::clock_t	start;
	std::clock_t	end;
	std::vector<int>	vectorInput;
	std::deque<int>		dequeInput;

	start = std::clock();
	vectorInput = parseVector(argc, argv);
	_original = vectorInput;
	_vectorResult = toIntVector(fordJohnsonVector(makeVectorItems(vectorInput)));
	end = std::clock();
	_vectorTime = static_cast<double>(end - start) * 1000000.0 / CLOCKS_PER_SEC;

	start = std::clock();
	dequeInput = parseDeque(argc, argv);
	_dequeResult = toIntDeque(fordJohnsonDeque(makeDequeItems(dequeInput)));
	end = std::clock();
	_dequeTime = static_cast<double>(end - start) * 1000000.0 / CLOCKS_PER_SEC;

	printVector("Before: ", _original);
	printVector("After: ", _vectorResult);
	printTime(_original.size(), "vector", _vectorTime);
	printTime(_original.size(), "deque", _dequeTime);
}
