# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: obelaizi <obelaizi@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/30 03:38:51 by obelaizi          #+#    #+#              #
#    Updated: 2023/05/15 15:51:15 by obelaizi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
FLAGS = -Werror -Wall -Wextra 
#-fsanitize=thread

SRCS = $(wildcard *.c )
OBJS= $(SRCS:.c=.o)


all : $(NAME)

%.o: %.c philo.h 
	cc -c -g $(FLAGS) $< -o $@

	
$(NAME): $(OBJS)
	@cc -g $(OBJS) -o $(NAME) 

clean:
	@rm -f $(OBJS) 

fclean: clean
	@rm -f $(NAME)
	
re: fclean all
