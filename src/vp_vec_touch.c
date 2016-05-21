/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vp_vec_touch.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/21 17:16:07 by aleung-c          #+#    #+#             */
/*   Updated: 2016/05/21 17:16:11 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

void			add_touch_to_vp_vec(t_screen_vec *vp_vec,
					t_scene_object *obj, t_vector3 origine,
						t_vector3 touch_point)
{
	t_touch		*new_touch;

	new_touch = (t_touch *)malloc(sizeof(t_touch));
	new_touch->next = NULL;
	new_touch->touched_obj = obj;
	new_touch->point = touch_point;
	new_touch->color = obj->color;
	new_touch->display_color = obj->color;
	new_touch->obj_inter_normale = get_normale(
			new_touch->touched_obj, touch_point);
	new_touch->distance = distance(origine, touch_point);
	vp_vec->touched_objs_list = add_newtouch_to_vp_vec_list(
		vp_vec->touched_objs_list, new_touch);
}

t_scene_object	*get_closest_object(t_screen_vec *vp_vec)
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

t_touch			*add_newtouch_to_vp_vec_list(t_touch *list,
												t_touch *new_obj)
{
	t_touch		*tmp;

	if (list == NULL)
		return (new_obj);
	else
	{
		tmp = list;
		if (new_obj->distance < tmp->distance)
		{
			list = new_obj;
			new_obj->next = tmp;
			return (list);
		}
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_obj;
		return (list);
	}
}
