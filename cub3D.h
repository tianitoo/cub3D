# ifndef CUB3D_H
# define CUB3D_H


#include <stdio.h>
#include "MLX42/include/MLX42/MLX42.h"
#include "get_next_line.h"
#include "libft/libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct s_mlx
{
    void    *window;
    void    *context;
    int32_t width;
    int32_t height;
    double  delta_time;
}   t_mlx;

typedef struct s_data
{
    mlx_t *mlx_ptr;
    void			*mlx_win;
	mlx_image_t		*img;
    int *c_tab;
    int *f_tab;
    char *n_texture;
    char *s_texture;
    char *w_texture;
    char *e_texture;
    char **map;
    int x_player;
    int y_player;
    char order;
} t_data;


int     check_the_order_and_path(char *str);
int     file_exist(char  *str);
char    *return_the_path(char *str, int i);
int     check_the_order(char *str);
int     skips_spaces(char *str);
int     check_floor_sky(char* str);
int     check_the_color(char *str);
int     find_the_comma(char * str, int i);
int     ft_isspace(char c);
char    *delete_last_spaces(char *s);
void    free_two_d(char **str);

#endif