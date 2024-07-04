# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rocky <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/04 11:18:41 by rocky             #+#    #+#              #
#    Updated: 2024/07/04 11:22:48 by rocky            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Program
NAME			=	philo

# Commands
COMPILER		=	cc
DFLAGS			=	-g3 -gdwarf-2
CFLAGS			=	-Wall -Wextra -Werror $(DFLAGS)
AR			=	ar rcs
RM			=	rm -rf
MAKEFLAGS 		+= 	--silent

# Structure
LIB_DIR					=	./lib
LIBFT					=	$(LIB_DIR)/libft/libft.a

SRC_DIR					=	./src
INCLUDES				=	-I./inc \
							-I $(LIB_DIR)/libft/inc \
MAIN_SOURCE				=	$(wildcard $(SRC_DIR)/*.c)
SOURCES					=	$(MAIN_SOURCE)

# Building
BUILD_DIR				=	./build
MAIN_OBJECT				=	$(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/src/%.o, $(MAIN_SOURCE))

OBJECTS					=	$(MAIN_OBJECT)

# Processing
all: $(NAME)

$(NAME): $(LIBFT) $(OBJECTS)
	@$(COMPILER) $(CFLAGS) $(OBJECTS) $(INCLUDES) $(LIBFT) -o $@ $(READLINE)
	@echo "$(GREEN)minishell compiled$(DEF_COLOR)"
	
$(BUILD_DIR)/src/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	@$(COMPILER) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT):
	@cd $(LIB_DIR)/libft -s && make -s

bonus: $(NAME)
	@echo "$(CYAN)bonus $(YELLOW)features $(MAGENTA)enabled$(DEF_COLOR)"

clean:
	@$(RM) $(BUILD_DIR)
	@$(RM) valgrind-out.txt
	@cd $(LIB_DIR)/libft && make clean
	@echo "$(GRAY)files.o removed$(DEF_COLOR)"
	
fclean: clean
	@$(RM) $(NAME)
	@rm -f test
	@cd $(LIB_DIR)/libft && make fclean
	@echo "$(RED)minishell removed$(DEF_COLOR)"

re: fclean
	@make

valgrind: $(NAME)
	@valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --suppressions=readline.supp --log-file=valgrind-out.txt ./minishell

.PHONY: all bonus clean fclean re test
