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
	// regarder si touche une sphere en calculant le determinant;
	algo.det = algo.b * algo.b - 4 * algo.a * algo.c;
	// si le vec touche la sphere, remplir le touch.
	if (algo.det >= 0.0) {
		// touche la sphere.
		algo_sphere_touched(&algo, origine, vec_dir);
		add_touch_to_vp_vec(vp_vec, obj, origine, algo.tpoint);
	}
}

void	algo_touching_sphere(t_sphere_algo *algo, t_scene_object *obj,
							t_vector3 origine, t_vector3 vec_dir)
{
	algo->a = (vec_dir.x * vec_dir.x) + (vec_dir.y * vec_dir.y) +
		(vec_dir.z * vec_dir.z);
	algo->b = 2 * vec_dir.x * (origine.x - obj->sphere_obj->pos.x) +
		2 * vec_dir.y * (origine.y - obj->sphere_obj->pos.y) + 2 *
		vec_dir.z *(origine.z - obj->sphere_obj->pos.z);
	algo->c = obj->sphere_obj->pos.x * obj->sphere_obj->pos.x +
		obj->sphere_obj->pos.y * obj->sphere_obj->pos.y +
		obj->sphere_obj->pos.z * obj->sphere_obj->pos.z +
		origine.x * origine.x + origine.y * origine.y + origine.z * origine.z
		+ -2 * (obj->sphere_obj->pos.x * origine.x + obj->sphere_obj->pos.y *
			origine.y + obj->sphere_obj->pos.z * origine.z)
		- obj->sphere_obj->diametre * obj->sphere_obj->radius;
}

void	algo_sphere_touched(t_sphere_algo *algo, t_vector3 origine,
							t_vector3 vec_dir)
{
	//t_vector3			s_vect;

	// calculer la position touchée;
	algo->t = (-algo->b - sqrt((algo->b * algo->b) - 4 * algo->a * algo->c)) / 2
		* algo->a;
	algo->tpoint.x = origine.x + algo->t * vec_dir.x;
	algo->tpoint.y = origine.y + algo->t * vec_dir.y;
	algo->tpoint.z = origine.z + algo->t * vec_dir.z;
	
	// calcul le vec de dir; unused for now.
	//s_vect.x = (algo.svec.x - obj->sphere_obj->pos.x) / obj->sphere_obj->radius;
	//s_vect.y = (algo.svec.y - obj->sphere_obj->pos.y) / obj->sphere_obj->radius;
	//s_vect.z = (algo.svec.z - obj->sphere_obj->pos.z) / obj->sphere_obj->radius;
}