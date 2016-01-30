/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_light_to_scene.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/23 13:28:22 by aleung-c          #+#    #+#             */
/*   Updated: 2016/01/23 13:28:28 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "RTv1.h"

void add_light_to_scene(t_rt *rt, t_vector3 pos, float intensity)
{
	t_light	*new_light;
	t_light	*tmp;

	new_light = (t_light *)malloc(sizeof(t_light)); // allouer le maillon.
	new_light->next = NULL;
	
	new_light->pos = pos;
	new_light->intensity = intensity;

	//add maillon to list;
	if (rt->scene_lights == NULL) // si liste null;
	{
		rt->scene_lights = new_light;
		return ;
	}
	else
	{
		tmp = rt->scene_lights;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_light;
		return ;
	}
}