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

#include "../includes/rtv1.h"

void	cylinder_check(t_screen_vec *vp_vec, t_scene_object *obj,
						t_vector3 origine, t_vector3 vec_dir)
{
	t_cylinder_algo		algo;

	algo.vec_rotated = do_rotate(obj->cylinder_obj->rot, vec_dir);
	algo.origine_rotated = do_rotate(obj->cylinder_obj->rot, origine);
	algo_touching_cylinder(&algo, obj, algo.origine_rotated,
							algo.vec_rotated);
	if (algo.det > 0.0)
	{
		algo_cylinder_touched(&algo, algo.origine_rotated, algo.vec_rotated);
		add_touch_to_vp_vec(vp_vec, obj, algo.origine_rotated, algo.tpoint);
	}
}

void	algo_touching_cylinder(t_cylinder_algo *algo, t_scene_object *obj,
							t_vector3 origine, t_vector3 vec_dir)
{
	algo->a =
		pow(vec_dir.x, 2) + pow(vec_dir.y, 2);
	algo->b =
		2.0 * (vec_dir.x * (origine.x - obj->cylinder_obj->pos.x)
		+ vec_dir.y * (origine.y - obj->cylinder_obj->pos.y));
	algo->c =
		pow((origine.x - obj->cylinder_obj->pos.x), 2)
		+ pow((origine.y - obj->cylinder_obj->pos.y), 2)
		- pow(obj->cylinder_obj->radius, 2);
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

int		cylinder_check_touch(t_scene_object *obj, t_light *cur_light,
								t_screen_vec *vp_vector)
{
	t_cylinder_algo			algo;
	t_casted_shadow_calcs	shad_algo;
	t_vector3				vec;
	t_vector3				origine;

	origine = vp_vector->touched_objs_list->point;
	origine = do_rotate(obj->cylinder_obj->rot, origine);
	vec = vec_dir(origine, cur_light->pos);
	algo_touching_cylinder(&algo, obj, origine, vec);
	if (algo.det > 0.0)
	{
		algo_cylinder_touched(&algo, origine, vec);
		shad_algo.inter_to_light = normalize_vector(vec);
		shad_algo.inter_to_obj_normale = get_cylinder_norm(obj, algo.tpoint);
		shad_algo.vec_angle = acos(scalar(shad_algo.inter_to_light,
										shad_algo.inter_to_obj_normale));
		shad_algo.dist_to_light = distance(origine, cur_light->pos);
		shad_algo.dist_to_obj = distance(origine, algo.tpoint);
		if (shad_algo.dist_to_obj < shad_algo.dist_to_light
			&& shad_algo.vec_angle > 1.6F)
			return (1);
		else
			return (0);
	}
	return (0);
}
