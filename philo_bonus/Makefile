# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: obelaizi <obelaizi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/30 03:38:51 by obelaizi          #+#    #+#              #
#    Updated: 2023/06/21 12:27:09 by obelaizi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo_bonus
FLAGS =  -Werror -Wextra -Wall

SRCS = free_all.c main.c mainHelper.c mainHelper1.c
OBJS= $(SRCS:.c=.o)


all : $(NAME)

%.o: %.c philo_bonus.h 
	cc -c -g $(FLAGS) $< -o $@

$(NAME): $(OBJS)
	cc -g  $(FLAGS) $(OBJS) -o $(NAME) 

clean:
	@rm -f $(OBJS) 

fclean: clean
	@rm -f $(NAME)
	
re: fclean all
