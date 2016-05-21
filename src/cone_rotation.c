/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone_rotation.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/19 16:15:27 by aleung-c          #+#    #+#             */
/*   Updated: 2016/05/19 16:15:30 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

void	set_cone_rotation(t_scene_object *new_obj, t_vector3 normale)
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
		new_obj->cone_obj->rot[0][0] = 1;
		new_obj->cone_obj->rot[1][1] = 1;
		new_obj->cone_obj->rot[2][2] = 1;
	}
	else
		get_rotate(axe, scalar(v, norm), new_obj->cone_obj->rot);
	new_obj->cone_obj->pos = do_rotate(new_obj->cone_obj->rot,
									new_obj->cone_obj->pos);
}
