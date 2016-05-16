/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_objects.c                             	    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <aleung-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/03 11:56:27 by aleung-c          #+#    #+#             */
/*   Updated: 2015/12/03 11:56:28 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

void		SetObjectName(t_scene_object *Obj, char *Str)
{
	Obj->name = Str;
}

char		*GetObjectName(t_scene_object *Obj)
{
	return (ft_strdup(Obj->name));
}

void		SetObjectId(t_scene_object *Obj, int Id)
{
	Obj->id = Id;
}

int			GetObjectId(t_scene_object *Obj)
{
	return (Obj->id);
}

char		*GetObjectType(t_scene_object *Obj)
{
	char *RetType;

	if (Obj->type == SPHERE)
		RetType = ft_strdup("Sphere");
	else if (Obj->type == PLANE)
		RetType = ft_strdup("Plane");
	else if (Obj->type == CONE)
		RetType = ft_strdup("Cone");
	else if (Obj->type == CYLINDER)
		RetType = ft_strdup("Cylinder");
	else
		RetType = ft_strdup("UnknownType");
	return (RetType);
}