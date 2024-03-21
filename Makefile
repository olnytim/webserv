NAME = webserv

FLAGS = -Wall -Wextra -Werror -std=c++98 -g #-fsanitize=address
CC = c++

PREF_SRC = src
PREF_OBJ = obj
PREF_HEADER = includes
PARSING_PATH = parsing
PARSING_HEADER = $(PREF_HEADER)/$(PARSING_PATH)
PARSING_SRC = $(addprefix $(PARSING_PATH)/, config.cpp ServerBlock.cpp LocationBlock.cpp)

SRC = $(addprefix $(PREF_SRC)/, main.cpp $(PARSING_SRC))
OBJ = $(patsubst $(PARSING_HEADER)/%.cpp $(PREF_SRC)/%.cpp, $(PREF_OBJ)/%.o, $(SRC))
HEADER = $(wildcard $(PARSING_HEADER)/*.hpp)

all: $(NAME)
	@echo > /dev/null

$(NAME): $(OBJ)
	@$(CC) $(FLAGS) $(OBJ) -o $(NAME)
	@echo "$(NAME) file was created!"
	@rm -rf webserv.dSYM


$(PREF_OBJ)/%.o: $(PREF_SRC)/%.cpp $(HEADER) Makefile
	@mkdir -p $(PREF_OBJ)
	@if [ ! -e $(NAME) ]; then \
		$(CC) $(FLAGS) -c $< -o $@; \
	else \
		$(CC) $(FLAGS) -c $< -o $@; \
		echo "$(SRC) $(HEADER) or Makefile files were updated!"; \
	fi

clean:
	@if [ -d $(PREF_OBJ) ]; then \
		rm -rf $(PREF_OBJ); \
		echo "$(PREF_OBJ) was deleted!"; \
	fi

fclean: clean
	@if [ -e $(NAME) ]; then \
		rm -rf $(NAME); \
		echo "$(NAME) was deleted!"; \
	fi

re:	fclean all

.PHONY: all clean fclean re