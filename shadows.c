/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadows.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/23 13:55:33 by aleung-c          #+#    #+#             */
/*   Updated: 2016/01/23 13:55:37 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"
#include <stdio.h> //


// TODO : A refaire. seul le premier objet envoie de l'ombre.

void		calculate_shadows(t_rt *rt)
{
	// parcours les obj et trace des rayons du point d'intersection vers les lights
	int scan_x;
	int scan_y;
	int i;

	scan_x = 0;
	scan_y = 0;
	i = 0;

	//color = 0x000000; // base color = black;
	while (scan_y < rt->screen_height) // pour chaque colonne.
	{
		while (scan_x < rt->screen_width) // pour chaque ligne de pixel.
		{
			// fait le check du vec actuel pour chaque premier obj touche de la scene.
			run_trough_lights_shadows(rt, &(rt->vp_vectors[i]));
			scan_x++;
			i++;
		}
		scan_y++;
		scan_x = 0;
	}
} 

void		run_trough_lights_shadows(t_rt *rt, t_screen_vec *vp_vector)
{
	t_light		*cur_light;

	cur_light = rt->scene_lights;
	// parcourir toutes les lights.
	while (cur_light)
	{
		// pour chaque light.
		if (check_is_in_shadow(rt, vp_vector, cur_light) == 1)
		{
			// isinshadow
			if (vp_vector->touched_objs_list != NULL) { 
				vp_vector->touched_objs_list->color = 0x000000;
			} // si no obj touche, reste noir.
			
		}
		cur_light = cur_light->next;
	}
}

// for each object
int check_is_in_shadow(t_rt *rt, t_screen_vec *vp_vector, t_light *cur_light)
{
	t_scene_object	*tmp;
	t_vector3		vec_direction;

	if (vp_vector->touched_objs_list != NULL) { // protect segfault
		vec_direction = vec_dir(vp_vector->touched_objs_list->point, cur_light->pos);
	} else {
		return (0); // no obj, dont touch the color.
	}
	// vec_direction = normalize_vector(vec_direction);
	tmp = rt->scene_objs;

	// parcourir tous les objs.
	while (tmp)
	{
		//printf ("shadowcheck : tmp = %p \n touchedobj = %p \n", tmp, vp_vector->touched_objs_list->touched_obj);

		if (tmp != vp_vector->touched_objs_list->touched_obj) // -> Tested = OK;
		{
			if (tmp->type == SPHERE)
			{
				if (sphere_check_touch(tmp,
					vp_vector->touched_objs_list->point, vec_direction) == 1)
					return (1);
			}
			/*else if (tmp->type == PLANE)
			{
				if (plane_check_touch(tmp,
					vp_vector->touched_objs_list->point, vec_direction) == 1)
					return (1);
			}*/
		}
		tmp = tmp->next;
	}
	return (0);
}
