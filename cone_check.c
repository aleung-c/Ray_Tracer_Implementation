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
	t_vector3			vec_normalized;
	t_vector3			vec_rotated_normalized;

	algo.vec_rotated = do_rotate(obj->cone_obj->rot, vec_dir);
	algo.origine_rotated = do_rotate(obj->cone_obj->rot, origine);

	vec_normalized = normalize_vector(vec_dir);
	vec_rotated_normalized = normalize_vector(algo.vec_rotated);
	
	algo_touching_cone(&algo, obj, algo.origine_rotated, algo.vec_rotated);

	if (algo.det > 0.1E-7) // epsilon (?)
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

int cone_check_touch(t_scene_object *obj, t_light *cur_light, t_screen_vec *vp_vector)
{
	t_cone_algo			algo;
	double				dist_to_light;
	double				dist_to_obj;
	t_vector3			vec;
	//t_vector3			vec_normalized;
	//t_vector3			vec_rotated_normalized;

	vec = vec_dir(vp_vector->touched_objs_list->point, cur_light->pos);
	//vec_normalized = normalize_vector(vec);

	algo.vec_rotated = do_rotate(obj->cone_obj->rot, vec);
	//vec_rotated_normalized = do_rotate(obj->cone_obj->rot, vec_normalized);
	algo.origine_rotated = do_rotate(obj->cone_obj->rot, vp_vector->touched_objs_list->point);
	
	algo_touching_cone(&algo, obj, algo.origine_rotated, algo.vec_rotated);
	if (algo.det > 0.1E-7)
	{
		algo_cone_touched(&algo, algo.origine_rotated, algo.vec_rotated);
		dist_to_light = distance(algo.origine_rotated, cur_light->pos);
		dist_to_obj = distance(algo.origine_rotated, algo.tpoint);
		if (dist_to_obj < dist_to_light)
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

int cone_check_touch2(t_scene_object *obj, t_light *cur_light, t_screen_vec *vp_vector)
{
	t_cone_algo			algo;
	double				dist_to_light;
	double				dist_to_obj;
	t_vector3			vec;
	t_vector3			vec_normalized;
	t_vector3			vec_rotated_normalized;

	vec = vec_dir(vp_vector->touched_objs_list->point, cur_light->pos);
	vec_normalized = normalize_vector(vec);

	algo.vec_rotated = do_rotate(obj->cone_obj->rot, vec);
	vec_rotated_normalized = do_rotate(obj->cone_obj->rot, vec_normalized);
	algo.origine_rotated = do_rotate(obj->cone_obj->rot, vp_vector->touched_objs_list->point);
	algo_touching_cone(&algo, obj, algo.origine_rotated, algo.vec_rotated);
	if (algo.det > 0.1E-7)
	{
		algo_cone_touched(&algo, algo.origine_rotated, algo.vec_rotated);
		dist_to_light = distance(algo.origine_rotated, cur_light->pos);
		dist_to_obj = distance(algo.origine_rotated, algo.tpoint);
		if (dist_to_obj < dist_to_light)
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
