/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_vec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <aleung-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/03 14:15:21 by aleung-c          #+#    #+#             */
/*   Updated: 2015/12/03 14:15:21 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

t_vector3 set_vec3(double x, double y, double z)
{
	t_vector3 ret;

	ret.x = x;
	ret.y = y;
	ret.z = z;
	return (ret);
}

t_vector3	point_from_vecdir(t_vector3 origine, t_vector3 vec_dir)
{
	// return le point origine + vecdir. Utile pour les limites.
	t_vector3	ret_point;

	ret_point.x = origine.x + vec_dir.x;
	ret_point.y = origine.y + vec_dir.y;
	ret_point.z = origine.z + vec_dir.z;
	return (ret_point);
}

t_vector3 vec_dir(t_vector3 origine, t_vector3 destination)
{
	// return le vecteur de directions entre les deux points.
	t_vector3 distance;

	distance.x = destination.x - origine.x;
	distance.y = destination.y - origine.y;
	distance.z = destination.z - origine.z;
	return (distance);
}

double vector_length(t_vector3 vec_dir)
{
	double ret;

	ret = vec_dir.x + vec_dir.y + vec_dir.z;
	return (ret);
}

t_vector3 vec_dir_distance_normalized(t_vector3 origine, t_vector3 destination)
{
	// return un vec de direction avec distance normalisée;
	t_vector3		ret;

	ret.x = destination.x - origine.x;
	ret.y = destination.y - origine.y;
	ret.z = destination.z - origine.z;
	ret = normalize_vector(ret);
	return (ret);
}

double distance(t_vector3 origine, t_vector3 destination)
{
	// return une val de distance pour comparaison;
	double		ret;

	ret = sqrt(
		pow(destination.x - origine.x, 2.0) +
		pow(destination.y - origine.y, 2.0) +
		pow(destination.z - origine.z, 2.0));
	return (ret);
}

t_vector3 normalize_vector(t_vector3 v)
{
	// normalise un vecteur de distance.
	t_vector3	ret;
	double	normal;

	normal = norme(v);
	ret.x = v.x / normal;
	ret.y = v.y / normal;
	ret.z = v.z / normal;
	return (ret);
}

double	norme(t_vector3 v)
{
	return (sqrt((v.x * v.x) + (v.y * v.y) + (v.z * v.z)));
}

t_vector3	do_rotate(double rot[3][3], t_vector3 p)
{
	t_vector3	ret;
	double	x;
	double	y;
	double	z;

	x = p.x;
	y = p.y;
	z = p.z;
	ret.x = x * rot[0][0] + y * rot[0][1] + z * rot[0][2];
	ret.y = x * rot[1][0] + y * rot[1][1] + z * rot[1][2];
	ret.z = x * rot[2][0] + y * rot[2][1] + z * rot[2][2];
	return (ret);
}