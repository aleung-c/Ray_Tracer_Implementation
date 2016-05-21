/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_rotation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/19 16:13:14 by aleung-c          #+#    #+#             */
/*   Updated: 2016/05/19 16:13:17 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

t_vector3	vector(t_vector3 a, t_vector3 b)
{
	t_vector3		ret;

	ret.x = a.y * b.z - a.z * b.y;
	ret.y = a.z * b.x - a.x * b.z;
	ret.z = a.x * b.y - a.y * b.x;
	return (ret);
}

t_vector3	do_rotate(double rot[3][3], t_vector3 p)
{
	t_vector3		ret;
	double			x;
	double			y;
	double			z;

	x = p.x;
	y = p.y;
	z = p.z;
	ret.x = x * rot[0][0] + y * rot[0][1] + z * rot[0][2];
	ret.y = x * rot[1][0] + y * rot[1][1] + z * rot[1][2];
	ret.z = x * rot[2][0] + y * rot[2][1] + z * rot[2][2];
	return (ret);
}

void		get_rotate(t_vector3 axe, double cos, double rot[3][3])
{
	double	sin;

	sin = sqrt(1 - pow(cos, 2));
	axe = normalize_vector(axe);
	rot[0][0] = pow(axe.x, 2) + (1 - pow(axe.x, 2)) * cos;
	rot[1][0] = axe.x * axe.y * (1 - cos) - axe.z * sin;
	rot[2][0] = axe.x * axe.z * (1 - cos) + axe.y * sin;
	rot[0][1] = axe.x * axe.y * (1 - cos) + axe.z * sin;
	rot[1][1] = pow(axe.y, 2) + (1 - pow(axe.y, 2)) * cos;
	rot[2][1] = axe.y * axe.z * (1 - cos) - axe.x * sin;
	rot[0][2] = axe.x * axe.z * (1 - cos) - axe.y * sin;
	rot[1][2] = axe.y * axe.z * (1 - cos) + axe.x * sin;
	rot[2][2] = pow(axe.z, 2) + (1 - pow(axe.z, 2)) * cos;
}

void		get_rotate_angle(t_vector3 axe, double angle, double rot[3][3])
{
	double	v_cos;
	double	v_sin;

	v_cos = cos(RAD(angle));
	v_sin = sin(RAD(angle));
	axe = normalize_vector(axe);
	rot[0][0] = pow(axe.x, 2) + (1 - pow(axe.x, 2)) * v_cos;
	rot[1][0] = axe.x * axe.y * (1 - v_cos) - axe.z * v_sin;
	rot[2][0] = axe.x * axe.z * (1 - v_cos) + axe.y * v_sin;
	rot[0][1] = axe.x * axe.y * (1 - v_cos) + axe.z * v_sin;
	rot[1][1] = pow(axe.y, 2) + (1 - pow(axe.y, 2)) * v_cos;
	rot[2][1] = axe.y * axe.z * (1 - v_cos) - axe.x * v_sin;
	rot[0][2] = axe.x * axe.z * (1 - v_cos) - axe.y * v_sin;
	rot[1][2] = axe.y * axe.z * (1 - v_cos) + axe.x * v_sin;
	rot[2][2] = pow(axe.z, 2) + (1 - pow(axe.z, 2)) * v_cos;
}
