/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   seek_objects.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/21 16:44:45 by aleung-c          #+#    #+#             */
/*   Updated: 2016/05/21 16:44:47 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

void		raytrace_objs(t_rt *rt)
{
	rt->scan_x = 0;
	rt->scan_y = 0;
	rt->i = 0;
	while (rt->scan_y < rt->screen_height)
	{
		while (rt->scan_x < rt->screen_width)
		{
			run_trough_objs(rt, &(rt->vp_vectors[rt->i]));
			rt->scan_x++;
			rt->i++;
		}
		rt->scan_y++;
		rt->scan_x = 0;
	}
}

void		run_trough_objs(t_rt *rt, t_screen_vec *vp_vector)
{
	rt->tmp = rt->scene_objs;
	while (rt->tmp)
	{
		if (rt->tmp->type == SPHERE)
			sphere_check(vp_vector, rt->tmp,
				rt->camera.camera_obj->pos, vp_vector->v);
		else if (rt->tmp->type == PLANE)
			plane_check(vp_vector, rt->tmp,
				rt->camera.camera_obj->pos, vp_vector->v);
		else if (rt->tmp->type == CYLINDER)
			cylinder_check(vp_vector, rt->tmp,
				rt->camera.camera_obj->pos, vp_vector->v);
		else if (rt->tmp->type == CONE)
			cone_check(vp_vector, rt->tmp,
				rt->camera.camera_obj->pos, vp_vector->v);
		rt->tmp = rt->tmp->next;
	}
}
