/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_entry.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/17 17:10:40 by aleung-c          #+#    #+#             */
/*   Updated: 2016/05/17 17:10:43 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

void		init_entry(t_rt *rt)
{
	rt->has_casted_shadows = 1;
	rt->has_casted_shadows_on_self = 1;
	rt->has_inner_shadows = 1;
	rt->has_shining = 1;
	init_screen_values(rt);
	init_camera(rt);
	if (rt->scene_number == 1)
		init_scene1(rt);
	else if (rt->scene_number == 2)
		init_scene2(rt);
	else if (rt->scene_number == 3)
		init_scene3(rt);
	else if (rt->scene_number == 4)
		init_scene4(rt);
	else if (rt->scene_number == 5)
		init_scene5(rt);
	else if (rt->scene_number == 6)
		init_scene6(rt);
	else if (rt->scene_number == 7)
		init_scene7(rt);
}

void		init_screen_values(t_rt *rt)
{
	rt->screen_height = SCREEN_H;
	rt->screen_width = SCREEN_W;
	rt->screen_height_ratio = 4.0;
	rt->screen_width_ratio = 4.0;
	rt->vp_vectors = malloc(sizeof(t_screen_vec)
		* (rt->screen_height
		* rt->screen_width));
}

void		init_camera(t_rt *rt)
{
	rt->camera.type = CAM;
	rt->camera.camera_obj = (t_camera *)malloc(sizeof(t_camera));
	rt->camera.camera_obj->pos.x = 0.0;
	rt->camera.camera_obj->pos.y = -1.0;
	rt->camera.camera_obj->pos.z = 1.0;
	rt->camera.camera_obj->euler_angles.x = 0.0;
	rt->camera.camera_obj->euler_angles.y = 0.0;
	rt->camera.camera_obj->euler_angles.z = 0.0;
	rt->camera.camera_obj->dist_cam_screen = 4.0;
}
