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

void		calculate_inner_shadows(t_rt *rt)
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
	int 		color_to_set;

	cur_light = rt->scene_lights;
	// parcourir toutes les lights.
	while (cur_light)
	{
		// pour chaque light.
		if (vp_vector->touched_objs_list != NULL)
		{
			if (vp_vector->touched_objs_list->touched_obj->type == PLANE)
			{
				color_to_set = set_inner_color_from_dist(cur_light, vp_vector);
				vp_vector->touched_objs_list->display_color = color_to_set;
			}
			else
			{
				color_to_set = set_inner_color_from_normale(cur_light, vp_vector);
				vp_vector->touched_objs_list->display_color = color_to_set;
			}
		}
		cur_light = cur_light->next;
	}
}

int			set_inner_color_from_dist(t_light *cur_light, t_screen_vec *vp_vector)
{
	float		distance_to_light;
	float		normalized_distance_to_light;
	t_rgb		rgb_color;
	int 		obj_color;
	double		color_incval_precise;
	int 		color_incval;
	int 		color_to_set;

	distance_to_light = distance(vp_vector->touched_objs_list->point, cur_light->pos);
	if (distance_to_light < cur_light->light_power_distance)
	{
		normalized_distance_to_light = 
		distance_to_light / cur_light->light_power_distance;
		obj_color = vp_vector->touched_objs_list->color;
		rgb_color = hex_to_rgb(obj_color);
		color_incval_precise = (normalized_distance_to_light) * 255.0;
		color_incval = (int)floor(color_incval_precise);
		// add color;
		rgb_color.r -= color_incval_precise;
		rgb_color.g -= color_incval;
		rgb_color.b -= color_incval;

		check_limit_darkening(&rgb_color); // if rgb < 0, rgb = 0;
		color_to_set = rgb_to_hex(rgb_color);
	}
	else
	{
		color_to_set = 0x000000;
	}
	return (color_to_set);
}

int			set_inner_color_from_normale(t_light *cur_light, t_screen_vec *vp_vector)
{
	
	t_vector3		inter_to_light;
	t_vector3		inter_to_obj_normale;
	int				obj_color;
	t_rgb			rgb_color;
	int				color_to_set;
	double			diffval_vecs;
	double 			vec_angle;
	int				color_incval_precise;
	int				color_incval;

	inter_to_light = vec_dir_distance_normalized(vp_vector->touched_objs_list->point, cur_light->pos);
	inter_to_obj_normale = vp_vector->touched_objs_list->obj_inter_normale;
	diffval_vecs = vector_length(inter_to_obj_normale) - vector_length(inter_to_light); // OK
	
	vec_angle = acos(scalar(inter_to_light, inter_to_obj_normale));
	if (vec_angle > 1.0F)
	{
		obj_color = vp_vector->touched_objs_list->color;
		
		rgb_color = hex_to_rgb(obj_color);
		color_incval_precise = (vec_angle - 1.0) * 255.0;
		color_incval = (int) floor(color_incval_precise);

		rgb_color.r -= color_incval_precise;
		rgb_color.g -= color_incval_precise;
		rgb_color.b -= color_incval_precise;

		check_limit_darkening(&rgb_color);
		color_to_set = rgb_to_hex(rgb_color);
	}
	else
	{
		color_to_set = vp_vector->touched_objs_list->touched_obj->color;
		//color_to_set = 0x00FF00;
	}
	return (color_to_set);
}










