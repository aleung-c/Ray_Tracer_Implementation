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

#include "../includes/rtv1.h"

void	add_light_to_scene(t_rt *rt, t_vector3 pos, double intensity,
							double light_power_distance)
{
	t_light	*new_light;
	t_light	*tmp;

	new_light = (t_light *)malloc(sizeof(t_light));
	new_light->next = NULL;
	new_light->pos = pos;
	new_light->intensity = intensity;
	new_light->light_power_distance = light_power_distance;
	if (rt->scene_lights == NULL)
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
