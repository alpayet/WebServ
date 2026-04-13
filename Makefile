.PHONY : all debug clean fclean re

#files
SRC_FILES = \
	main.cpp \

#directories
SRC_DIR = src/

OBJ_DIR = obj/
INC_DIR = inc/

#files full paths
SRC = $(addprefix $(SRC_DIR), $(SRC_FILES))
OBJ = $(addprefix $(OBJ_DIR), $(SRC_FILES:.cpp=.o))
DEP = $(addprefix $(OBJ_DIR), $(SRC_FILES:.cpp=.d))

NAME = webserv

CC = c++
CFLAGS = -Wall -Wextra -Werror -Wconversion -Wsign-conversion -Weffc++ -MMD -MP -std=c++98
IFLAGS = -I $(INC_DIR)
MAKE = @make --no-print-directory -j

DEBUG_VALGRIND = valgrind --leak-check=full --show-leak-kinds=all -s

all : $(NAME)

$(NAME) : $(OBJ)
	$(CC) $(OBJ) -o $@

$(OBJ_DIR)%.o : $(SRC_DIR)%.cpp Makefile | $(OBJ_DIR)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@

$(OBJ_DIR) :
	@mkdir $@

-include $(DEP)

debug : all
	$(DEBUG_VALGRIND) ./$(NAME) $(ARGS)

clean :
	rm -rf $(OBJ_DIR)

fclean : clean
	rm -f $(NAME)

re: fclean all
