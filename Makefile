.PHONY: all clean fclean re

NAME := test.out

SRCS_DIR := src/
INCS_DIR := inc/
OBJS_DIR := .build/

SRCS := $(addprefix $(SRCS_DIR), Parser.cpp Tokenizer.cpp main.cpp)
INCS := $(INCS_DIR)
OBJS := $(addprefix $(OBJS_DIR), $(SRCS:%.cpp=%.o))
DEPS := $(OBJS:.o=.d)

SRCS := $(addprefix $(SERIAL_DIR), $(SERIAL_CL))

CXX := c++
CXXFLAGS := -Wall -Wextra -Werror -std=c++98
CPPFLAGS := $(addprefix -I,$(INCS)) -MMD -MP
MAKEFLAGS += --no-print-directory

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $@

$(OBJS_DIR)%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $< -o $@

-include $(DEPS)

clean:
	rm -rf $(OBJS_DIR)

fclean:
	rm -rf $(OBJS_DIR)
	rm -f $(NAME)

re: fclean
	$(MAKE) all
