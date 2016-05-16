/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_obj_to_scene.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <aleung-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/03 11:56:27 by aleung-c          #+#    #+#             */
/*   Updated: 2015/12/03 11:56:28 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"
#include <stdio.h> //


void add_sphere_to_scene(t_rt *rt, t_vector3 centre, double radius, int color)
{
	t_scene_object	*new_obj;

	new_obj = NULL;
	new_obj = clean_obj(new_obj);
	// alloue et set les vals.
	new_obj->type = SPHERE;
	new_obj->color = color;
	new_obj->sphere_obj = (t_sphere *)malloc(sizeof(t_sphere)); // alloue l'obj.
	new_obj->sphere_obj->pos = centre;
	new_obj->sphere_obj->radius = radius;
	new_obj->sphere_obj->diametre = radius * 2.0;
	rt->last_added_obj = new_obj;
	add_obj_to_scene_list(rt, new_obj);
}

void add_plane_to_scene(t_rt *rt, t_vector3 point, t_vector3 normale, int color)
{
	t_scene_object	*new_obj;

	new_obj = NULL;
	new_obj = clean_obj(new_obj);
	// Alloue et set les vals.
	new_obj->type = PLANE;
	new_obj->color = color;
	new_obj->plane_obj = (t_plane *)malloc(sizeof(t_plane)); // alloue l'obj.
	new_obj->plane_obj->point = point;
	new_obj->plane_obj->normale = normale;
	rt->last_added_obj = new_obj;
	add_obj_to_scene_list(rt, new_obj);
}


void add_cylinder_to_scene(t_rt *rt, t_vector3 point, double radius, int color)
{
	t_scene_object	*new_obj;

	new_obj = NULL;
	new_obj = clean_obj(new_obj);
	// Alloue et set les vals.
	new_obj->type = CYLINDER;
	new_obj->color = color;
	new_obj->cylinder_obj = (t_cylinder *)malloc(sizeof(t_cylinder)); // alloue l'obj.
	new_obj->cylinder_obj->pos = point;
	new_obj->cylinder_obj->radius = radius;
	new_obj->cylinder_obj->rot[0][0] = 1;
	new_obj->cylinder_obj->rot[1][1] = 1;
	new_obj->cylinder_obj->rot[2][2] = 1;
	rt->last_added_obj = new_obj;
	add_obj_to_scene_list(rt, new_obj);
}

void add_cone_to_scene(t_rt *rt, t_vector3 point, double angle, int color)
{
	t_scene_object	*new_obj;

	new_obj = NULL;
	new_obj = clean_obj(new_obj);
	// Alloue et set les vals.
	new_obj->type = CONE;
	new_obj->color = color;
	new_obj->cone_obj = (t_cone *)malloc(sizeof(t_cone)); // alloue l'obj.
	new_obj->cone_obj->pos = point;
	new_obj->cone_obj->angle = angle;
	new_obj->cone_obj->rot[0][0] = 1;
	new_obj->cone_obj->rot[1][1] = 1;
	new_obj->cone_obj->rot[2][2] = 1;
	rt->last_added_obj = new_obj;
	add_obj_to_scene_list(rt, new_obj);
}

void add_obj_to_scene_list(t_rt *rt, t_scene_object *obj_to_add)
{
	t_scene_object	*tmp;

	// Add maillon to list;
	if (rt->scene_objs == NULL) // si liste null;
	{
		rt->scene_objs = obj_to_add;
		return ;
	}
	else
	{
		tmp = rt->scene_objs;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = obj_to_add;
		return ;
	}
}

t_scene_object	*clean_obj(t_scene_object	*new_obj)
{
	new_obj = (t_scene_object *)malloc(sizeof(t_scene_object));
	new_obj->next = NULL;
	new_obj->sphere_obj = NULL;
	new_obj->plane_obj = NULL;
	new_obj->cylinder_obj = NULL;
	new_obj->cone_obj = NULL;
	return (new_obj);
}
