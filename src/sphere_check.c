/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <aleung-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/03 13:32:45 by aleung-c          #+#    #+#             */
/*   Updated: 2015/12/03 13:32:46 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

void	sphere_check(t_screen_vec *vp_vec, t_scene_object *obj,
						t_vector3 origine, t_vector3 vec)
{
	t_sphere_algo		algo;

	algo_touching_sphere(&algo, obj, origine, vec);
	if (algo.det > 0.0)
	{
		algo_sphere_touched(&algo, origine, vec);
		add_touch_to_vp_vec(vp_vec, obj, origine, algo.tpoint);
	}
}

void	algo_touching_sphere(t_sphere_algo *algo, t_scene_object *obj,
								t_vector3 origine, t_vector3 vec_dir)
{
	algo->a =
		pow(vec_dir.x, 2) + pow(vec_dir.y, 2) + pow(vec_dir.z, 2);
	algo->b =
		2.0 * vec_dir.x * (origine.x - obj->sphere_obj->pos.x)
		+ 2.0 * vec_dir.y * (origine.y - obj->sphere_obj->pos.y)
		+ 2.0 * vec_dir.z * (origine.z - obj->sphere_obj->pos.z);
	algo->c =
		pow(obj->sphere_obj->pos.x, 2) +
		pow(obj->sphere_obj->pos.y, 2) +
		pow(obj->sphere_obj->pos.z, 2) +
		pow(origine.x, 2) +
		pow(origine.y, 2) +
		pow(origine.z, 2) +
		-2.0
		* (obj->sphere_obj->pos.x * origine.x
		+ obj->sphere_obj->pos.y * origine.y
		+ obj->sphere_obj->pos.z * origine.z)
		- pow(obj->sphere_obj->radius, 2);
	algo->det =
		pow(algo->b, 2) - 4.0 * algo->a * algo->c;
}

void	algo_sphere_touched(t_sphere_algo *algo, t_vector3 origine,
								t_vector3 vec_dir)
{
	double				ret;
	double				ret2;

	ret = (-algo->b + sqrt(algo->det)) / (2.0 * algo->a);
	ret2 = (-algo->b - sqrt(algo->det)) / (2.0 * algo->a);
	algo->t = (ret2 > 0.0001 ? ret2 : ret);
	algo->tpoint.x = origine.x + algo->t * vec_dir.x;
	algo->tpoint.y = origine.y + algo->t * vec_dir.y;
	algo->tpoint.z = origine.z + algo->t * vec_dir.z;
}

int		sphere_check_touch(t_scene_object *obj, t_light *cur_light,
							t_screen_vec *vp_vector)
{
	t_sphere_algo		algo;
	double				dist_to_light;
	double				dist_to_obj;
	t_vector3			vec_direction;

	vec_direction = vec_dir(vp_vector->touched_objs_list->point,
								cur_light->pos);
	algo_touching_sphere(&algo, obj, vp_vector->touched_objs_list->point,
							vec_direction);
	if (algo.det > 0.0)
	{
		algo_sphere_touched(&algo, vp_vector->touched_objs_list->point,
								vec_direction);
		dist_to_light = distance(vp_vector->touched_objs_list->point,
									cur_light->pos);
		dist_to_obj = distance(vp_vector->touched_objs_list->point,
								algo.tpoint);
		if (dist_to_obj < dist_to_light)
			return (1);
		else
			return (0);
	}
	return (0);
}
