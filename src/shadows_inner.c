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

#include "../includes/rtv1.h"

void		calculate_inner_shadows(t_rt *rt)
{
	int i;
	int screen_size;

	i = 0;
	screen_size = rt->screen_height * rt->screen_width;
	while (i < screen_size)
	{
		run_trough_lights_inner_shadows(rt, &(rt->vp_vectors[i]));
		i++;
	}
}

void		run_trough_lights_inner_shadows(t_rt *rt, t_screen_vec *vp_vector)
{
	t_light		*cur_light;
	int			color_to_set;

	cur_light = rt->scene_lights;
	while (cur_light)
	{
		if (vp_vector->touched_objs_list != NULL)
		{
			if (vp_vector->touched_objs_list->touched_obj->type == PLANE)
			{
				color_to_set = set_inner_color_from_dist(cur_light, vp_vector);
				vp_vector->touched_objs_list->display_color = color_to_set;
			}
			else
			{
				color_to_set = set_inner_color_from_normale(cur_light,
					vp_vector);
				vp_vector->touched_objs_list->display_color = color_to_set;
			}
		}
		cur_light = cur_light->next;
	}
}

int			set_inner_color_from_dist(t_light *cur_light,
										t_screen_vec *vp_vector)
{
	t_inner_shadow_calcs	algo;

	algo.distance_to_light = distance(vp_vector->touched_objs_list->point,
		cur_light->pos);
	if (algo.distance_to_light < cur_light->light_power_distance)
	{
		algo.normalized_distance_to_light =
		algo.distance_to_light / cur_light->light_power_distance;
		algo.obj_color = vp_vector->touched_objs_list->color;
		algo.rgb_color = hex_to_rgb(algo.obj_color);
		algo.color_incval_precise = (algo.normalized_distance_to_light) * 255.0;
		algo.color_incval = (int)floor(algo.color_incval_precise);
		algo.rgb_color.r -= algo.color_incval;
		algo.rgb_color.g -= algo.color_incval;
		algo.rgb_color.b -= algo.color_incval;
		check_limit_darkening(&algo.rgb_color);
		algo.color_to_set = rgb_to_hex(algo.rgb_color);
	}
	else
		algo.color_to_set = 0x000000;
	return (algo.color_to_set);
}

int			set_inner_color_from_normale(t_light *cur_light,
											t_screen_vec *vp_vector)
{
	t_inner_shadow_calcs	algo;

	algo.inter_to_light = vec_dir_distance_normalized(
		vp_vector->touched_objs_list->point, cur_light->pos);
	algo.inter_to_obj_normale = vp_vector->touched_objs_list->
	obj_inter_normale;
	algo.vec_angle = acos(scalar(algo.inter_to_light,
						algo.inter_to_obj_normale));
	if (algo.vec_angle > 1.0F)
	{
		algo.obj_color = vp_vector->touched_objs_list->color;
		algo.rgb_color = hex_to_rgb(algo.obj_color);
		algo.color_incval_precise = (algo.vec_angle - 1.0) * 255.0;
		algo.color_incval = (int)floor(algo.color_incval_precise);
		algo.rgb_color.r -= algo.color_incval_precise;
		algo.rgb_color.g -= algo.color_incval_precise;
		algo.rgb_color.b -= algo.color_incval_precise;
		check_limit_darkening(&algo.rgb_color);
		algo.color_to_set = rgb_to_hex(algo.rgb_color);
	}
	else
		algo.color_to_set = vp_vector->touched_objs_list->touched_obj->color;
	return (algo.color_to_set);
}
