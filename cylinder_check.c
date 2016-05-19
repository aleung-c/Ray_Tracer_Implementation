/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_check.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/16 13:29:03 by aleung-c          #+#    #+#             */
/*   Updated: 2016/05/16 13:29:05 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"
#include <stdio.h> //

void cylinder_check(t_screen_vec *vp_vec, t_scene_object *obj, t_vector3 origine,
				t_vector3 vec_dir)
{
	t_cylinder_algo		algo;
	//t_vector3			vec_dir_normalized;

	// apply cylinder rotation
	//vec_dir_normalized = normalize_vector(vec_dir);
	algo.vec_rotated = do_rotate(obj->cylinder_obj->rot, vec_dir);
	algo.origine_rotated = do_rotate(obj->cylinder_obj->rot, origine);
	algo_touching_cylinder(&algo, obj, algo.origine_rotated, algo.vec_rotated);
	if (algo.det > 0.0)
	{
		algo_cylinder_touched(&algo, algo.origine_rotated, algo.vec_rotated);
		add_touch_to_vp_vec(vp_vec, obj, algo.origine_rotated, algo.tpoint);
		// limite cylinder. pas besoin.
		/*return ((cylinder->limite1 == cylinder->limite2 || \
		(vec.z * dist > cylinder->limite1 && vec.z * \
		dist < cylinder->limite2)) ? dist : -1);*/

	}
}

void	algo_touching_cylinder(t_cylinder_algo *algo, t_scene_object *obj,
							t_vector3 origine, t_vector3 vec_dir)
{
	algo->a = pow(vec_dir.x, 2) + pow(vec_dir.y, 2);
	algo->b = 2.0 * (vec_dir.x * (origine.x - obj->cylinder_obj->pos.x)
		+ vec_dir.y * (origine.y - obj->cylinder_obj->pos.y));
	algo->c = pow((origine.x - obj->cylinder_obj->pos.x), 2)
	+ pow((origine.y - obj->cylinder_obj->pos.y), 2) - pow(obj->cylinder_obj->radius, 2);
	algo->det = pow(algo->b, 2) - 4.0 * algo->a * algo->c;
}

void	algo_cylinder_touched(t_cylinder_algo *algo, t_vector3 origine,
							t_vector3 vec_dir)
{
	double			ret;
	double			ret2;

	ret = (-algo->b + sqrt(algo->det)) / (2.0 * algo->a);
	ret2 = (-algo->b - sqrt(algo->det)) / (2.0 * algo->a);
	
	algo->t = (ret2 > 0.0001 ? ret2 : ret);
	algo->tpoint.x = origine.x + algo->t * vec_dir.x;
	algo->tpoint.y = origine.y + algo->t * vec_dir.y;
	algo->tpoint.z = origine.z + algo->t * vec_dir.z;
}

int cylinder_check_touch(t_scene_object *obj, t_light *cur_light, t_screen_vec *vp_vector)
{
	t_cylinder_algo		algo;
	double				dist_to_light;
	double				dist_to_obj;
	t_vector3			vec;

	t_vector3			point_displacement;
	t_vector3			vec_point_to_cam_normalized;

	// displace inter point closer to screen
	point_displacement = vp_vector->touched_objs_list->point;

	vec_point_to_cam_normalized = normalize_vector(vp_vector->v);
	point_displacement.x += -(vec_point_to_cam_normalized.x) * 1.2;
	point_displacement.y += -(vec_point_to_cam_normalized.y) * 1.2;
	point_displacement.z += -(vec_point_to_cam_normalized.z) * 1.2;
	

	vec = vec_dir_distance_normalized(point_displacement, cur_light->pos);
	// apply cylinder rotation
	algo.vec_rotated = do_rotate(obj->cylinder_obj->rot, vec);
	algo.origine_rotated = do_rotate(obj->cylinder_obj->rot, point_displacement);
	algo_touching_cylinder(&algo, obj, algo.origine_rotated, algo.vec_rotated);
	if (algo.det > 0.0)
	{
		algo_cylinder_touched(&algo, algo.origine_rotated, algo.vec_rotated);
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
