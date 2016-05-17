/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_scene_definition.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/17 17:15:29 by aleung-c          #+#    #+#             */
/*   Updated: 2016/05/17 17:15:34 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

void			init_scene1(t_rt *rt)
{
	t_vector3	pos;

	rt->has_casted_shadows = 0;
	// Light
	pos = set_vec3(2.0, 1.0, 1.0);
	add_light_to_scene(rt, pos, 1.0, 8.0);

	// adding sphere //
	pos = set_vec3(0.0, 4.0, 1.0);
	add_sphere_to_scene(rt, pos, 2.0, 0xAA0000); // sphere rouge
}

void			init_scene2(t_rt *rt)
{
	t_vector3	pos;
	//t_vector3	normale;

	rt->has_casted_shadows = 0;
	// Light
	pos = set_vec3(2.0, 1.0, 1.0);
	add_light_to_scene(rt, pos, 1.0, 7.0);

	// Adding cylinder
	pos = set_vec3(0.0, 4.0, 1.0);
	add_cylinder_to_scene(rt, pos, 1.0, 0xFF9966); // cylindre peche

}

void		init_scene3(t_rt *rt)
{
	t_vector3	pos;
	t_vector3	normale;

	rt->has_casted_shadows = 0;
	// Light
	pos = set_vec3(2.0, 1.0, 1.0);
	add_light_to_scene(rt, pos, 1.0, 7.0);

	// Adding cone
	pos = set_vec3(0.0, 4.0, 1.0);
	add_cone_to_scene(rt, pos, 0.5, 0xFFCC33); // cone jaune

	// adding plane //
	normale = set_vec3(0.0, 0.0, 1.0);
	pos = set_vec3(0.0, 0.0, 5.0);
	add_plane_to_scene(rt, pos, normale, 0x0000BB); // plan vert
}

void		init_scene4(t_rt *rt)
{
	if (rt)
	{}
}

void		init_scene5(t_rt *rt)
{
	if (rt)
	{}
}
