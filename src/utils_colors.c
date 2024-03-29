/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/21 16:58:15 by aleung-c          #+#    #+#             */
/*   Updated: 2016/05/21 16:58:19 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

t_rgb		hex_to_rgb(int hex_color)
{
	t_rgb	rgb_color;

	rgb_color.r = (((hex_color >> 16) & 0xFF));
	rgb_color.g = (((hex_color >> 8) & 0xFF));
	rgb_color.b = (((hex_color) & 0xFF));
	return (rgb_color);
}

int			rgb_to_hex(t_rgb rgb_color)
{
	int ret;

	ret =
		((rgb_color.r & 0xff) << 16) +
		((rgb_color.g & 0xff) << 8) +
		(rgb_color.b & 0xff);
	return (ret);
}

void		check_limit_darkening(t_rgb *rgb_color)
{
	if (rgb_color->r < 0)
		rgb_color->r = 0;
	if (rgb_color->g < 0)
		rgb_color->g = 0;
	if (rgb_color->b < 0)
		rgb_color->b = 0;
}

void		check_limit_brightening(t_rgb *rgb_color)
{
	if (rgb_color->r > 255)
		rgb_color->r = 255;
	if (rgb_color->g > 255)
		rgb_color->g = 255;
	if (rgb_color->b > 255)
		rgb_color->b = 255;
}
