/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_entry.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/17 17:10:40 by aleung-c          #+#    #+#             */
/*   Updated: 2016/05/17 17:10:43 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

void init_entry(t_rt *rt)
{
	t_vector3	pos;
	t_vector3	normale;

	// Default settings
	rt->has_casted_shadows = 1;
	rt->has_casted_shadows_on_self = 1;
	rt->has_inner_shadows = 1;
	rt->has_shining = 1;
	
	init_screen_values(rt);
	init_camera(rt);
	
	if (rt->scene_number == 1)
		init_scene1(rt);
	else if (rt->scene_number == 2)
		init_scene2(rt);
	else if (rt->scene_number == 3)
		init_scene3(rt);
	else if (rt->scene_number == 4)
		init_scene4(rt);
	else if (rt->scene_number == 5)
		init_scene5(rt);
	else if (rt->scene_number == 6)
		init_scene6(rt);
	else if (rt->scene_number == 7)
		init_scene7(rt);
	else
	{

		// --- SPHERES 
		
		// adding sphere //
		//pos = set_vec3(0.5, 5.0, 0.4);
		//add_sphere_to_scene(rt, pos, 0.2, 0x006600); // sphere verte
		
		// adding sphere //
		pos = set_vec3(-1.0, 5.0, 2.0);
		add_sphere_to_scene(rt, pos, 2.0, 0x0066FF); // sphere bleu
		SetObjectId(rt->last_added_obj, 1);
		
		// --- PLANES //
		
		// adding plane //
		normale = set_vec3(0.0, 0.0, 1.0);
		pos = set_vec3(0.0, 0.0, 0.0);
		add_plane_to_scene(rt, pos, normale, 0x669999); // plan vert
		SetObjectId(rt->last_added_obj, 3);
		
		// adding plane //
		normale = set_vec3(1.0, 0.0, 0.0);
		pos = set_vec3(2.0, 2.5, 0.0);
		add_plane_to_scene(rt, pos, normale, 0x6699FF); // plan bleu
		SetObjectId(rt->last_added_obj, 4);

		// adding plane //
		normale = set_vec3(0.0, 1.0, 0.0);
		pos = set_vec3(0.0, 10.0, 0.0);
		add_plane_to_scene(rt, pos, normale, 0x663366); // plan violet
		SetObjectId(rt->last_added_obj, 5);

		// // adding cylinder
		// pos = set_vec3(4.0, 5.0, 2.0);
		// add_cylinder_to_scene(rt, pos, 0.5, 0xFF9966); // cylindre peche
		// SetObjectId(rt->last_added_obj, 6);

		// // adding cone
		// pos = set_vec3(2.5, 5.0, 2.0);
		// add_cone_to_scene(rt, pos, 0.2, 0xCC9900); // cone jaune
		// SetObjectId(rt->last_added_obj, 7);


		// DEBUG ---------- //
		// OBJ DEBUG
		t_scene_object *tmp;
		int i;

		i = 0;
		tmp = rt->scene_objs;
		while (tmp) {
			i++;
			if (tmp->type == SPHERE) {
				printf("Add sphere to scene \n");
			}
			tmp = tmp->next;
		}
		printf("Scene nb %d :\n", rt->scene_number);
		printf("Nombre d'objets : %d \n", i);
		// LIGHT DEBUG
		t_light *tmp_light;

		i = 0;
		tmp_light = rt->scene_lights;
		while (tmp_light) {
			i++;
			tmp_light = tmp_light->next;
		}
		printf("Nombre de lights : %d \n", i);
		// DEBUG End --------- //
	}
}

void		init_screen_values(t_rt *rt)
{
	rt->screen_height = SCREEN_H;
	rt->screen_width = SCREEN_W;
	rt->screen_height_ratio = 4.0;
	rt->screen_width_ratio = 4.0;
	rt->vp_vectors = malloc(sizeof(t_screen_vec) * (rt->screen_height * rt->screen_width));
}

void		init_camera(t_rt *rt)
{
	rt->camera.type = CAM;
	rt->camera.camera_obj = (t_camera *)malloc(sizeof(t_camera));
	rt->camera.camera_obj->pos.x = 0.0;
	rt->camera.camera_obj->pos.y = -1.0;
	rt->camera.camera_obj->pos.z = 1.0;
	rt->camera.camera_obj->euler_angles.x = 0.0;
	rt->camera.camera_obj->euler_angles.y = 0.0;
	rt->camera.camera_obj->euler_angles.z = 0.0;
	rt->camera.camera_obj->dist_cam_screen = 4.0;
}
