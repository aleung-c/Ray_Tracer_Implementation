/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/21 16:23:11 by aleung-c          #+#    #+#             */
/*   Updated: 2016/05/21 16:23:13 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rtv1.h"

int			key_press(int keycode, t_rt *rt)
{
	if (rt && keycode == 53)
	{
		ft_putendl("Exit RTv1");
		exit(0);
	}
	return (0);
}

char		*pixel_put_to_image(t_rt *rt, int x, int y, int color)
{
	ft_memcpy(&rt->img[(y * rt->sizeline) + (x * (rt->bpp / 8))], &color, \
		sizeof(int));
	return (rt->img);
}

int			expose_hook(t_rt *rt)
{
	int ret;

	ret = 0;
	mlx_put_image_to_window(rt->mlx, rt->win, rt->imgv, 0, 0);
	return (ret);
}

void		init_mlx(t_rt *rt)
{
	if (!(rt->mlx = mlx_init()))
		exit(0);
	if (!(rt->win = mlx_new_window(rt->mlx, \
	rt->screen_width, rt->screen_height, "RTv1")))
		exit(0);
	rt->imgv = mlx_new_image(rt->mlx, rt->screen_width, rt->screen_height);
	rt->img = mlx_get_data_addr(rt->imgv, &rt->bpp, &rt->sizeline, &rt->endian);
	raytrace_once(rt);
	mlx_expose_hook(rt->win, expose_hook, rt);
	mlx_key_hook(rt->win, key_press, rt);
	mlx_loop_hook(rt->mlx, ft_trace_rt, rt);
	mlx_loop(rt->mlx);
	mlx_destroy_image(rt->mlx, rt->imgv);
}

void		raytrace_once(t_rt *rt)
{
	trace_black_screen(rt);
	raytrace_objs(rt);
	if (rt->has_inner_shadows == 1)
		calculate_inner_shadows(rt);
	if (rt->has_shining == 1)
		calcultate_shining(rt);
	if (rt->has_casted_shadows == 1)
		calculate_casted_shadows(rt);
}
