/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_rt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/21 16:46:45 by aleung-c          #+#    #+#             */
/*   Updated: 2016/05/21 16:46:47 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

int		ft_trace_rt(t_rt *rt)
{
	display_rt(rt);
	return (0);
}

void	display_rt(t_rt *rt)
{
	rt->scan_x = 0;
	rt->scan_y = 0;
	rt->i = 0;
	while (rt->scan_y < rt->screen_height)
	{
		while (rt->scan_x < rt->screen_width)
		{
			if (rt->vp_vectors[rt->i].touched_objs_list == NULL)
				pixel_put_to_image(rt, rt->scan_x, rt->scan_y,
									0x000000);
			else
				pixel_put_to_image(rt, rt->scan_x, rt->scan_y,
					rt->vp_vectors[rt->i].touched_objs_list->
					display_color);
			rt->scan_x++;
			rt->i++;
		}
		rt->scan_y++;
		rt->scan_x = 0;
	}
}

void	trace_black_screen(t_rt *rt)
{
	rt->scan_x = 0;
	rt->scan_y = 0;
	rt->i = 0;
	rt->color = 0x000000;
	while (rt->scan_y < rt->screen_height)
	{
		while (rt->scan_x < rt->screen_width)
		{
			pixel_put_to_image(rt, rt->scan_x, rt->scan_y,
								rt->color);
			rt->scan_x++;
			rt->i++;
		}
		rt->scan_y++;
		rt->scan_x = 0;
	}
}
