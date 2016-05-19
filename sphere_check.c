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

#include "RTv1.h"

void	sphere_check(t_screen_vec *vp_vec, t_scene_object *obj,
						t_vector3 origine, t_vector3 vec_dir)
{
	t_sphere_algo		algo; // contient toutes les val pour calculer.
	t_vector3			vec_normalized;

	vec_normalized = normalize_vector(vec_dir);
	algo_touching_sphere(&algo, obj, origine, vec_dir);
	
	// si le vec touche la sphere, remplir le touch.
	if (algo.det > 0.0)
	{
		// touche la sphere.
		algo_sphere_touched(&algo, origine, vec_dir);
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
		-2.0 * (obj->sphere_obj->pos.x * origine.x
				+ obj->sphere_obj->pos.y * origine.y
				+ obj->sphere_obj->pos.z * origine.z)
		- pow(obj->sphere_obj->radius, 2);

	// regarder si touche une sphere en calculant le determinant;
	algo->det =
		pow(algo->b, 2) - 4.0 * algo->a * algo->c;
}

void	algo_sphere_touched(t_sphere_algo *algo, t_vector3 origine,
							t_vector3 vec_dir)
{
	// calculer la position touchée;
	double	ret;
	double	ret2;

	ret = (-algo->b + sqrt(algo->det)) / (2.0 * algo->a);
	ret2 = (-algo->b - sqrt(algo->det)) / (2.0 * algo->a);
	algo->t = (ret2 > 0.0001 ? ret2 : ret);
	//algo->t = (-algo->b - sqrt((algo->b * algo->b) - 4.0 * algo->a * algo->c)) / (2.0 * algo->a);
	algo->tpoint.x = origine.x + algo->t * vec_dir.x;
	algo->tpoint.y = origine.y + algo->t * vec_dir.y;
	algo->tpoint.z = origine.z + algo->t * vec_dir.z;
}

int		sphere_check_touch(t_scene_object *obj, t_light *cur_light, t_screen_vec *vp_vector)
{
	// TODO : ne fonctionne pas pour lombre, le vecteur depasse la light ...
	// sert seulement a voir si ca touche.
	t_sphere_algo		algo; // contient toutes les val pour calculer.
	
	double				dist_to_light;
	double				dist_to_obj;
	t_vector3			vec_direction;
	t_vector3			vec_normalized;

	vec_direction = vec_dir(vp_vector->touched_objs_list->point, cur_light->pos);
	vec_normalized = normalize_vector(vec_direction);

	algo_touching_sphere(&algo, obj, vp_vector->touched_objs_list->point, vec_direction);
	if (algo.det > 0.0)
	{
		// touche sphere
		algo_sphere_touched(&algo, vp_vector->touched_objs_list->point, vec_direction);

		dist_to_light = distance(vp_vector->touched_objs_list->point, cur_light->pos);
		dist_to_obj = distance(vp_vector->touched_objs_list->point, algo.tpoint);
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

int		sphere_check_touch2(t_scene_object *obj, t_light *cur_light, t_screen_vec *vp_vector)
{
	// sphere sur sphere.
	t_sphere_algo		algo; // contient toutes les val pour calculer.
	
	double				dist_to_light;
	double				dist_to_obj;
	t_vector3			vec_direction;
	t_vector3			vec_normalized;
	t_vector3			sc_tpoint;

	

	sc_tpoint = vp_vector->touched_objs_list->point;
	vec_direction = vec_dir(sc_tpoint, cur_light->pos);
	vec_normalized = normalize_vector(vec_direction);
	algo_touching_sphere(&algo, obj, sc_tpoint, vec_normalized);
	if (algo.det > 0.0)
	{
		// touche sphere
		algo_sphere_touched(&algo, sc_tpoint, vec_direction);

		dist_to_light = distance(sc_tpoint, cur_light->pos);
		dist_to_obj = distance(sc_tpoint, algo.tpoint);
		/*if (vp_vector->touched_objs_list->touched_obj->type == SPHERE)
		{
			printf("dist to light : %f - dist to obj : %f \n", dist_to_light, dist_to_obj);
		}*/
		if (dist_to_obj > dist_to_light)
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
