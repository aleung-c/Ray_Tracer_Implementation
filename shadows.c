/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadows.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/23 13:55:33 by aleung-c          #+#    #+#             */
/*   Updated: 2016/01/23 13:55:37 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"
#include <stdio.h> //

void		calculate_casted_shadows(t_rt *rt)
{
	int		scan_x;
	int		scan_y;
	int		i;

	scan_x = 0;
	scan_y = 0;
	i = 0;
	while (scan_y < rt->screen_height)
	{
		while (scan_x < rt->screen_width)
		{
			run_trough_lights_shadows(rt, &(rt->vp_vectors[i]));
			scan_x++;
			i++;
		}
		scan_y++;
		scan_x = 0;
	}
} 

void		run_trough_lights_shadows(t_rt *rt, t_screen_vec *vp_vector)
{
	t_light		*cur_light;

	cur_light = rt->scene_lights;
	while (cur_light)
	{
		check_is_in_shadow(rt, vp_vector, cur_light);
		cur_light = cur_light->next;
	}
}

void		check_is_in_shadow(t_rt *rt, t_screen_vec *vp_vector, t_light *cur_light)
{
	if (vp_vector->touched_objs_list == NULL)
	{
		return ;
	}
	rt->tmp = rt->scene_objs;
	while (rt->tmp)
	{
		if (check_is_in_shadow_type_filtering(rt->tmp, vp_vector, cur_light))
			return ;
		rt->tmp = rt->tmp->next;
	}
}

int			check_is_in_shadow_type_filtering (t_scene_object *tmp, 
		t_screen_vec *vp_vector, t_light *cur_light)
{
	if (tmp->type == SPHERE)
	{
		if (tmp != vp_vector->touched_objs_list->touched_obj)
		{
			if (sphere_check_touch(tmp, cur_light, vp_vector) == 1)
			{
				vp_vector->touched_objs_list->display_color =
					darken_color(vp_vector->touched_objs_list->display_color, 2);
				return (1);
			}
		}
	}
	if (tmp->type == PLANE && tmp != vp_vector->touched_objs_list->touched_obj)
	{
		if (plane_check_touch(tmp, cur_light, vp_vector) == 1)
		{
			vp_vector->touched_objs_list->display_color =
				darken_color(vp_vector->touched_objs_list->display_color, 2);
			return (1);
		}
	}
	if (tmp->type == CYLINDER && tmp != vp_vector->touched_objs_list->touched_obj)
	{
		if (cylinder_check_touch(tmp, cur_light, vp_vector) == 1)
		{
			vp_vector->touched_objs_list->display_color =
				darken_color(vp_vector->touched_objs_list->display_color, 2);
			return (1);
		}
	}
	if (tmp->type == CONE)
	{
		if (tmp != vp_vector->touched_objs_list->touched_obj)
		{
			if (cone_check_touch(tmp, cur_light, vp_vector) == 1)
			{
				vp_vector->touched_objs_list->display_color =
					darken_color(vp_vector->touched_objs_list->display_color, 2);
				return (1);
			}
		}
	}
	return (0);
}

int		darken_color(int hex_target_color, int divisor)
{
	t_rgb				rgb_color;

	if (divisor != 0) 
	{
		rgb_color = hex_to_rgb(hex_target_color);
		rgb_color.r /= divisor;
		rgb_color.g /= divisor;
		rgb_color.b /= divisor;
		return (rgb_to_hex(rgb_color));
	}
	return (hex_target_color);
}
