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
#include <stdio.h> //

void add_touch_to_vp_vec(t_screen_vec *vp_vec, t_scene_object *obj,
							t_vector3 origine, t_vector3 touch_point)
{
	t_touch		*new_touch;
	t_touch		*tmp;

	new_touch = (t_touch *)malloc(sizeof(t_touch)); // alloue le maillon.
	new_touch->next = NULL;
	// alloue et set les vals.
	new_touch->touched_obj = obj;
	new_touch->point = touch_point;
	new_touch->color = obj->color;
	new_touch->display_color = obj->color;
	new_touch->obj_inter_normale = get_normale(new_touch->touched_obj, touch_point);
	new_touch->distance = distance(origine, touch_point);
	//printf("distance : %.4f \n", new_touch->distance);

	// add maillon to list;
	if (vp_vec->touched_objs_list == NULL) // si liste null;
	{
		vp_vec->touched_objs_list = new_touch;
		return ;
	}
	else
	{
		tmp = vp_vec->touched_objs_list;
		// si new obj est plus pres que lelem1 de la liste, new obj est le prems elem.
		if (new_touch->distance < tmp->distance)
		{
			vp_vec->touched_objs_list = new_touch;
			new_touch->next = tmp;
			return ;
		}
		//sinon, new obj go en fin de liste.
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
				//tmp = vp_vec->touched_objs_list;
			}
			tmp = tmp->next;
		}
		return (closest->touched_obj);
	}
	return (NULL);
}