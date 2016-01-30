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

int plane_check_touch(t_scene_object *obj, t_vector3 origine,
				t_vector3 vec_dir)
{
	t_plane_algo	algo;
	t_vector3		max_point;

	max_point = point_from_vecdir(origine, vec_dir);
	algo.t = -(((obj->plane_obj->normale.x * origine.x)
	+ (obj->plane_obj->normale.z * origine.z)
	+ (obj->plane_obj->normale.y * origine.y) 
	+ obj->plane_obj->point.y)
	/ ((obj->plane_obj->normale.x * vec_dir.x) 
	+ (obj->plane_obj->normale.z * vec_dir.z)
	+ -(obj->plane_obj->normale.y * vec_dir.y)));

	if (algo.t >= 0.0)
	{
		// TODO : ne fonctionne pas pour lombre, le vecteur depasse la cam ...
		// touche le plan.
		// calcul du point touché.
		algo.tpoint.x = origine.x + algo.t * vec_dir.x;
		algo.tpoint.y = origine.y + algo.t * vec_dir.y;
		algo.tpoint.z = origine.z + algo.t * vec_dir.z;
		if (distance(origine, algo.tpoint) < distance(origine, max_point))
			return (1);
		else
			return (0);
	}
	return (0);
}