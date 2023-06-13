# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: asousa-n <asousa-n@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/06 12:28:18 by asousa-n          #+#    #+#              #
#    Updated: 2023/05/06 16:19:56 by asousa-n         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc -pthread
CFLAGS = -Wall -Wextra -Werror -fsanitize=thread
RM = rm -rf

NAME = philo

SRCS =	philo.c \
	verific.c\
	init.c\
	control_death.c \
	time.c \
	routine.c \
	destroy.c\

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o philo

clean:
	$(RM) $(OBJS)
	
fclean: clean
	$(RM) $(NAME)
	
re: fclean all

run: all clean

.PHONY: all clean fclean re run

.SILENT:
