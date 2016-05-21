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

#include "../includes/rtv1.h"

t_vector3		set_vec3(double x, double y, double z)
{
	t_vector3 ret;

	ret.x = x;
	ret.y = y;
	ret.z = z;
	return (ret);
}

t_vector3		point_from_vecdir(t_vector3 origine, t_vector3 vec_dir)
{
	t_vector3	ret_point;

	ret_point.x = origine.x + vec_dir.x;
	ret_point.y = origine.y + vec_dir.y;
	ret_point.z = origine.z + vec_dir.z;
	return (ret_point);
}

t_vector3		vec_dir(t_vector3 origine, t_vector3 destination)
{
	t_vector3 distance;

	distance.x = destination.x - origine.x;
	distance.y = destination.y - origine.y;
	distance.z = destination.z - origine.z;
	return (distance);
}

double			vector_length(t_vector3 vec_dir)
{
	double ret;

	ret = vec_dir.x + vec_dir.y + vec_dir.z;
	return (ret);
}

t_vector3		vec_dir_distance_normalized(t_vector3 origine,
										t_vector3 destination)
{
	t_vector3		ret;

	ret.x = destination.x - origine.x;
	ret.y = destination.y - origine.y;
	ret.z = destination.z - origine.z;
	ret = normalize_vector(ret);
	return (ret);
}
