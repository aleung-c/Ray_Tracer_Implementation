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

void add_sphere_to_scene(t_rt *rt, t_vector3 centre, double diametre, double radius) {
	t_scene_object	*new_obj;
	t_scene_object	*tmp;

	new_obj = (t_scene_object *)malloc(sizeof(t_scene_object)); // allouer le maillon.
	// alloue et set les vals.
	new_obj->type = SPHERE;
	new_obj->sphere = (t_sphere *)malloc(sizeof(t_sphere));
	new_obj->sphere->centre = centre;
	new_obj->sphere->diametre = diametre;
	new_obj->sphere->radius = radius;

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