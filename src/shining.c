/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shining.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/20 18:24:04 by aleung-c          #+#    #+#             */
/*   Updated: 2016/05/20 18:24:07 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

void		calcultate_shining(t_rt *rt)
{
	int i;
	int screen_size;

	i = 0;
	screen_size = rt->screen_height * rt->screen_width;
	while (i < screen_size)
	{
		run_trough_lights_shining(rt, &(rt->vp_vectors[i]));
		i++;
	}
}

void		run_trough_lights_shining(t_rt *rt, t_screen_vec *vp_vector)
{
	t_light		*cur_light;
	int			color_to_set;

	cur_light = rt->scene_lights;
	while (cur_light)
	{
		if (vp_vector->touched_objs_list != NULL)
		{
			if (vp_vector->touched_objs_list->touched_obj->type != PLANE)
			{
				color_to_set = set_shining_color(cur_light,
					vp_vector);
				vp_vector->touched_objs_list->display_color = color_to_set;
			}
		}
		cur_light = cur_light->next;
	}
}

int			set_shining_color(t_light *cur_light,
								t_screen_vec *vp_vector)
{
	t_shining_calcs		algo;

	algo.inter_to_light = vec_dir_distance_normalized(
		vp_vector->touched_objs_list->point, cur_light->pos);
	algo.inter_to_obj_normale = vp_vector->touched_objs_list->
	obj_inter_normale;
	algo.vec_angle = acos(scalar(algo.inter_to_light,
						algo.inter_to_obj_normale));
	if (algo.vec_angle < 0.2F)
	{
		algo.vec_angle = algo.vec_angle / 0.2;
		algo.obj_color = vp_vector->touched_objs_list->color;
		algo.rgb_color = hex_to_rgb(algo.obj_color);
		algo.rgb_color.r += (1.0 - (algo.vec_angle))
							* (255.0 - algo.rgb_color.r);
		algo.rgb_color.g += (1.0 - (algo.vec_angle))
							* (255.0 - algo.rgb_color.g);
		algo.rgb_color.b += (1.0 - (algo.vec_angle))
							* (255.0 - algo.rgb_color.b);
		check_limit_brightening(&algo.rgb_color);
		algo.color_to_set = rgb_to_hex(algo.rgb_color);
	}
	else
		algo.color_to_set = vp_vector->touched_objs_list->display_color;
	return (algo.color_to_set);
}
