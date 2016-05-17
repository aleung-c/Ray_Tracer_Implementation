/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RTv1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <aleung-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/21 12:59:16 by aleung-c          #+#    #+#             */
/*   Updated: 2015/10/01 09:25:50 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "RTv1.h"
#include <stdio.h> //

int		key_press(int keycode, t_rt *rt)
{
	if (keycode == 124) // right
		rt->camera.camera_obj->pos.x += 0.5; 
	else if (keycode == 123) // left
		rt->camera.camera_obj->pos.x -= 0.5;
	else if (keycode == 65362 || keycode == 126) // up
		rt->camera.camera_obj->pos.y += 0.5;
	else if (keycode == 65364 || keycode == 125) // down
		rt->camera.camera_obj->pos.y -= 0.5;
	else if (keycode == 65307)
	{
		ft_putendl("Exit RTv1");
		exit(0);
	}
	return (0);
}



char *pixel_put_to_image(t_rt *rt, int x, int y, int color)
{
	ft_memcpy(&rt->img[(y * rt->sizeline) + (x * (rt->bpp / 8))], &color, \
		sizeof(int));
	return (rt->img);
}

int set_color(double sum_vect) // set pixel color screen depending on vector sum.
{
	int r;
	int g;
	int b;

	sum_vect *= 30; // a un impact sur la puissance de la lumiere.

	r = (255 - (int)sum_vect);
	g = (255 - (int)sum_vect);
	b = (255 - (int)sum_vect);

	return ((r << 16) + (g << 8) + b);
}

void trace_black_screen(t_rt *rt) // pour remplir lecran de noir. => protect ecran non alloue.
{
	rt->scan_x = 0;
	rt->scan_y = 0;
	rt->i = 0;
	rt->color = 0x000000;
	while (rt->scan_y < rt->screen_height) // pour chaque colonne.
	{
		while (rt->scan_x < rt->screen_width) // pour chaque ligne de pixel.
		{
			pixel_put_to_image(rt, rt->scan_x, rt->scan_y, rt->color);
			rt->scan_x++;
			rt->i++;
		}
		rt->scan_y++;
		rt->scan_x = 0;
	}
}

void run_trough_objs(t_rt *rt, t_screen_vec *vp_vector)
{
	rt->tmp = rt->scene_objs;

	// parcourir tous les objs.
	while (rt->tmp)
	{
		if (rt->tmp->type == SPHERE)
		{
			sphere_check(vp_vector, rt->tmp, rt->camera.camera_obj->pos, vp_vector->v);
		}
		else if (rt->tmp->type == PLANE)
		{
			plane_check(vp_vector, rt->tmp, rt->camera.camera_obj->pos, vp_vector->v);
		}
		else if (rt->tmp->type == CYLINDER)
		{
			cylinder_check(vp_vector, rt->tmp, rt->camera.camera_obj->pos, vp_vector->v);
		}
		else if (rt->tmp->type == CONE)
		{
			cone_check(vp_vector, rt->tmp, rt->camera.camera_obj->pos, vp_vector->v);
		}
		rt->tmp = rt->tmp->next;
	}
}

void raytrace_objs(t_rt *rt) // pour calculer tous les objs
{
	rt->scan_x = 0;
	rt->scan_y = 0;
	rt->i = 0;
	//color = 0x000000; // base color = black;
	while (rt->scan_y < rt->screen_height) // pour chaque colonne.
	{
		while (rt->scan_x < rt->screen_width) // pour chaque ligne de pixel.
		{
			// fait le check du vec actuel pour chaque obj de la scene en fonction de son type.
			// vecteur actuel == rt->vp_vectors[i]
			// pour chaque obj, regarder le type, puis lenvoyer pour calculer dans l'algo correspondant.
			run_trough_objs(rt, &(rt->vp_vectors[rt->i]));
			rt->scan_x++;
			rt->i++;
		}
		rt->scan_y++;
		rt->scan_x = 0;
	}
}

void display_rt(t_rt *rt)
{
	rt->scan_x = 0;
	rt->scan_y = 0;
	rt->i = 0;
	while (rt->scan_y < rt->screen_height) // pour chaque colonne.
	{
		while (rt->scan_x < rt->screen_width) // pour chaque ligne de pixel.
		{
			if (rt->vp_vectors[rt->i].touched_objs_list == NULL) {
				// no touch, put black; -> crash security;
				pixel_put_to_image(rt, rt->scan_x, rt->scan_y, 0x000000);
			}
			else
			{
				pixel_put_to_image(rt, rt->scan_x, rt->scan_y, 
					rt->vp_vectors[rt->i].touched_objs_list->display_color);
			}
			rt->scan_x++;
			rt->i++;
		}
		rt->scan_y++;
		rt->scan_x = 0;
	}
}

int ft_trace_rt(t_rt *rt)
{	
	display_rt(rt); // parcours les vec et affiche les colors.
	return (0);
}

int		expose_hook(t_rt *rt)
{
	int ret;

	ret = 0;
	mlx_put_image_to_window(rt->mlx, rt->win, rt->imgv, 0, 0);
	return (ret);
}





void init_mlx(t_rt *rt)
{
	if (!(rt->mlx = mlx_init()))
		exit(0);
	if (!(rt->win = mlx_new_window(rt->mlx, \
	rt->screen_width, rt->screen_height, "RTv1")))
		exit (0);
	rt->imgv = mlx_new_image(rt->mlx, rt->screen_width, rt->screen_height);
	rt->img = mlx_get_data_addr(rt->imgv, &rt->bpp, &rt->sizeline, &rt->endian);

	// Raytrace once;
	trace_black_screen(rt);
	raytrace_objs(rt);
	if (rt->has_inner_shadows == 1)
		calculate_inner_shadows(rt);
	if (rt->has_casted_shadows == 1)
		calculate_casted_shadows(rt); // casted overrides inner.
//	ft_trace_rt(rt);

	mlx_expose_hook(rt->win, expose_hook, rt);
	//mlx_hook(rt->win, 2, (1L<<0), &key_press, rt); // ????? ne semble pas marcher.
	mlx_hook(rt->win, KeyPress, KeyPressMask, key_press, rt);
	mlx_loop_hook(rt->mlx, ft_trace_rt, rt);
	mlx_loop(rt->mlx);
	mlx_destroy_image(rt->mlx, rt->imgv);
}

void RTv1(int scene_number)
{
	t_rt rt;
	rt.scene_objs = NULL; // init list chainee d'objs.
	rt.scene_lights = NULL;
	rt.scene_number = scene_number;
	init_entry(&rt);
	calculate_viewplane(&rt);
	//rotate_viewplane(&rt); //  Optionnel : ne fonctionne pas ....
	init_mlx(&rt);
}

int main(int argc, char **argv)
{
	if (argc == 2 && (ft_strlen(argv[1]) == 1) 
		&& (argv[1][0] >= '1' && argv[1][0] <= '7'))
	{
		RTv1(ft_atoi(argv[1]));
	}
	else
	{
		ft_putendl ("Usage: ./RTv1 [1-7]");
		return (-1);
	}
	return (0);
}
