#ifndef PMERGEME_HPP
# define PMERGEME_HPP

# include <cstddef>
# include <ctime>
# include <deque>
# include <iostream>
# include <stdexcept>
# include <string>
# include <vector>

class PmergeMe
{
	private:
		struct Item
		{
			int			value;
			std::size_t	id;
		};

		struct Pair
		{
			Item	winner;
			Item	loser;
		};

		std::vector<int>	_original;
		std::vector<int>	_vectorResult;
		std::deque<int>		_dequeResult;
		double				_vectorTime;
		double				_dequeTime;

		static int					parseNumber(const std::string& text);
		static std::vector<int>		parseVector(int argc, char **argv);
		static std::deque<int>		parseDeque(int argc, char **argv);
		static std::vector<int>		jacobsthalOrder(std::size_t size);

		static std::vector<Item>		makeVectorItems(const std::vector<int>& input);
		static std::deque<Item>		makeDequeItems(const std::deque<int>& input);
		static std::vector<int>		toIntVector(const std::vector<Item>& items);
		static std::deque<int>		toIntDeque(const std::deque<Item>& items);

		static std::vector<Item>		fordJohnsonVector(std::vector<Item> items);
		static std::deque<Item>		fordJohnsonDeque(std::deque<Item> items);

		static std::size_t			findVectorItem(const std::vector<Item>& items,
									 std::size_t id);
		static std::size_t			findDequeItem(const std::deque<Item>& items,
									 std::size_t id);
		static std::size_t			vectorInsertPosition(const std::vector<Item>& items,
									 int value, std::size_t limit);
		static std::size_t			dequeInsertPosition(const std::deque<Item>& items,
									 int value, std::size_t limit);

		static void					printVector(const std::string& text,
									 const std::vector<int>& values);
		static void					printDeque(const std::string& text,
									 const std::deque<int>& values);
		static void					printTime(std::size_t size,
									 const std::string& container, double us);

	public:
		PmergeMe();
		PmergeMe(const PmergeMe& orig);
		PmergeMe&	operator=(const PmergeMe& orig);
		~PmergeMe();

		void	process(int argc, char **argv);
};

#endif
