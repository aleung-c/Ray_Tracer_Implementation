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

void		calculate_casted_shadows(t_rt *rt)
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
		check_is_in_shadow(rt, vp_vector, cur_light);
		// pour chaque light.
		/*if (check_is_in_shadow(rt, vp_vector, cur_light) == 1)
		{
			// isinshadow
			if (vp_vector->touched_objs_list != NULL) { 
				vp_vector->touched_objs_list->display_color = 0x000000;
			} // si no obj touche, reste noir.
			
		}*/
		cur_light = cur_light->next;
	}
}

// for each object
void check_is_in_shadow(t_rt *rt, t_screen_vec *vp_vector, t_light *cur_light)
{
	t_scene_object		*tmp;
	int					in_shadow;
	t_rgb				rgb_color;

	in_shadow = 0;
	if (vp_vector->touched_objs_list == NULL) // protect segfault
	{
		return ; // no obj, dont touch the color.
	}
	tmp = rt->scene_objs;

	// parcourir tous les objs.
	while (tmp)
	{
		// TODO : empecher l'ombre sur le meme obj;
			if (tmp->type == SPHERE && tmp != vp_vector->touched_objs_list->touched_obj)
			{
				if (sphere_check_touch(tmp, cur_light, vp_vector) == 1)
				{
					/*if (vp_vector->touched_objs_list->touched_obj->id == 2)
					printf("sphere nb %d touche sphere %d\n", vp_vector->touched_objs_list->touched_obj->id, tmp->id);*/
					// divise la couleur pour l'ombrager
					rgb_color = hex_to_rgb(vp_vector->touched_objs_list->display_color);

					rgb_color.r /= 3;
					rgb_color.g /= 3;
					rgb_color.b /= 3;

					vp_vector->touched_objs_list->display_color = rgb_to_hex(rgb_color);
					return ;
				}
			}
			if (tmp->type == PLANE && tmp != vp_vector->touched_objs_list->touched_obj)
			{
				if (plane_check_touch(tmp, cur_light, vp_vector) == 1)
				{
					rgb_color = hex_to_rgb(vp_vector->touched_objs_list->display_color);

					rgb_color.r /= 3;
					rgb_color.g /= 3;
					rgb_color.b /= 3;

					vp_vector->touched_objs_list->display_color = rgb_to_hex(rgb_color);
					return ;
				}
			}
			if (tmp->type == CYLINDER && tmp != vp_vector->touched_objs_list->touched_obj)
			{
				if (cylinder_check_touch(tmp, cur_light, vp_vector) == 1)
				{
					rgb_color = hex_to_rgb(vp_vector->touched_objs_list->display_color);

					rgb_color.r /= 3;
					rgb_color.g /= 3;
					rgb_color.b /= 3;

					vp_vector->touched_objs_list->display_color = rgb_to_hex(rgb_color);
					return ;
				}
			}
			if (tmp->type == CONE && tmp != vp_vector->touched_objs_list->touched_obj)
			{
				if (cone_check_touch(tmp, cur_light, vp_vector) == 1)
				{
					rgb_color = hex_to_rgb(vp_vector->touched_objs_list->display_color);
					
					rgb_color.r /= 3;
					rgb_color.g /= 3;
					rgb_color.b /= 3;

					vp_vector->touched_objs_list->display_color = rgb_to_hex(rgb_color);
					return ;
				}
			}

		tmp = tmp->next;
	}
}
