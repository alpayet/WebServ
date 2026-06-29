# .PHONY: all clean fclean re

# NAME := webserv

# SRCS_DIR := src/
# CONF_DIR := src/config/
# SERV_DIR := src/server/
# STOR_DIR := src/infrastructure/storage/file_system/
# INCS_DIR := inc/
# OBJS_DIR := .build/

# SRCS := $(addprefix $(SRCS_DIR),main.cpp)
# SRCS += $(addprefix $(CONF_DIR), Config.cpp Tokenizer.cpp Parser.cpp Semantic.cpp)
# SRCS += $(addprefix $(SERV_DIR), Server.cpp)
# SRCS += $(addprefix $(STOR_DIR), Storage.cpp Reader.cpp fdReader.cpp Exception.cpp)
# INCS := $(INCS_DIR)
# OBJS := $(addprefix $(OBJS_DIR), $(SRCS:%.cpp=%.o))
# DEPS := $(OBJS:.o=.d)

# SRCS := $(addprefix $(SERIAL_DIR), $(SERIAL_CL))

# CXX := c++
# CXXFLAGS := -Wall -Wextra -Werror -std=c++98
# CPPFLAGS := $(addprefix -I,$(INCS)) -MMD -MP
# MAKEFLAGS += --no-print-directory

# all: $(NAME)

# $(NAME): $(OBJS)
# 	$(CXX) $(CXXFLAGS) $(OBJS) -o $@

# $(OBJS_DIR)%.o: %.cpp
# 	@mkdir -p $(dir $@)
# 	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $< -o $@

# -include $(DEPS)

# clean:
# 	rm -rf $(OBJS_DIR)

# fclean:
# 	rm -rf $(OBJS_DIR)
# 	rm -f $(NAME)

# re: fclean
# 	$(MAKE) all

# /**

.PHONY : all debug clean fclean re

#files
SRC_FILES = \
	main.cpp \
	server/Server.cpp \
	infrastructure/storage/file_system/TempWriter.cpp \
	infrastructure/storage/file_system/Storage.cpp \
	infrastructure/storage/file_system/Reader.cpp \
	infrastructure/storage/file_system/Exception.cpp \
	infrastructure/storage/file_system/constants.cpp \
	infrastructure/http/statusReason.cpp \
	infrastructure/http/methods.cpp \
	infrastructure/http/Handler.cpp \
	infrastructure/http/Context.cpp \
	infrastructure/http/constants.cpp \
	infrastructure/http/router/Router.cpp \
	infrastructure/http/response/Sender.cpp \
	infrastructure/http/response/ResponseBuilder.cpp \
	infrastructure/http/response/Response.cpp \
	infrastructure/http/response/HeaderBlockSerializer.cpp \
	infrastructure/http/request/Request.cpp \
	infrastructure/http/request/Parser.cpp \
	infrastructure/http/request/BodyFile.cpp \
	infrastructure/http/presenters/success_lookup.cpp \
	infrastructure/http/presenters/ServeStaticResourcePresenter.cpp \
	infrastructure/http/presenters/DeleteStaticResourcePresenter.cpp \
	infrastructure/http/mappers/ServeStaticResourceDtoMapper.cpp \
	infrastructure/http/mappers/DeleteStaticResourceDtoMapper.cpp \
	infrastructure/http/exceptions/Exception.cpp \
	infrastructure/http/controllers/ServeStaticResourceController.cpp \
	infrastructure/http/controllers/DeleteStaticResourceController.cpp \
	domain/Exception.cpp \
	domain/value_objects/ResourceMetaData.cpp \
	domain/entities/StaticResource.cpp \
	domain/entities/DynamicResource.cpp \
	config/Tokenizer.cpp \
	config/Semantic.cpp \
	config/Parser.cpp \
	config/Config.cpp \
	application/Exception.cpp \
	application/use_cases/serve_static_resource/ServeStaticResource.cpp \
	application/use_cases/delete_static_resource/DeleteStaticResource.cpp \
# 	application/use_cases/execute_dynamic_resource/ExecuteDynamicResource.cpp \
	infrastructure/http/presenters/ExecuteDynamicResourcePresenter.cpp \
	infrastructure/http/mappers/ExecuteDynamicResourceDtoMapper.cpp \
	infrastructure/http/controllers/ExecuteDynamicResourceController.cpp

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
CFLAGS = -Wall -Wextra -MMD -MP -std=c++98
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