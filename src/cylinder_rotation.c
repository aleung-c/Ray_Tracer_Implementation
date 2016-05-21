/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_rotation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/19 16:08:33 by aleung-c          #+#    #+#             */
/*   Updated: 2016/05/19 16:08:41 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

void		set_cylinder_rotation(t_scene_object *new_obj, t_vector3 normale)
{
	t_vector3	v;
	t_vector3	norm;
	t_vector3	axe;

	create_vertical_norm(&norm);
	v = normale;
	v = normalize_vector(v);
	axe = vector(v, norm);
	if (!axe.x && !axe.y && !axe.z)
	{
		new_obj->cylinder_obj->rot[0][0] = 1;
		new_obj->cylinder_obj->rot[1][1] = 1;
		new_obj->cylinder_obj->rot[2][2] = 1;
	}
	else
		get_rotate(axe, scalar(v, norm), new_obj->cylinder_obj->rot);
	new_obj->cylinder_obj->pos = do_rotate(new_obj->cylinder_obj->rot,
									new_obj->cylinder_obj->pos);
}
