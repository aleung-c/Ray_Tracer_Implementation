/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_normale.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/20 12:17:20 by aleung-c          #+#    #+#             */
/*   Updated: 2016/05/20 12:17:23 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

t_vector3	get_cylinder_norm(t_scene_object *obj, t_vector3 inter_point)
{
	t_vector3	point;

	point.x = obj->cylinder_obj->pos.x;
	point.y = obj->cylinder_obj->pos.y;
	point.z = inter_point.z;
	return (normalize_vector(vec_dir(point, inter_point)));
}

t_vector3	get_cone_norm(t_scene_object *obj, t_vector3 inter_point)
{
	float	x;
	float	y;
	float	z;
	float	size;
	t_vector3	vec;

	x = inter_point.x - obj->cone_obj->pos.x;
	y = inter_point.y - obj->cone_obj->pos.y;
	z = -obj->cone_obj->angle * (inter_point.z - obj->cone_obj->pos.z);
	size = sqrt(x * x + y * y + z * z);
	vec.x = x / size;
	vec.y = y / size;
	vec.z = z / size;
	return (vec);
}

t_vector3	get_sphere_norm(t_scene_object *obj, t_vector3 inter_point)
{
	return (normalize_vector(vec_dir(obj->sphere_obj->pos, inter_point)));
}

t_vector3	get_normale(t_scene_object *obj, t_vector3 inter_point)
{
	t_vector3	normale_ret;

	normale_ret.x = 0.0;
	normale_ret.y = 0.0;
	normale_ret.z = 0.0;
	if (obj->type == SPHERE)
	{
		normale_ret	= get_sphere_norm(obj, inter_point);
		return (normale_ret);
	}
	else if (obj->type == CYLINDER)
	{
		normale_ret	= get_cylinder_norm(obj, inter_point);
		return (normale_ret);
	}
	else if (obj->type == CONE)
	{
		normale_ret	= get_cone_norm(obj, inter_point);
		return (normale_ret);
	}
	return (normale_ret);
}