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

void add_sphere_to_scene(t_rt *rt, t_vector3 centre, double diametre, double radius, int color)
{
	t_scene_object	*new_obj;
	t_scene_object	*tmp;

	new_obj = (t_scene_object *)malloc(sizeof(t_scene_object)); // allouer le maillon.
	new_obj->next = NULL;
	// alloue et set les vals.
	new_obj->type = SPHERE;
	new_obj->color = color;
	new_obj->sphere_obj = (t_sphere *)malloc(sizeof(t_sphere)); // alloue l'obj.
	new_obj->sphere_obj->pos = centre;
	new_obj->sphere_obj->diametre = diametre;
	new_obj->sphere_obj->radius = radius;

	//add maillon to list;
	if (rt->scene_objs == NULL) // si liste null;
	{
		rt->scene_objs = new_obj;
		return ;
	}
	else
	{
		tmp = rt->scene_objs;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_obj;
		return ;
	}
}

void add_plane_to_scene(t_rt *rt, t_vector3 point, t_vector3 normale, int color)
{
	t_scene_object	*new_obj;
	t_scene_object	*tmp;

	new_obj = (t_scene_object *)malloc(sizeof(t_scene_object)); // allouer le maillon.
	new_obj->next = NULL;
	// Alloue et set les vals.
	new_obj->type = PLANE;
	new_obj->color = color;
	new_obj->plane_obj = (t_plane *)malloc(sizeof(t_plane)); // alloue l'obj.
	new_obj->plane_obj->point = point;
	new_obj->plane_obj->normale = normale;

	// Add maillon to list;
	if (rt->scene_objs == NULL) // si liste null;
	{
		rt->scene_objs = new_obj;
		return ;
	}
	else
	{
		tmp = rt->scene_objs;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_obj;
		return ;
	}

}