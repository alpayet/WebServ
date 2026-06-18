.PHONY : all debug clean fclean re

# files
SRC_FILES = main.cpp Server.cpp \
	reactor/Reactor.cpp \
	reactor/demultiplexer/EpollDemultiplexer.cpp \
	reactor/demultiplexer/KqueueDemultiplexer.cpp \
	event_handler/TcpListenerHandler.cpp event_handler/TcpListenerFactory.cpp event_handler/ConnectionHandler.cpp \
	transport/Socket.cpp transport/TcpTransport.cpp \
	transport/endpoint/build_endpoints.cpp transport/endpoint/TcpEndpoint.cpp \
	protocol/TestProtocol.cpp \
	config/ServerConfig.cpp \
	utils/utils.cpp

# directories
SRC_DIR = src/
OBJ_DIR = obj/

# files full paths
SRC = $(addprefix $(SRC_DIR), $(SRC_FILES))
OBJ = $(addprefix $(OBJ_DIR), $(SRC_FILES:.cpp=.o))
DEP = $(addprefix $(OBJ_DIR), $(SRC_FILES:.cpp=.d))

NAME = webserv

CC = c++
CFLAGS = -Wall -Wextra -Wconversion -Wsign-conversion -Weffc++ -MMD -MP -std=c++98 -g
CFLAGS += $(EXTRA_FLAGS)
IFLAGS = -I $(SRC_DIR)

DEBUG_VALGRIND = valgrind --leak-check=full --show-leak-kinds=all -s

all : $(NAME)

$(NAME) : $(OBJ)
	$(CC) $(OBJ) -o $@

$(OBJ_DIR)%.o : $(SRC_DIR)%.cpp Makefile
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@

-include $(DEP)

debug : all
	$(DEBUG_VALGRIND) ./$(NAME) $(ARGS)

clean :
	rm -rf $(OBJ_DIR)

fclean : clean
	rm -f $(NAME)

re : fclean all
