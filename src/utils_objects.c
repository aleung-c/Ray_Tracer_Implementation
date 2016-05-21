/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/21 17:02:49 by aleung-c          #+#    #+#             */
/*   Updated: 2016/05/21 17:02:52 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

void			set_object_id(t_scene_object *obj, int id)
{
	obj->id = id;
}

void			set_object_color(t_scene_object *obj, int color)
{
	obj->color = color;
}

char			*get_object_type(t_scene_object *obj)
{
	char *ret_type;

	if (obj->type == SPHERE)
		ret_type = ft_strdup("Sphere");
	else if (obj->type == PLANE)
		ret_type = ft_strdup("Plane");
	else if (obj->type == CONE)
		ret_type = ft_strdup("Cone");
	else if (obj->type == CYLINDER)
		ret_type = ft_strdup("Cylinder");
	else
		ret_type = ft_strdup("UnknownType");
	return (ret_type);
}

t_scene_object	*clean_obj(t_scene_object *new_obj)
{
	new_obj = (t_scene_object *)malloc(sizeof(t_scene_object));
	new_obj->next = NULL;
	new_obj->sphere_obj = NULL;
	new_obj->plane_obj = NULL;
	new_obj->cylinder_obj = NULL;
	new_obj->cone_obj = NULL;
	return (new_obj);
}
