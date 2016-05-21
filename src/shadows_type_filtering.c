/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadows_type_filtering.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/21 14:27:05 by aleung-c          #+#    #+#             */
/*   Updated: 2016/05/21 14:27:09 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

int		check_sphere_shadow(t_scene_object *tmp,
								t_screen_vec *vp_vector, t_light *cur_light)
{
	if (sphere_check_touch(tmp, cur_light, vp_vector) == 1)
	{
		vp_vector->touched_objs_list->display_color =
			darken_color(vp_vector->touched_objs_list->display_color, 2);
		return (1);
	}
	return (0);
}

int		check_plane_shadow(t_scene_object *tmp,
								t_screen_vec *vp_vector, t_light *cur_light)
{
	if (plane_check_touch(tmp, cur_light, vp_vector) == 1)
	{
		vp_vector->touched_objs_list->display_color =
			darken_color(vp_vector->touched_objs_list->display_color, 2);
		return (1);
	}
	return (0);
}

int		check_cylinder_shadow(t_scene_object *tmp,
								t_screen_vec *vp_vector, t_light *cur_light)
{
	if (cylinder_check_touch(tmp, cur_light, vp_vector) == 1)
	{
		vp_vector->touched_objs_list->display_color =
			darken_color(vp_vector->touched_objs_list->display_color, 2);
		return (1);
	}
	return (0);
}

int		check_cone_shadow(t_scene_object *tmp,
								t_screen_vec *vp_vector, t_light *cur_light)
{
	if (cone_check_touch(tmp, cur_light, vp_vector) == 1)
	{
		vp_vector->touched_objs_list->display_color =
			darken_color(vp_vector->touched_objs_list->display_color, 2);
		return (1);
	}
	return (0);
}
