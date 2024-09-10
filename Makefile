NAME = webserv
#
FLAGS = -Wall -Wextra -Werror -std=c++98 -g #-fsanitize=address
CC = c++
#
PREF_SRC = srcs
PREF_OBJ = obj
PREF_HEADER = includes
#
PARSING_PATH = parsing
PARSING_HEADER = $(PREF_HEADER)/$(PARSING_PATH)
PARSING_SRC = $(addprefix $(PARSING_PATH)/, Config.cpp ServerBlock.cpp ServerBlockKeymap.cpp LocationBlock.cpp LocationBlockKeymap.cpp)
#
SOCKETS_PATH = sockets
SOCKETS_HEADER = $(PREF_HEADER)/$(SOCKETS_PATH)
SOCKETS_SRC = #$(addprefix $(SOCKETS_PATH)/, WebServer.cpp SocketListener.cpp DataStorage.cpp)
SOCKETS_SRC = $(addprefix $(SOCKETS_PATH)/, web.cpp cli.cpp req.cpp res.cpp)
#
REQUEST_PATH = request
REQUEST_HEADER = #$(PREF_HEADER)/$(REQUEST_PATH)
REQUEST_SRC = #$(addprefix $(REQUEST_PATH)/, Request.cpp RequestParsing.cpp)
#
HEADER_FILE = $(PREF_HEADER)/Headers.hpp
HEADER_FILE += $(PREF_HEADER)/Mime.hpp
#
SRC = $(addprefix $(PREF_SRC)/, main.cpp Mime.cpp Utils.cpp $(SOCKETS_SRC) $(PARSING_SRC) $(REQUEST_SRC))
OBJ = $(patsubst $(PREF_SRC)/%.cpp \
		$(PREF_SRC)/$(PARSING_PATH)/%.cpp \
		$(PREF_SRC)/$(SOCKETS_PATH)/%.cpp, \
		$(PREF_OBJ)/%.o \
		$(PREF_SRC)/$(PARSING_PATH)/%.o \
		$(PREF_SRC)/$(SOCKETS_PATH)/%.o, \
		$(SRC))
#
#OBJ = $(patsubst $(PREF_SRC)/%.cpp \
#		$(PREF_SRC)/$(PARSING_PATH)/%.cpp \
#		$(PREF_SRC)/$(SOCKETS_PATH)/%.cpp \
#		$(PREF_SRC)/$(REQUEST_PATH)/%.cpp, \
#		$(PREF_OBJ)/%.o \
#		$(PREF_SRC)/$(PARSING_PATH)/%.o \
#		$(PREF_SRC)/$(SOCKETS_PATH)/%.o \
#		$(PREF_SRC)/$(REQUEST_PATH)/%.o, \
#		$(SRC))
#
HEADER = $(wildcard $(PARSING_HEADER)/*.hpp)
HEADER += $(wildcard $(SOCKETS_HEADER)/*.hpp)
HEADER += $(wildcard $(REQUEST_HEADER)/*.hpp)
HEADER += $(wildcard $(PREF_HEADER)/*.hpp)
HEADER += $(HEADER_FILE)
#
all: $(NAME)
	@echo > /dev/null
#
$(NAME): $(OBJ)
	@$(CC) $(FLAGS) $(OBJ) -o $(NAME)
	@echo "$(NAME) file was created!"
	@rm -rf webserv.dSYM
#
$(PREF_OBJ)/%.o: $(PREF_SRC)/%.cpp $(HEADER) Makefile
	@mkdir -p $(PREF_OBJ)
	@if [ ! -e $(NAME) ]; then \
		$(CC) $(FLAGS) -c $< -o $@; \
	else \
		$(CC) $(FLAGS) -c $< -o $@; \
		echo "$(SRC) $(HEADER) or Makefile files were updated!"; \
	fi
#
clean:
	@if [ -d $(PREF_OBJ) ]; then \
		rm -rf $(PREF_OBJ); \
		echo "$(PREF_OBJ) was deleted!"; \
	fi
#
fclean: clean
	@if [ -e $(NAME) ]; then \
		rm -rf $(NAME); \
		echo "$(NAME) was deleted!"; \
	fi
#
re:	fclean all
#
.PHONY: all clean fclean re