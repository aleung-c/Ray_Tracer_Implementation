/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vp_vec_touch.c                             		:+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <aleung-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/03 11:56:27 by aleung-c          #+#    #+#             */
/*   Updated: 2015/12/03 11:56:28 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

void add_touch_to_vp_vec(t_screen_vec *vp_vec, t_scene_object *obj,
							t_vector3 origine, t_vector3 touch_point)
{
	t_touch		*new_touch;
	t_touch		*tmp;

	new_touch = (t_touch *)malloc(sizeof(t_touch)); // alloue le maillon.
	new_touch->next = NULL;
	new_touch->touched_obj = obj;
	new_touch->point = touch_point;
	new_touch->color = obj->color;
	new_touch->display_color = obj->color;
	new_touch->obj_inter_normale = get_normale(new_touch->touched_obj, touch_point);
	new_touch->distance = distance(origine, touch_point);
	if (vp_vec->touched_objs_list == NULL)
	{
		vp_vec->touched_objs_list = new_touch;
		return ;
	}
	else
	{
		tmp = vp_vec->touched_objs_list;
		if (new_touch->distance < tmp->distance)
		{
			vp_vec->touched_objs_list = new_touch;
			new_touch->next = tmp;
			return ;
		}
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_touch;
		return ;
	}
}

t_scene_object *get_closest_object(t_screen_vec *vp_vec)
{
	t_touch *tmp;
	t_touch *closest;

	closest = NULL;
	if (vp_vec->touched_objs_list == NULL)
			return (NULL);
	else
	{
		closest = vp_vec->touched_objs_list;
		tmp = vp_vec->touched_objs_list;
		while (tmp)
		{
			if (tmp->distance < closest->distance)
				closest = tmp;
			tmp = tmp->next;
		}
		return (closest->touched_obj);
	}
	return (NULL);
}