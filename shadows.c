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
	// parcours les obj et trace des rayons du point d'intersection vers les lights
	int scan_x;
	int scan_y;
	int i;

	scan_x = 0;
	scan_y = 0;
	i = 0;
	while (scan_y < rt->screen_height) // pour chaque colonne.
	{
		while (scan_x < rt->screen_width) // pour chaque ligne de pixel.
		{
			// fait le check du vec actuel pour chaque premier obj touche de la scene.
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
	// parcourir toutes les lights.
	while (cur_light)
	{
		check_is_in_shadow(rt, vp_vector, cur_light);
		cur_light = cur_light->next;
	}
}

// for each object
void check_is_in_shadow(t_rt *rt, t_screen_vec *vp_vector, t_light *cur_light)
{
	t_scene_object		*tmp;

	if (vp_vector->touched_objs_list == NULL) // protect segfault
	{
		return ; // no obj, dont touch the color.
	}
	tmp = rt->scene_objs;

	// parcourir tous les objs.
	while (tmp)
	{
		if (check_is_in_shadow_type_filtering(tmp, vp_vector, cur_light, rt->has_casted_shadows_on_self) == 1)
			return ; // stops it when found one shadow to merge them.
		tmp = tmp->next;
	}
}

int	check_is_in_shadow_type_filtering (t_scene_object *tmp, 
		t_screen_vec *vp_vector, t_light *cur_light, int has_self_shadows)
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
		else if (has_self_shadows == 1) // shadowing the same object;
		{
			if (sphere_check_touch2(tmp, cur_light, vp_vector) == 1)
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
		else if (has_self_shadows == 1)  // shadowing the same object;
		{
			if (cone_check_touch2(tmp, cur_light, vp_vector) == 1)
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
