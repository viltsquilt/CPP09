NAME = RPN
CXX = c++
CFLAGS = -std=c++20 -Wall -Wextra -Werror
SRCS = main.cpp RPN.cpp

O_DIR = objects

OBJS = $(addprefix $(O_DIR)/,$(SRCS:.cpp=.o))

all: $(NAME)

$(NAME): $(OBJS)
	@$(CXX) $(CFLAGS) $(OBJS) -o $(NAME)

$(O_DIR):
		mkdir -p $@

$(O_DIR)/%.o: %.cpp | $(O_DIR)
		$(CXX) $(CFLAGS) -c $< -o $@
clean:
		@rm -rf $(O_DIR)

fclean: clean
		@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re  
