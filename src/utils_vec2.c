/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_vec2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/21 17:07:16 by aleung-c          #+#    #+#             */
/*   Updated: 2016/05/21 17:07:19 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

t_vector3		normalize_vector(t_vector3 v)
{
	t_vector3	ret;
	double		normal;

	normal = norme(v);
	ret.x = v.x / normal;
	ret.y = v.y / normal;
	ret.z = v.z / normal;
	return (ret);
}

double			norme(t_vector3 v)
{
	return (sqrt((v.x * v.x) + (v.y * v.y) + (v.z * v.z)));
}

void			create_vertical_norm(t_vector3 *norm)
{
	norm->x = 0;
	norm->y = 0;
	norm->z = 1;
}

double			distance(t_vector3 origine, t_vector3 destination)
{
	double		ret;

	ret = sqrt(
		pow(destination.x - origine.x, 2.0) +
		pow(destination.y - origine.y, 2.0) +
		pow(destination.z - origine.z, 2.0));
	return (ret);
}

t_vector3		translate(t_vector3 p, t_vector3 v)
{
	t_vector3		ret;

	ret.x = p.x + v.x;
	ret.y = p.y + v.y;
	ret.z = p.z + v.z;
	return (ret);
}
