/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_angles.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <aleung-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/03 15:52:12 by aleung-c          #+#    #+#             */
/*   Updated: 2015/12/03 15:52:13 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

double	angle_check(double angle)
{
	if (angle > 360.0)
		angle -= 360.0;
	if (angle < 0.0)
		angle += 360.0;
	return (angle);
}

int		angle_rev(int angle)
{
	int angle_rev;

	angle_rev = angle + 180.0;
	if (angle_rev > 360.0)
		angle_rev = angle_rev - 360.0;
	return (angle_rev);
}

double	scalar(t_vector3 a, t_vector3 b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}
