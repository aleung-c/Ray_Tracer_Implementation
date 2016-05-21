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

#include "../includes/rtv1.h"

void			add_sphere_to_scene(t_rt *rt, t_vector3 centre,
									double radius, int color)
{
	t_scene_object	*new_obj;

	new_obj = NULL;
	new_obj = clean_obj(new_obj);
	new_obj->type = SPHERE;
	new_obj->color = color;
	new_obj->sphere_obj = (t_sphere *)malloc(sizeof(t_sphere));
	new_obj->sphere_obj->pos = centre;
	new_obj->sphere_obj->radius = radius;
	new_obj->sphere_obj->diametre = radius * 2.0;
	rt->last_added_obj = new_obj;
	add_obj_to_scene_list(rt, new_obj);
}

void			add_plane_to_scene(t_rt *rt, t_vector3 point,
									t_vector3 normale, int color)
{
	t_scene_object	*new_obj;

	new_obj = NULL;
	new_obj = clean_obj(new_obj);
	new_obj->type = PLANE;
	new_obj->color = color;
	new_obj->plane_obj = (t_plane *)malloc(sizeof(t_plane));
	new_obj->plane_obj->point = point;
	new_obj->plane_obj->normale = normale;
	rt->last_added_obj = new_obj;
	add_obj_to_scene_list(rt, new_obj);
}

void			add_cylinder_to_scene(t_rt *rt, t_vector3 point,
						t_vector3 normale, double radius)
{
	t_scene_object	*new_obj;

	new_obj = NULL;
	new_obj = clean_obj(new_obj);
	new_obj->type = CYLINDER;
	new_obj->cylinder_obj = (t_cylinder *)malloc(sizeof(t_cylinder));
	new_obj->cylinder_obj->pos = point;
	new_obj->cylinder_obj->radius = radius;
	new_obj->cylinder_obj->normale = normale;
	set_cylinder_rotation(new_obj, normale);
	rt->last_added_obj = new_obj;
	add_obj_to_scene_list(rt, new_obj);
}

void			add_cone_to_scene(t_rt *rt, t_vector3 point,
					t_vector3 normale, double angle)
{
	t_scene_object	*new_obj;

	new_obj = NULL;
	new_obj = clean_obj(new_obj);
	new_obj->type = CONE;
	new_obj->cone_obj = (t_cone *)malloc(sizeof(t_cone));
	new_obj->cone_obj->pos = point;
	new_obj->cone_obj->angle = angle;
	new_obj->cone_obj->normale = normale;
	set_cone_rotation(new_obj, normale);
	rt->last_added_obj = new_obj;
	add_obj_to_scene_list(rt, new_obj);
}

void			add_obj_to_scene_list(t_rt *rt,
										t_scene_object *obj_to_add)
{
	t_scene_object	*tmp;

	if (rt->scene_objs == NULL)
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
