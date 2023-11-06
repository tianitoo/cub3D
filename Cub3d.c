/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamza <hamza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 19:24:35 by hachahbo          #+#    #+#             */
/*   Updated: 2023/11/06 20:52:52 by hamza            ###   ########.fr       */
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

    if (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r' || c == '\0')
        return (1);
    return (0);
}

int check_the_map(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        
        if (str[i] != '0' && str[i] != '1' && str[i] != 'S' && str[i] != 'N' && str[i] != 'W' && str[i] != 'E' && !ft_isspace(str[i]))
        {
            return (0);
        }
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
        printf("%s", str[i]);
        if (!check_the_map(str[i]))
            return (0);
        i++;
    }
    i = l;
    j = 0;
    while (str[i][j] != '\n')
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
        // printf("->>>>>>>>>>>>>%s\n",s);
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
    while(str[i])
    {
        if(check_the_first_of_map(str, i))
            break;
        printf("%s", str[i]);
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

int main()
{
    int j = count_the_lines();
    char **str = fill_string(j);

    if(!the_minimalist(str, j))
        printf("\nnot valid\n");
    else
        printf("\nvalid\n");
    return (0);
}