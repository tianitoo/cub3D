/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamza <hamza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 12:02:34 by hamza             #+#    #+#             */
/*   Updated: 2023/11/24 18:41:26 by hamza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <math.h>
#include "MLX42.h"

#define PI 3.14159265359


int main()
{
    // //degree to radians 
    // double degrees;
    // degrees = 57.295780 * 3;
    // printf("degrees  %f \n", degrees);
    // double r = degrees  * (PI / 180);

    // printf("->>>>> %f\n", r);
    
    //distance between rays;
    double  Fov_angle = 60 * (PI /180);
    double NUM_RAYS = 320;
    
    double RayAngle  = 0 ;
    RayAngle += Fov_angle / NUM_RAYS;
    printf("->>>>> %f\n", RayAngle);
        
}