/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/16 14:59:33 by aleung-c          #+#    #+#             */
/*   Updated: 2016/05/16 14:59:36 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"
#include <stdio.h> //

t_rgb	hex_to_rgb(int hex_color)
{
	t_rgb	rgb_color;

	rgb_color.r = (((hex_color >> 16) & 0xFF));
	rgb_color.g = (((hex_color >> 8) & 0xFF));
	rgb_color.b = (((hex_color) & 0xFF));
	return (rgb_color);
}

int		rgb_to_hex(t_rgb rgb_color)
{
	int ret;

	ret =
		((rgb_color.r & 0xff) << 16) +
		((rgb_color.g & 0xff) << 8) +
		(rgb_color.b & 0xff);
	return (ret);
}