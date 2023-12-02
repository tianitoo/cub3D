# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hnait <hnait@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/30 15:29:47 by hnait             #+#    #+#              #
#    Updated: 2023/12/02 17:38:14 by hnait            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D
CC = cc
FLAGS = -Wall -Wextra -Werror
AR = ar -r
RM = rm -f
HEAD = cub3D.h
MK = make
LIBFT = ./libft/libft.a
HEADLIBFT = ./libft/libft.h
PRINTF = ./ft_printf/ft_printf.a
HEADPRINTF = ./ft_printf/ft_printf.h
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
		parcing_part_one.c\
		parcing_part_two.c\
		parcing_part_three.c\
		parcing_part_four.c\
		parcing_part_five.c\
		parcing_part_six.c\

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

PRINTFSRC = ./ft_printf/ft_printf.c\
		./ft_printf/ft_putchar.c\
		./ft_printf/ft_puthex.c\
		./ft_printf/ft_putnbr.c\
		./ft_printf/ft_putstr.c\
		./ft_printf/ft_putunsignednbr.c\
		./ft_printf/ft_printf.h

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

$(PRINTF): $(PRINTFSRC)
	$(MK) -C ./ft_printf

$(GNL): $(GNLSRC)
	$(MK) -C ./gnl

$(NAME): $(BUILD) $(LIBFT) $(PRINTF) $(GNL) $(OBJ)
	$(MK) -C MLX42/build
	$(CC) $(OBJ) $(LIBFT) $(PRINTF) $(GNL)  $(MLX) -o $(NAME)


%.o : %.c $(HEAD)
	$(CC) -Wall -Wextra -Werror -Imlx -c $< -o $@
clean:
	$(RM) $(OBJ)
	$(RM) main.o
	$(MK) clean -C ./libft
	$(MK) clean -C ./ft_printf
	$(MK) clean -C ./gnl

fclean: clean
	$(RM) $(NAME)
	$(RM) $(LIBFT)
	$(RM) $(PRINTF)
	$(RM) $(GNL)
	$(RM) -r MLX42/build

re: fclean all

.PHONY: all bonus clean fclean re