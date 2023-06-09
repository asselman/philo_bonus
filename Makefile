# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aasselma <aasselma@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/04 03:59:04 by aasselma          #+#    #+#              #
#    Updated: 2023/06/09 01:27:28 by aasselma         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo_bonus

SRC = philo_bonus.c philo_utils_bonus.c philo_routin_bonus.c

CC = cc

CFLAGS = -Wall -Wextra -Werror 

RM = rm -rf

$(NAME): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(NAME)

# $(NAME): $(OBJ)
# 	$(CC) $(CFLAGS) -fsanitize=thread -g $(SRC) -o $(NAME)

all: $(NAME)

clean:
	@echo "<<<<all files are deleted>>>>"

fclean: clean
	@$(RM) $(NAME)

re:	fclean all
