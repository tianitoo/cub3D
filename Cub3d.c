/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamza <hamza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 19:24:35 by hachahbo          #+#    #+#             */
/*   Updated: 2023/11/09 16:43:00 by hamza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// int main()
// {
//     int a = 0;
//     int b = 0;
//     mlx_t *ptr;
//     mlx_image_t *img;
//     ptr = mlx_init(1000, 1000, "hamza", 1);
//     img = mlx_new_image(ptr, 1000, 1000);
//     while(a < 1000)
//     {
//         b = 0;
//         while(b < 1000)
//         {
//             mlx_put_pixel(img, a, b , 0xe5555FF);
//             b++;
//         }
//         a++;
//     }
//     mlx_image_to_window(ptr, img, 0, 0);
//     mlx_loop(ptr);
// }

int ft_isspace(char c)
{

    if (c == ' ' || c == '\t' 
    || c == '\n' || c == '\v' 
    || c == '\f' || c == 
    '\r' || c == '\0')
        return (1);
    return (0);
}

int check_the_map(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        
        if (str[i] != '0' && str[i] != '1' 
        && str[i] != 'S' && str[i] != 'N' 
        && str[i] != 'W' && str[i] != 'E' 
        && !ft_isspace(str[i]))
            return (0);
        i++;
    }
    return (1);
}
int check_the_map_is_valid(char **str, int x, int i)
{
    int j;
    int l;

    l = i;
    while (str[i])
    {
        if (!check_the_map(str[i]))
            return (0);
        i++;
    }
    i = l;
    j = 0;
    while (str[i][j] != '\n' )
    {
        if (str[i][j] != '1' && !ft_isspace(str[i][j]))
            return (0);
        j++;
    }
    i++;
    j = 0;
    while (i < x - 1)
    {
        j = skips_spaces(str[i]);
        if (str[i][j] != '1')
            return (0);
        while (str[i][j] != '\n')
            j++;
        j--;
        while (str[i][j] != '1')
        {
            if (str[i][j] == '0' || str[i][j] == 'S' || str[i][j] == 'N' || str[i][j] == 'W' || str[i][j] == 'E')
                return (0);
            if (ft_isspace(str[i][j]))
                j--;
        }
        i++;
    }
    j = 0;
    while (str[i][j] != '\0')
    {
        if (str[i][j] != '1' && !ft_isspace(str[i][j]))
            return (0);
        j++;
    }
    return (1);
}
int check_is_one_player(char **str, int x, char c, int i)
{
    int j;
    int l;
    
    j = 0;
    l = 0;
    if(c == '0')
        return (1);
    while (i < x - 1)
    {
        j = 0;
        while (str[i][j] != '\n')
        {
            if (str[i][j] == c)
                l++;
            j++;
        }
        i++;
    }
    if(l > 1)
        return(0);
    return (1);
}

int check_is_only_one_order(char **str, int x, char c, int i)
{

   int j;
    int l;
    
    j = 0;
    l = 0;
    if(c == '0')
        return (1);
    while (i < x - 1)
    {
        j = 0;
        while (str[i][j] != '\n')
        {
            if (str[i][j] == 'N' || str[i][j] == 'W'
                || str[i][j] == 'E' || str[i][j] == 'S')
            {
                l++;
            }
            j++;
        }
        i++;
    }
    if(l > 1)
        return(0);
    return (1);   
}
int check_element_is_valid(char **str, int x, char c, int i)
{
    int j;
    int l;
    
    i++;
    l = i;
    j = 0;
    while (i < x - 1)
    {
        j = 0;
        while (str[i][j] != '\n')
        {
            if (str[i][j] == c)
            {
                if(ft_isspace(str[i][j - 1]) || ft_isspace(str[i][j + 1]))
                    return 0;
                if (ft_isspace(str[i - 1][j]) || ft_isspace(str[i + 1][j]))
                    return (0);                
            }
            j++;
        }
        i++;
    }
    if(!check_is_one_player(str, x, c, l))
        return (0);
    if(!check_is_only_one_order(str, x, c , l))
        return (0);
    return (1);
}

int check_the_player_is_valid(char **str, int x, int i)
{

    if(!check_element_is_valid(str, x, '0', i))
        return (0);
    if(!check_element_is_valid(str, x, 'N', i))
        return (0);
    if(!check_element_is_valid(str, x, 'E', i))
        return (0);
    if(!check_element_is_valid(str, x, 'W', i))
        return (0);
    if(!check_element_is_valid(str, x, 'S', i))
        return (0);
    return (1);
}
int the_map(char **str, int x, int i)
{
    if (!check_the_map_is_valid(str, x, i))
        return (0);
    if(!check_the_player_is_valid(str, x, i))
        return (0);
    return (1);
}
int check_the_first_of_map(char **str, int i)
{
    int j;

    j = 0;
    if(!str[i])
        return(0);
    while (str[i][j] != '\n')
    {
        if (str[i][j] != '1' && !ft_isspace(str[i][j]))
            return (0);
        j++;
    }
    return (1);
}
char *fill_the_str_to_check(char *str)
{
    char *s;
    int i;
    int j;
    
    i = check_the_order(str);
    s = malloc(i + 1);
    j = 0;
    while(j < i)
    {
        s[j] = str[j];
        j++;
    }
    s[j] = '\0';
    return (s);
}
int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2 [i])
		i++;
	return (s1[i] - s2[i]);
}

int check_the_orders_is_valid(char **str)
{
    int i;
    char *s;
    char *st;
    int j;

    i = 0;
    j = 0;
    while(str[i])
    {
        if(check_the_first_of_map(str, i))
            break;
        s = fill_the_str_to_check(str[i]);
        j = i + 1;
        while(str[j])
        {
            if(check_the_first_of_map(str, j))
                break;
            st = fill_the_str_to_check(str[j]);
            if(!ft_strcmp(st, s))
                return(0);
            j++;
        }
        i++;
    }
    return(1);
}
int the_minimalist(char **str, int x) 
{
    int i;

    i = 0;
    while(!check_the_first_of_map(str, i))
    {
        if(!str[i])
            return(0);
        if(!check_the_order_and_path(str[i]) && !check_floor_sky(str[i]))
            return(0);
        i++;
    }
    if(!check_the_orders_is_valid(str))
        return (0);
    if(!the_map(str, x, i))
        return(0);
    return (1);
}

int check_and_skip_spaces(char *str)
{
    int i;

    i = skips_spaces(str);
    if(str[i] == '\n' || str[i] != '\0')
        return(1);
    return (0);
}

int count_the_lines(void)
{
    char *str;
    int i = 0;

    int fd = open("order", O_CREAT | O_RDWR, 0666);

    str = get_next_line(fd);
    while (str)
    {
        if (check_and_skip_spaces(str))
            i++;
        str = get_next_line(fd);
    }
    close(fd);
    return (i);
}
char **fill_string(int i)
{
    char *str;
    char **strs;

    int fd = open("order", O_CREAT | O_RDWR, 0666);
    strs = (char **)malloc((i + 1) * sizeof(char *));
    str = get_next_line(fd);
    i = 0;
    while (str)
    {
        if (check_and_skip_spaces(str))
        {
            strs[i] = str;
            i++;
        }
        str = get_next_line(fd);
    }
    strs[i] = NULL;
    close(fd);
    return (strs);
}

int *return_color(char *str, int i)
{
    char *st = return_the_path(str, i);
    char **d_str;
    int *tab;
    int j;
    tab = malloc(sizeof(int) * 3);
    d_str = ft_split(st, ',');
    j = 0;
    while(j < 3) 
    {
        tab[j] = ft_atoi(d_str[j]);
        j++;
    }
    return(tab);
       
}
void fill_order_and_path(t_data *data, char *str)
{
    int i;

    i = skips_spaces(str);
    if(str[i] == 'N' && str[i + 1] == 'O' && ft_isspace(str[i+2]))
        data->n_texture = return_the_path(str, i + 2);
    else if(str[i] == 'S' && str[i + 1] == 'O' && ft_isspace(str[i+2]))
        data->s_texture = return_the_path(str, i + 2);
    else if(str[i] == 'W' && str[i + 1] == 'E' && ft_isspace(str[i+2]))
        data->w_texture = return_the_path(str, i + 2);
    else if(str[i] == 'E' && str[i + 1] == 'A' && ft_isspace(str[i+2]))
        data->e_texture = return_the_path(str, i + 2);
    else if(str[i] == 'C' && ft_isspace(str[i + 1]))
        data->c_tab = return_color(str, i + 1);
    else if(str[i] == 'F' && ft_isspace(str[i + 1]))
        data->f_tab = return_color(str, i + 1);
}

char **fill_the_map(char **str, int i)
{
    int j;
    char **d_str;
    
    j = i;
    while(str[i])
        i++;
    d_str = malloc(sizeof(char *) *  i + 1);
    i = j;
    j = 0;
    while(str[i])
    {
        d_str[j] = ft_strdup(str[i]);
        i++;
        j++;
    }
    d_str[j] = NULL;
    return(d_str);
    
}

int cor_of_player(t_data *data)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while(data->map[i])
    {
        j = 0;
        while(data->map[i][j])
        {
            if(data->map[i][j] == 'N' || data->map[i][j] == 'E'
                || data->map[i][j] == 'W' || data->map[i][j] == 'S')
            {
                data->x_player = j;
                data->y_player = i;
                data->order = data->map[i][j];
                return(1);
            }
            j++;
        }  
        i++;
    }
    return(0);
}
void init_data(t_data *data)
{
    data->c_tab = NULL;
    data->f_tab = NULL;
    data->e_texture = 0;
    data->n_texture = 0;
    data->w_texture = 0;
    data->s_texture = 0;
    data->order = 0;
    data->x_player = 0;
    data->y_player = 0;
    data->map = NULL;
}
int  inits_the_data(t_data *data, char **str)
{
    int i;

    i = 0;
    init_data(data);
    while(!check_the_first_of_map(str, i))
    {
        fill_order_and_path(data, str[i]);
        i++;
    }
    data->map = fill_the_map(str, i);
    if(!cor_of_player(data))
        return(0);
    return(1);
}
void display_data(t_data data)
{
    int i;

    i = 0;
    printf("DATA : \n");
    printf("NO ->>>> %s\n", data.n_texture);
    printf("EA ->>>> %s\n", data.e_texture);
    printf("SO ->>>> %s\n", data.s_texture);
    printf("WE ->>>> %s\n", data.w_texture);
    printf("\nC : ");
    while(i < 3)
    {
        printf(" %d |", data.c_tab[i]);
        i++;
    }
    i = 0;
    printf("\nF  : ");
    while(i < 3)
    {
        printf(" %d |", data.f_tab[i]);
        i++;
    }
    i = -1;
    printf("\n\n MAP : \n");
    while(data.map[++i])
        printf("%s", data.map[i]);
    printf("\n\nthe type  : %c \n", data.order);
    printf("Coordinate of player x : %d\n", data.x_player);
    printf("Coordinate of player y : %d\n", data.y_player);
}
int fail_the_inits(t_data data)
{
    if(!data.e_texture)
        return(0);
    else if(!data.n_texture)
        return(0);
    else if(!data.s_texture)
        return(0);
    else if(!data.w_texture)
        return(0);
    else if(!data.c_tab)
        return(0);
    else if(!data.f_tab)
        return(0);
    else if(!data.map)
        return(0);
    else if(!data.order)
        return(0);
    else if(!data.x_player)
        return(0);
    else if(!data.y_player)
        return(0);
    return(1);
}
int main()
{
    int j = count_the_lines();
    char **str = fill_string(j);
    t_data data;

    if(!the_minimalist(str, j))
    {
        printf("NOT VALID\n");
        return(0);
    }
    if(!inits_the_data(&data, str))
    {
        printf("NOT VALID\n");
        return(0);
    }
    if(!fail_the_inits(data))
    {
        printf("NOT VALID\n");
        return(0);
    }
    else
    {
        printf("VALID\n");
        display_data(data);
    }
    data;
    
    return (0);
}