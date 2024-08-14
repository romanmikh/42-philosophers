# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rocky <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/14 16:36:01 by rocky             #+#    #+#              #
#    Updated: 2024/08/14 16:36:03 by rocky            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= philo
CFLAGS	= -Werror -Wall -Wextra -pthread

SRCS	= main.c format_converters.c time.c utils.c handle_actions.c logic.c
OBJS	= ${SRCS:.c=.o}

all: $(NAME)

bonus: $(B_NAME)

%.o: %.c
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

$(B_NAME): $(B_OBJS)
	@$(CC) $(CFLAGS) $(B_OBJS) -o $(B_NAME)

clean:
	@rm -f $(OBJS) $(B_OBJS)

fclean: clean
	@rm -f $(NAME) $(B_NAME)

re: clean all

.PHONY: all, clean, fclean, re
