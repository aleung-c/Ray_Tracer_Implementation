/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadows_inner.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/12 14:26:41 by aleung-c          #+#    #+#             */
/*   Updated: 2016/05/12 14:26:45 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "RTv1.h"
#include <stdio.h> //

void	calculate_inner_shadows(t_rt *rt)
{
	// parcours les obj et trace des rayons du point d'intersection vers les lights
	int i;
	int screen_size;

	i = 0;
	screen_size = rt->screen_height * rt->screen_width;

	while (i < screen_size) // pour chaque ligne de pixel.
	{
		// pour chaque viewport vector.
		run_trough_lights_inner_shadows(rt, &(rt->vp_vectors[i]));
		i++;
	}
}

void		run_trough_lights_inner_shadows(t_rt *rt, t_screen_vec *vp_vector)
{
	t_light		*cur_light;
	float		distance_to_light;
	float		normalized_distance_to_light;
	t_rgb		rgb_color;
	int 		obj_color;
	double		color_incval_precise;
	int 		color_incval;
	int 		color_to_set;

	cur_light = rt->scene_lights;
	// parcourir toutes les lights.
	while (cur_light)
	{
		// pour chaque light.
		if (vp_vector->touched_objs_list != NULL)
		{
			distance_to_light = distance(vp_vector->touched_objs_list->point, cur_light->pos);
			if (distance_to_light < cur_light->light_power_distance)
			{
				normalized_distance_to_light = 
					distance_to_light / cur_light->light_power_distance;
				//printf("%f\n", normalized_distance_to_light);
				// jusqu'ici, ok !
				// conversion couleur hexa en rgb;
				obj_color = vp_vector->touched_objs_list->color;
				//printf("%#08x\n", obj_color); 
				rgb_color.r = (((obj_color >> 16) & 0xFF));
				rgb_color.g = (((obj_color >> 8) & 0xFF));
				rgb_color.b = (((obj_color) & 0xFF));

				//printf("%dr %dg %db\n", rgb_color.r, rgb_color.g, rgb_color.b);
				color_incval_precise = (normalized_distance_to_light) * 255.0;
				color_incval = (int)floor(color_incval_precise);
				//printf("inc color %d\n", color_incval);
				// add color;
				rgb_color.r -= color_incval;
				rgb_color.g -= color_incval;
				rgb_color.b -= color_incval;

				if (rgb_color.r < 0) 
				{
					rgb_color.r = 0;
				}
				if (rgb_color.g < 0) 
				{
					rgb_color.g = 0;
				}
				if (rgb_color.b < 0) 
				{
					rgb_color.b = 0;
				}

				/*if (rgb_color.r > 255) 
				{
					rgb_color.r = 255;
				}
				if (rgb_color.g > 255) 
				{
					rgb_color.g = 255;
				}
				if (rgb_color.b > 255) 
				{
					rgb_color.b = 255;
				}*/
				//printf("%dr %dg %db\n", rgb_color.r, rgb_color.g, rgb_color.b);

				// set color
				color_to_set = 
				((rgb_color.r & 0xff) << 16) +
				((rgb_color.g & 0xff) << 8) +
				(rgb_color.b & 0xff);
			}
			else
			{
				color_to_set = 0x000000;
			}
			vp_vector->touched_objs_list->display_color = color_to_set;
		}
		cur_light = cur_light->next;
	}
	
}