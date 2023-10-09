# **************************************************************************** #
#																			  #
#														 :::	  ::::::::	#
#	Makefile										   :+:	  :+:	:+:	#
#													 +:+ +:+		 +:+	  #
#	By: hnait <hnait@student.42.fr>				+#+  +:+	   +#+		 #
#												 +#+#+#+#+#+   +#+			#
#	Created: 2022/11/12 11:50:23 by hnait 	   		   #+#	#+#			  #
#	Updated: 2023/03/14 17:38:58 by hnait			###   ########.fr		#
#																			  #
# **************************************************************************** #

NAME = get_next_line.a
CC = gcc
FLAGS = -Wall -Werror -Wextra 
AR = ar rc
RM = rm -f
HEAD = get_next_line.h

SRC = get_next_line.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
		$(AR) $(NAME) $(OBJ)

%.o : %.c $(HEAD)
		$(CC) -c $< -o $@ $(FLAGS)

clean:
		$(RM) $(OBJ)

fclean: clean
		$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re