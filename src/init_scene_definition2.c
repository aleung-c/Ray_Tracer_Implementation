/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_scene_definition2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/17 17:22:02 by aleung-c          #+#    #+#             */
/*   Updated: 2016/05/17 17:22:08 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

void		init_scene6(t_rt *rt)
{
	t_vector3	pos;
	t_vector3	normale;

	rt->has_casted_shadows = 1;
	rt->has_casted_shadows_on_self = 0;
	pos = set_vec3(-0.5, -0.5, 1.0);
	add_light_to_scene(rt, pos, 1.0, 20.0);
	normale = set_vec3(0.0, 0.0, 1.0);
	pos = set_vec3(0.0, 0.0, 1.0);
	add_plane_to_scene(rt, pos, normale, 0x777777);
	normale = set_vec3(-1.0, 0.8, 0.0);
	pos = set_vec3(0.0, 5.0, 0.0);
	add_plane_to_scene(rt, pos, normale, 0x33CCFF);
	normale = set_vec3(0.5, -0.5, 1.0);
	pos = set_vec3(0.5, 1.8, 0.5);
	add_cone_to_scene(rt, pos, normale, 0.6);
	set_object_color(rt->last_added_obj, 0xFFCC33);
	normale = set_vec3(1.0, -0.8, -1.0);
	pos = set_vec3(-1.0, 3.0, 1.0);
	add_cylinder_to_scene(rt, pos, normale, 0.5);
	set_object_color(rt->last_added_obj, 0x33FF99);
	pos = set_vec3(0.0, 2.0, 0.4);
	add_sphere_to_scene(rt, pos, 0.3, 0xCC0000);
}

void		init_scene7(t_rt *rt)
{
	t_vector3	pos;
	t_vector3	normale;

	rt->has_casted_shadows = 1;
	rt->has_casted_shadows_on_self = 0;
	pos = set_vec3(1.0, 1.0, 1.0);
	add_light_to_scene(rt, pos, 1.0, 60.0);
	pos = set_vec3(-1.0, 1.0, 1.0);
	add_light_to_scene(rt, pos, 1.0, 60.0);
	normale = set_vec3(0.0, 0.0, 1.0);
	pos = set_vec3(0.0, 0.0, 1.0);
	add_plane_to_scene(rt, pos, normale, 0x777777);
	normale = set_vec3(0.0, 1.0, 0.0);
	pos = set_vec3(0.0, 15.0, 0.0);
	add_plane_to_scene(rt, pos, normale, 0x33CCFF);
	pos = set_vec3(1.0, 3.0, 1.0);
	add_sphere_to_scene(rt, pos, 0.5, 0xCC0000);
	normale = set_vec3(0.0, 0.0, 1.0);
	pos = set_vec3(-1.0, 3.0, 1.0);
	add_cylinder_to_scene(rt, pos, normale, 0.5);
	set_object_color(rt->last_added_obj, 0x33FF99);
}
