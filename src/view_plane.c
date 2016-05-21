/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view_plane.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/16 14:43:01 by aleung-c          #+#    #+#             */
/*   Updated: 2016/05/16 14:43:05 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

void	calculate_viewplane(t_rt *rt)
{
	t_viewplane_vars	vp;

	init_useful_vars(rt, &vp);
	init_count_vars(rt, &vp);
	vp.inc_x = rt->screen_width_ratio / (float)rt->screen_width;
	vp.inc_z = rt->screen_height_ratio / (float)rt->screen_height;
	while (vp.y < rt->screen_height)
	{
		while (vp.x < rt->screen_width)
		{
			vp.xref += vp.inc_x;
			rt->vp_vectors[vp.i].v.x = vp.xref - rt->camera.camera_obj->pos.x;
			rt->vp_vectors[vp.i].v.y = vp.yref - rt->camera.camera_obj->pos.y;
			rt->vp_vectors[vp.i].v.z = vp.zref - rt->camera.camera_obj->pos.z;
			rt->vp_vectors[vp.i].touched_objs_list = NULL;
			vp.i++;
			vp.x++;
		}
		vp.xref = rt->vp_upleft_pos.x;
		vp.zref -= vp.inc_z;
		vp.x = 0;
		vp.y++;
	}
}

void	init_count_vars(t_rt *rt, t_viewplane_vars *vp)
{
	vp->xref = rt->vp_upleft_pos.x;
	vp->yref = rt->vp_upleft_pos.y;
	vp->zref = rt->vp_upleft_pos.z;
	vp->y = 0;
	vp->x = 1;
	vp->i = 1;
}

void	init_useful_vars(t_rt *rt, t_viewplane_vars *vp)
{
	rt->vp_center_pos.x = rt->camera.camera_obj->pos.x;
	rt->vp_center_pos.y = rt->camera.camera_obj->pos.y
							+ rt->camera.camera_obj->dist_cam_screen;
	rt->vp_center_pos.z = rt->camera.camera_obj->pos.z;
	vp->vecdir_cam_screen_y = rt->vp_center_pos.y
							- rt->camera.camera_obj->pos.y;
	vp->vecdir_cam_screen_y *= vp->vecdir_cam_screen_y;
	vp->vecdir_cam_screen_y += 1.0;
	vp->vecdir_cam_screen_y = sqrt(vp->vecdir_cam_screen_y);
	rt->vp_upleft_pos.x = rt->camera.camera_obj->pos.x
							- (rt->screen_width_ratio / 2.0);
	rt->vp_upleft_pos.y = rt->camera.camera_obj->pos.y
							+ rt->camera.camera_obj->dist_cam_screen;
	rt->vp_upleft_pos.z = rt->camera.camera_obj->pos.z
							+ (rt->screen_height_ratio / 2.0);
	rt->vp_vectors[0].v.x = rt->vp_upleft_pos.x
								- rt->camera.camera_obj->pos.x;
	rt->vp_vectors[0].v.y = rt->vp_upleft_pos.y
								- rt->camera.camera_obj->pos.y;
	rt->vp_vectors[0].v.z = rt->vp_upleft_pos.z
								- rt->camera.camera_obj->pos.z;
}
