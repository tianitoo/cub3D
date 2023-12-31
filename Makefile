# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hachahbo <hachahbo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/30 15:29:47 by hnait             #+#    #+#              #
#    Updated: 2023/12/24 17:09:04 by hachahbo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D
CC = cc
FLAGS = -Wall -Wextra -Werror #-fsanitize=address -g
AR = ar -r
RM = rm -f
HEAD = cub3D.h
MK = make
LIBFT = ./libft/libft.a
HEADLIBFT = ./libft/libft.h
BUILD = MLX42/build
GNL = ./gnl/get_next_line.a
MLX = MLX42/build/libmlx42.a  -Iinclude -lglfw -L"/Users/$(USER)/.brew/opt/glfw/lib"


SRC = main.c\
		./horizontal.c\
		./vertical.c\
		./ray.c\
		./mouvements.c\
		./draw.c\
		checkers.c\
		cast_rays.c\
		Cub3d.c\
		c_f_color.c\
		order_path.c\
		check_the_map.c\
		check_the_player.c\
		fill_the_str.c\
		minimalist.c\
		resize_the_map.c\
		fill_the_map.c\
		temp_file.c\
		file_is_empty.c\
		rendring_mouse.c\

LIBFTSRC = ./libft/ft_atoi.c\
		./libft/ft_bzero.c\
		./libft/ft_calloc.c\
		./libft/ft_isalnum.c\
		./libft/ft_isalpha.c\
		./libft/ft_isprint.c\
		./libft/ft_isdigit.c\
		./libft/ft_isascii.c\
		./libft/ft_itoa.c\
		./libft/ft_memchr.c\
		./libft/ft_memcpy.c\
		./libft/ft_memset.c\
		./libft/ft_memcmp.c\
		./libft/ft_memmove.c\
		./libft/ft_split.c\
		./libft/ft_strlcat.c\
		./libft/ft_strlen.c\
		./libft/ft_strnstr.c\
		./libft/ft_strrchr.c\
		./libft/ft_strchr.c\
		./libft/ft_strlcpy.c\
		./libft/ft_strlcat.c\
		./libft/ft_strdup.c\
		./libft/ft_strncmp.c\
		./libft/ft_strlcat.c\
		./libft/ft_strtrim.c\
		./libft/ft_substr.c\
		./libft/ft_tolower.c\
		./libft/ft_toupper.c\
		./libft/ft_strmapi.c\
		./libft/ft_striteri.c\
		./libft/ft_strjoin.c\
		./libft/ft_putchar_fd.c\
		./libft/ft_putstr_fd.c\
		./libft/ft_putendl_fd.c\
		./libft/ft_putnbr_fd.c\
		./libft/libft.h


GNLSRC = ./gnl/get_next_line.c\
		./gnl/get_next_line.h
		


OBJ = $(SRC:.c=.o)

all: $(NAME)

$(BUILD):
	@if [ ! -d MLX42/build ]; then \
		(cd MLX42 && cmake -B build); \
	fi

$(LIBFT): $(LIBFTSRC)
	$(MK) -C ./libft


$(GNL): $(GNLSRC)
	$(MK) -C ./gnl

$(NAME): $(BUILD) $(LIBFT) $(GNL) $(OBJ)
	$(MK) -C MLX42/build
	$(CC) $(OBJ) $(LIBFT) $(GNL)  $(MLX) -o $(NAME)


%.o : %.c $(HEAD)
	$(CC) -Wall -Wextra -Werror -Imlx -c $< -o $@
clean:
	$(RM) $(OBJ)
	$(RM) main.o
	$(MK) clean -C ./libft
	$(MK) clean -C ./gnl

fclean: clean
	$(RM) $(NAME)
	$(RM) $(LIBFT)
	$(RM) $(GNL)
	$(RM) -r MLX42/build

re: fclean all

.PHONY: all bonus clean fclean re