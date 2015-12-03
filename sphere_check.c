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

void sphere_check(t_rt *rt, t_vector3 origine, t_vector3 vec_dir) {

	t_sphere_algo algo; // contient toutes les val pour calculer.
	t_vector3 s_vect;
	double sum_vect;
	int color;

	algo.a = (vec_dir.x * vec_dir.x) + (vec_dir.y * vec_dir.y) + (vec_dir.z * vec_dir.z);

	algo.b = 2 * vec_dir.x * (rt->cam_x - rt->sphere.centre.x) + 2 * vec_dir.y * (rt->cam_y - rt->sphere.centre.y) + 2 * vec_dir.z *(rt->cam_z - rt->sphere.centre.z);

	algo.c = rt->sphere.centre.x * rt->sphere.centre.x + rt->sphere.centre.y * rt->sphere.centre.y + rt->sphere.centre.z * rt->sphere.centre.z + 
		rt->cam_x * rt->cam_x + rt->cam_y * rt->cam_y + rt->cam_z * rt->cam_z
		+ -2*(rt->sphere.centre.x * rt->cam_x + rt->sphere.centre.y * rt->cam_y + rt->sphere.centre.z * rt->cam_z) 
		- rt->sphere.diametre * rt->sphere.radius;

	// regarder si touche une sphere en calculant le determinant;
	algo.det = algo.b * algo.b - 4 * algo.a * algo.c;
	// printf("det abc = %f\n", det);

	// calculer la position touchée;
	algo.t = (-algo.b - sqrt((algo.b * algo.b) - 4 * algo.a * algo.c)) / 2 * algo.a;
	algo.sx = rt->cam_x + algo.t * vec_dir.x;
	algo.sy = rt->cam_y + algo.t * vec_dir.y;
	algo.sz = rt->cam_z + algo.t * vec_dir.z;
	//printf("sx = %f, sy = %f, sz = %f \n", sx, sy , sz); 
	s_vect.x = (sx - rt->sphere.centre.x) / rt->sphere.radius;
	s_vect.y = (sy - rt->sphere.centre.y) / rt->sphere.radius;
	s_vect.z = (sz - rt->sphere.centre.z) / rt->sphere.radius;
	sum_vect = fabs(s_vect.x) + fabs(s_vect.y) + fabs(s_vect.z); // somme des vect, indique une distance comparée.
	// printf("sum sphere vect = %f\n",  sum_vect);

	color = set_color(sum_vect);
	if (det >= 0.0)
		pixel_put_to_image(rt, scan_x, scan_y, color);
	//printf("a = %f, b = %f, c = %f \n", a, b , c);

}