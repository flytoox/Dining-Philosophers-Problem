# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: obelaizi <obelaizi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/30 03:38:51 by obelaizi          #+#    #+#              #
#    Updated: 2023/03/30 03:39:15 by obelaizi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
FLAGS = -Werror -Wall -Wextra

SRCS = $(wildcard ./Bonus/*.c ./gnl/*.c)
OBJS= $(SRCS:.c=.o)


all : $(NAME)

%.o: %.c ./philo/philo.h 
	cc -c -g $(FLAGS) $< -o $@

	
$(NAME): $(OBJS)
	@cc -g $(OBJS) -o $(NAME) 

clean:
	@rm -f $(OBJS) 

fclean:clean
	@rm -f $(NAME)
	
re: fclean all