/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/16 16:41:44 by aleung-c          #+#    #+#             */
/*   Updated: 2016/05/16 16:41:47 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"
#include <stdio.h> //

void	cone_check(t_screen_vec *vp_vec, t_scene_object *obj,
						t_vector3 origine, t_vector3 vec_dir)
{
	t_cone_algo			algo; // contient toutes les val pour calculer.

	algo.vec_rotated = do_rotate(obj->cone_obj->rot, vec_dir);
	algo.origine_rotated = do_rotate(obj->cone_obj->rot, origine);
	algo_touching_cone(&algo, obj, algo.origine_rotated, algo.vec_rotated);
	if (algo.det > 0.0) // epsilon (?)
	{
		algo_cone_touched(&algo, algo.origine_rotated, algo.vec_rotated);
		add_touch_to_vp_vec(vp_vec, obj, algo.origine_rotated, algo.tpoint);
		// limite. not needed.
		/*return ((cone->limite1 == cone->limite2 || \
		(vec.z * dist > cone->limite1 && vec.z * \
		dist < cone->limite2)) ? dist : -1);*/
	}
}

void	algo_touching_cone(t_cone_algo *algo, t_scene_object *obj,
							t_vector3 origine, t_vector3 vec_dir)
{
	algo->a = 
		pow(vec_dir.x, 2)
		+ pow(vec_dir.y, 2)
		- pow(vec_dir.z, 2)
		* pow(tan(obj->cone_obj->angle), 2);

	algo->b = 2.0
		* (vec_dir.x * (origine.x - obj->cone_obj->pos.x) 
		+ vec_dir.y * (origine.y - obj->cone_obj->pos.y)
		- vec_dir.z * (origine.z - obj->cone_obj->pos.z) 
		* pow(tan(obj->cone_obj->angle), 2));

	algo->c =
		  pow((origine.x - obj->cone_obj->pos.x), 2)
		+ pow((origine.y - obj->cone_obj->pos.y), 2)
		- pow(((origine.z - obj->cone_obj->pos.z)), 2)
		* pow(tan(obj->cone_obj->angle), 2);
	
	algo->det = pow(algo->b, 2) - 4.0 * algo->a * algo->c;
}

void	algo_cone_touched(t_cone_algo *algo, t_vector3 origine,
							t_vector3 vec_dir)
{
	double	ret;
	double	ret2;

	ret = (-algo->b + sqrt(algo->det)) / (2.0 * algo->a);
	ret2 = (-algo->b - sqrt(algo->det)) / (2.0 * algo->a);
	algo->t = (ret2 > 0.0001 ? ret2 : ret);

	algo->tpoint.x = origine.x + algo->t * vec_dir.x;
	algo->tpoint.y = origine.y + algo->t * vec_dir.y;
	algo->tpoint.z = origine.z + algo->t * vec_dir.z;
}

int		cone_check_touch(t_scene_object *obj, t_light *cur_light, t_screen_vec *vp_vector)
{
	t_cone_algo			algo;
	double				dist_to_light;
	double				dist_to_obj;
	t_vector3			vec;
	t_vector3			origine;

	t_vector3			inter_to_light;
	t_vector3			inter_to_obj_normale;
	double				vec_angle;

	origine = vp_vector->touched_objs_list->point;
	origine = do_rotate(obj->cone_obj->rot, origine);
	vec = vec_dir(origine, cur_light->pos);
	algo_touching_cone(&algo, obj, origine, vec);
	if (algo.det > 0.0)
	{
		algo_cone_touched(&algo, origine, vec);
		dist_to_light = distance(origine, cur_light->pos);
		dist_to_obj = distance(origine, algo.tpoint);
		inter_to_light = normalize_vector(vec);
		inter_to_obj_normale = get_cone_norm(obj, algo.tpoint);
		vec_angle = acos(scalar(inter_to_light, inter_to_obj_normale));
		
		if (dist_to_obj < dist_to_light && vec_angle > 1.6F)
		{
			return (1);
		}
		else
		{
			return (0);
		}
	}
	return (0);
}
