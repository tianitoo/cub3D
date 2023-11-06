# ifndef CUB3D_H
# define CUB3D_H


#include <stdio.h>
#include "MLX42/include/MLX42/MLX42.h"
#include "get_next_line.h"
#include "libft/libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


int check_the_order_and_path(char *str);
int file_exist(char  *str);
char *return_the_path(char *str, int i);
int check_the_order(char *str);
int skips_spaces(char *str);
int check_floor_sky(char* str);
int check_the_color(char *str);
int find_the_comma(char * str, int i);
int ft_isspace(char c);

#endif