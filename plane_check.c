/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/02 14:50:47 by aleung-c          #+#    #+#             */
/*   Updated: 2016/01/02 14:50:51 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"


void plane_check(t_screen_vec *vp_vec, t_scene_object *obj, t_vector3 origine,
				t_vector3 vec_dir)
{
	t_plane_algo	algo;

	vec_dir = normalize_vector(vec_dir);
	/*algo.t = -(((obj->plane_obj->normale.x * origine.x)
			+ (obj->plane_obj->normale.y * origine.y)
			+ (obj->plane_obj->normale.z * origine.z) 
			+ obj->plane_obj->point.z)
			/ ((obj->plane_obj->normale.x * vec_dir.x) 
			+ (obj->plane_obj->normale.y * vec_dir.y)
			+ (obj->plane_obj->normale.z * vec_dir.z)));*/

			algo.t = -(((obj->plane_obj->normale.x * origine.x)
			+ (obj->plane_obj->normale.z * origine.z)
			+ (obj->plane_obj->normale.y * origine.y) 
			+ obj->plane_obj->point.y)
			
			/ ((obj->plane_obj->normale.x * vec_dir.x) 
			+ (obj->plane_obj->normale.z * vec_dir.z)
			+ -(obj->plane_obj->normale.y * vec_dir.y)));

	if (algo.t >= 0.0)
	{
		// touche le plan.
		// calcul du point touché.
		algo.tpoint.x = origine.x + algo.t * vec_dir.x;
		algo.tpoint.y = origine.y + algo.t * vec_dir.y;
		algo.tpoint.z = origine.z + algo.t * vec_dir.z;
		add_touch_to_vp_vec(vp_vec, obj, origine, algo.tpoint);
	}
}

void algo_touching_plane (t_plane_algo *algo, t_scene_object *obj, t_vector3 origine, t_vector3 vec_dir)
{
	// calculations pour trouver touched point.
	algo->t = -(((obj->plane_obj->normale.x * origine.x)
			+ (obj->plane_obj->normale.z * origine.z)
			+ (obj->plane_obj->normale.y * origine.y) 
			+ obj->plane_obj->point.y)
			
			/ ((obj->plane_obj->normale.x * vec_dir.x) 
			+ (obj->plane_obj->normale.z * vec_dir.z)
			+ -(obj->plane_obj->normale.y * vec_dir.y)));
}

int plane_check_touch(t_scene_object *obj, t_light *cur_light, t_screen_vec *vp_vector)
{
	t_plane_algo		algo;
	double				dist_to_light;
	double				dist_to_obj;
	t_vector3			vec_direction;

	vec_direction = vec_dir_distance_normalized(vp_vector->touched_objs_list->point,
		cur_light->pos);
	algo_touching_plane(&algo, obj, vp_vector->touched_objs_list->point, vec_direction);
	if (algo.t > 0.0)
	{
		// TODO : ne fonctionne pas, a regarder en detail.
		algo.tpoint.x = vp_vector->touched_objs_list->point.x + algo.t * vec_direction.x;
		algo.tpoint.y = vp_vector->touched_objs_list->point.y + algo.t * vec_direction.y;
		algo.tpoint.z = vp_vector->touched_objs_list->point.z + algo.t * vec_direction.z;

		dist_to_light = distance(vp_vector->touched_objs_list->point, cur_light->pos);
		dist_to_obj = distance(vp_vector->touched_objs_list->point, algo.tpoint);
		if (dist_to_obj < dist_to_light) {
			return (1);
		} else {
			return (0);
		}
	}
	return (0);
}