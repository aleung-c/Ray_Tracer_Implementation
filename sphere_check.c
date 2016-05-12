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

	algo_touching_sphere(&algo, obj, origine, vec_dir);
	
	
	// si le vec touche la sphere, remplir le touch.
	if (algo.det > 0.0) {
		// touche la sphere.
		algo_sphere_touched(&algo, origine, vec_dir);
		add_touch_to_vp_vec(vp_vec, obj, origine, algo.tpoint);
	}
}

void	algo_touching_sphere(t_sphere_algo *algo, t_scene_object *obj,
							t_vector3 origine, t_vector3 vec_dir)
{
	algo->a = pow(vec_dir.x, 2) + pow(vec_dir.y, 2) +
		pow(vec_dir.z, 2);

	algo->b = 2.0 * vec_dir.x * (origine.x - obj->sphere_obj->pos.x) + 2.0 * vec_dir.y * (origine.y - obj->sphere_obj->pos.y) + 2.0 *
		vec_dir.z * (origine.z - obj->sphere_obj->pos.z);

	algo->c = 
		pow(obj->sphere_obj->pos.x, 2) +
		pow(obj->sphere_obj->pos.y, 2) +
		pow(obj->sphere_obj->pos.z, 2) +

		pow(origine.x, 2) + 
		pow(origine.y, 2) +
		pow(origine.z, 2) + -2.0 *
		(obj->sphere_obj->pos.x * origine.x + obj->sphere_obj->pos.y *
			origine.y + obj->sphere_obj->pos.z * origine.z)
		- pow(obj->sphere_obj->radius, 2);

		// regarder si touche une sphere en calculant le determinant;
		algo->det = (algo->b * algo->b) - 4.0 * algo->a * algo->c;
}

void	algo_sphere_touched(t_sphere_algo *algo, t_vector3 origine,
							t_vector3 vec_dir)
{
	//t_vector3			s_vect;

	/*double	ret;
	double	ret2;


	ret = (-algo->b + sqrt(algo->det)) / (2.0 * algo->a);
	ret2 = (-algo->b - sqrt(algo->det)) / (2.0 * algo->a);
	algo->t = ret2 > 0.0001 ? ret2 : ret;*/

	// calculer la position touchée;
	algo->t = (-algo->b - sqrt((algo->b * algo->b) - 4.0 * algo->a * algo->c)) / 2.0 * algo->a;
	algo->tpoint.x = origine.x + algo->t * vec_dir.x;
	algo->tpoint.y = origine.y + algo->t * vec_dir.y;
	algo->tpoint.z = origine.z + algo->t * vec_dir.z;
	
	// calcul le vec de dir; unused for now.
	//s_vect.x = (algo.svec.x - obj->sphere_obj->pos.x) / obj->sphere_obj->radius;
	//s_vect.y = (algo.svec.y - obj->sphere_obj->pos.y) / obj->sphere_obj->radius;
	//s_vect.z = (algo.svec.z - obj->sphere_obj->pos.z) / obj->sphere_obj->radius;
}

int		sphere_check_touch(t_scene_object *obj,
						t_vector3 origine, t_vector3 vec_direction)
{
	// TODO : ne fonctionne pas pour lombre, le vecteur depasse la light ...
	// sert seulement a voir si ca touche.
	// toujours pas ...
	t_sphere_algo		algo; // contient toutes les val pour calculer.
	
	t_vector3			LightObjtouchPoint;
	double 				dist_to_light;
	double				dist_to_obj;

	LightObjtouchPoint.x = origine.x + vec_direction.x;
	LightObjtouchPoint.y = origine.y + vec_direction.y;
	LightObjtouchPoint.z = origine.z + vec_direction.z;

	dist_to_light = distance(origine, LightObjtouchPoint);

	algo_touching_sphere(&algo, obj, origine, vec_direction);
	// regarder si touche une sphere en calculant le determinant;
	//algo.det = (algo.b * algo.b) - 4.0 * algo.a * algo.c;
	if (algo.det > 0.0)
	{
		// touche sphere
		algo_sphere_touched(&algo, origine, vec_direction);

		dist_to_obj = distance(origine, algo.tpoint);
		//printf("dist to light : %f - dist to obj : %f \n", dist_to_light, dist_to_obj);
		if (dist_to_obj < dist_to_light) {
			return (1);
		} else {
			return (0);
		}
	}
	return (0);
}