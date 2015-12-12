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

void add_touch_to_vp_vec(t_screen_vec *vp_vec, t_scene_object *obj, t_vector3 origine, t_vector3 touch_point)
{
	t_touch		*new_obj;
	t_touch		*tmp;

	new_obj = (t_touch *)malloc(sizeof(t_touch)); // alloue le maillon.
	new_obj->next = NULL;
	// alloue et set les vals.
	new_obj->touched_obj = obj;
	new_obj->point = touch_point;
	new_obj->color = obj->color;

	new_obj->distance = distance(origine, touch_point);

	// add maillon to list;
	if (vp_vec->touched_objs_list == NULL) // si liste null;
	{
		vp_vec->touched_objs_list = new_obj;
		return ;
	}
	else
	{
		tmp = vp_vec->touched_objs_list;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_obj;
		return ;
	}

}

t_scene_object *get_closest_object(t_screen_vec *vp_vec) // marche pas ...
{
	t_touch *tmp;
	t_touch *closest;

	closest = NULL;
	if (vp_vec->touched_objs_list == NULL) // si liste null;
			return (NULL);
	else
	{
		closest = vp_vec->touched_objs_list;
		tmp = vp_vec->touched_objs_list;
		while (tmp)
		{
			if (tmp->distance < closest->distance)
			{
				closest = tmp; // elem actuel = closest, restart tri.
				tmp = vp_vec->touched_objs_list;
			}
			else
				tmp = tmp->next;
		}
			return (closest->touched_obj);
	}
	return (NULL);
}