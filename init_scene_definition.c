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
	t_vector3	normale;

	rt->has_casted_shadows = 0;
	// Light
	pos = set_vec3(2.0, 1.0, 1.0);
	add_light_to_scene(rt, pos, 1.0, 7.0);

	// Adding cylinder
	normale = set_vec3(0.0, 0.0, 0.0);
	pos = set_vec3(0.0, 4.0, 1.0);
	add_cylinder_to_scene(rt, pos, normale, 1.0, 0xFF9966); // cylindre peche

}

void		init_scene3(t_rt *rt)
{
	t_vector3	pos;
	t_vector3	normale;

	rt->has_casted_shadows = 1;
	rt->has_casted_shadows_on_self = 0;
	// Light
	pos = set_vec3(2.0, 1.0, 2.0);
	add_light_to_scene(rt, pos, 1.0, 15.0);
//	add_sphere_to_scene(rt, pos, 0.01, 0xFF0000); // sphere rouge

	// Adding cone
	normale = set_vec3(0.0, 0.0, 1.0);
	pos = set_vec3(0.0, 4.0, 1.0);
	add_cone_to_scene(rt, pos, normale, 0.5, 0xFFCC33); // cone jaune

	// adding plane //
	normale = set_vec3(0.0, 0.0, 1.0);
	pos = set_vec3(0.0, 0.0, 5.0);
	add_plane_to_scene(rt, pos, normale, 0x0000BB); // plan bleu
}

void		init_scene4(t_rt *rt)
{
	t_vector3	pos;
	t_vector3	normale;

	rt->has_casted_shadows = 0;
	rt->has_casted_shadows_on_self = 0;
	rt->has_inner_shadows = 1;

	// Light
	pos = set_vec3(1.0, 1.0, 2.0);
	add_light_to_scene(rt, pos, 1.0, 15.0);

	// adding plane //
	normale = set_vec3(0.0, 0.0, 1.0);
	pos = set_vec3(0.0, 0.0, 5.0);
	add_plane_to_scene(rt, pos, normale, 0x777777); // plan gris

	// adding plane //
	normale = set_vec3(0.0, 1.0, 0.0);
	pos = set_vec3(0.0, 10.0, 0.0);
	add_plane_to_scene(rt, pos, normale, 0x33CCFF); // plan bleu

	// Adding cone
	normale = set_vec3(0.5, 0.0, 1.0);
	pos = set_vec3(1.0, 4.0, 0.8);
	add_cone_to_scene(rt, pos, normale, 0.6, 0xFFCC33); // cone jaune

	// Adding cylinder
	normale = set_vec3(1.0, 0.0, -1.0);
	pos = set_vec3(-1.0, 4.0, 1.0);
	add_cylinder_to_scene(rt, pos, normale, 0.5, 0x33FF99); // cylindre vert

	// adding sphere //
	pos = set_vec3(0.0, 3.5, 0.4);
	add_sphere_to_scene(rt, pos, 0.5, 0xCC0000); // sphere rouge
}

void		init_scene5(t_rt *rt)
{
	t_vector3	pos;
	t_vector3	normale;

	rt->has_casted_shadows = 0;
	rt->has_casted_shadows_on_self = 0;
	// Light
	pos = set_vec3(-1.0, 1.0, 1.0);
	add_light_to_scene(rt, pos, 1.0, 6.0);

	// adding plane //
	normale = set_vec3(0.0, 0.0, 1.0);
	pos = set_vec3(0.0, 0.0, 1.0);
	add_plane_to_scene(rt, pos, normale, 0x777777); // plan gris

	// adding plane //
	normale = set_vec3(-1.0, 0.8, 0.0);
	pos = set_vec3(0.0, 5.0, 0.0);
	add_plane_to_scene(rt, pos, normale, 0x33CCFF); // plan bleu

	// Adding cone
	normale = set_vec3(0.5, -0.5, 1.0);
	pos = set_vec3(0.5, 1.8, 0.5);
	add_cone_to_scene(rt, pos, normale, 0.6, 0xFFCC33); // cone jaune

	// Adding cylinder
	normale = set_vec3(1.0, -0.8, -1.0);
	pos = set_vec3(-1.0, 3.0, 1.0);
	add_cylinder_to_scene(rt, pos, normale, 0.5, 0x33FF99); // cylindre vert

	// adding sphere //
	pos = set_vec3(0.0, 2.0, 0.4);
	add_sphere_to_scene(rt, pos, 0.3, 0xCC0000); // sphere rouge
}
