# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: obelaizi <obelaizi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/30 03:38:51 by obelaizi          #+#    #+#              #
#    Updated: 2023/06/21 12:26:42 by obelaizi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
FLAGS = -Werror -Wall -Wextra

SRCS = free_all.c main.c mainHelper.c mainHelper1.c
OBJS= $(SRCS:.c=.o)


all : $(NAME)

%.o: %.c philo.h 
	cc -c -g $(FLAGS) $< -o $@

$(NAME): $(OBJS)
	cc -g  $(FLAGS) $(OBJS) -o $(NAME) 

clean:
	@rm -f $(OBJS) 

fclean: clean
	@rm -f $(NAME)
	
re: fclean all
