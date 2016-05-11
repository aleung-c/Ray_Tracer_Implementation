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
	int scan_x;
	int scan_y;
	int i;
	int color;

	scan_x = 0;
	scan_y = 0;
	i = 0;
	color = 0x000000;
	while (scan_y < rt->screen_height) // pour chaque colonne.
	{
		while (scan_x < rt->screen_width) // pour chaque ligne de pixel.
		{
			pixel_put_to_image(rt, scan_x, scan_y, color);
			scan_x++;
			i++;
		}
		scan_y++;
		scan_x = 0;
	}
}

void run_trough_objs(t_rt *rt, t_screen_vec *vp_vector)
{
	t_scene_object	*tmp;

	tmp = rt->scene_objs;

	// parcourir tous les objs.
	while (tmp) {
		if (tmp->type == SPHERE) {
			sphere_check(vp_vector, tmp, rt->camera.camera_obj->pos, vp_vector->v);
		}
		else if (tmp->type == PLANE) {
			plane_check(vp_vector, tmp, rt->camera.camera_obj->pos, vp_vector->v);
		}
		tmp = tmp->next;
	}
}

void raytrace_objs(t_rt *rt) // pour calculer tous les objs
{
	int scan_x;
	int scan_y;
	int i;

	scan_x = 0;
	scan_y = 0;
	i = 0;
	//color = 0x000000; // base color = black;
	while (scan_y < rt->screen_height) // pour chaque colonne.
	{
		while (scan_x < rt->screen_width) // pour chaque ligne de pixel.
		{
			// fait le check du vec actuel pour chaque obj de la scene en fonction de son type.
			// vecteur actuel == rt->vp_vectors[i]
			// pour chaque obj, regarder le type, puis lenvoyer pour calculer dans l'algo correspondant.
			run_trough_objs(rt, &(rt->vp_vectors[i]));	
			scan_x++;
			i++;
		}
		scan_y++;
		scan_x = 0;
	}
}

void display_rt(t_rt *rt)
{
	int scan_x;
	int scan_y;
	int i;

	scan_x = 0;
	scan_y = 0;
	i = 0;
	//color = 0x000000; // base color = black;
	while (scan_y < rt->screen_height) // pour chaque colonne.
	{
		while (scan_x < rt->screen_width) // pour chaque ligne de pixel.
		{
			if (rt->vp_vectors[i].touched_objs_list == NULL) {
				// no touch, put black;
				pixel_put_to_image(rt, scan_x, scan_y, 0x000000);
			}
			else 
			{
				//t_scene_object	*closest_obj;
				//closest_obj = get_closest_object(&(rt->vp_vectors[i]));
				//pixel_put_to_image(rt, scan_x, scan_y, closest_obj->color);
				pixel_put_to_image(rt, scan_x, scan_y, rt->vp_vectors[i].touched_objs_list->color);
			}
			// fait le check du vec actuel pour chaque obj de la scene en fonction de son type.
			// vecteur actuel == rt->vp_vectors[i]
			// pour chaque obj, regarder le type, puis lenvoyer pour calculer dans l'algo correspondant.
			
			// sphere_check(rt, rt->camera.pos, vec_dir); // a changé.
			scan_x++;
			i++;
		}
		scan_y++;
		scan_x = 0;
	}
}

int ft_trace_rt(t_rt *rt)
{
	trace_black_screen(rt);
	
	raytrace_objs(rt);
	calculate_shadows(rt);
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

void calculate_viewplane(t_rt *rt)
{
	int y;
	int x;
	int i;
	double xref;
	double yref;
	double zref;
	double inc_x;
	double inc_z;
	// pas besoin du y, l'ecran est plat.

	// remplir le viewplane positioning en dur avant de le rotate avec une matrice 
	// qui prendra l'angle en compte.
	
	// *** Y avance, X strafe, Z altitude. **** //
	
	// cam est a 1.0 1.0 1.0 au debut.
	// angle est a 0.0, 0.0, 0.0 ;
	// screen est de 400 x 000.

	// calcul des points interessants du viewplane.
	// vecteur point central = pos_cam - pos_cam avec y+dist to screen;
	rt->vp_center_pos.x = rt->camera.camera_obj->pos.x;
	rt->vp_center_pos.y = rt->camera.camera_obj->pos.y + rt->camera.camera_obj->dist_cam_screen;
	rt->vp_center_pos.z = rt->camera.camera_obj->pos.z;

	/*rt->vp_up_pos.x = rt->camera.camera_obj->pos.x;
	rt->vp_up_pos.y = rt->camera.camera_obj->pos.y + rt->camera.camera_obj->dist_cam_screen;
	rt->vp_up_pos.z = rt->camera.camera_obj->pos.z + 1.0;

	rt->vp_right_pos.x = rt->camera.camera_obj->pos.x + 1.0;
	rt->vp_right_pos.y = rt->camera.camera_obj->pos.y + rt->camera.camera_obj->dist_cam_screen;
	rt->vp_right_pos.z = rt->camera.camera_obj->pos.z;*/

	float vecdir_cam_screen_y = rt->vp_center_pos.y - rt->camera.camera_obj->pos.y;

	vecdir_cam_screen_y *= vecdir_cam_screen_y; // au carre. longueur au carre
	vecdir_cam_screen_y += 1.0; // == largeur de la moitie de lecran en fonction de x au carre
	vecdir_cam_screen_y = sqrt(vecdir_cam_screen_y);


	rt->vp_upleft_pos.x = rt->camera.camera_obj->pos.x - 1.0;
	rt->vp_upleft_pos.y = rt->camera.camera_obj->pos.y + rt->camera.camera_obj->dist_cam_screen;
	rt->vp_upleft_pos.z = rt->camera.camera_obj->pos.z + 1.0;


	// CHECK LOGS //
	// printf("rt->vp_center_pos : %f x, %f y, %f z;\n", rt->vp_center_pos.x, rt->vp_center_pos.y, rt->vp_center_pos.z);
	// printf("rt->vp_up_pos : %f x, %f y, %f z;\n", rt->vp_up_pos.x, rt->vp_up_pos.y, rt->vp_up_pos.z);
	// printf("rt->vp_right_pos : %f x, %f y, %f z;\n", rt->vp_right_pos.x, rt->vp_right_pos.y, rt->vp_right_pos.z);
	// printf("rt->vp_upleft_pos : %f x, %f y, %f z;\n", rt->vp_upleft_pos.x, rt->vp_upleft_pos.y, rt->vp_upleft_pos.z);

	rt->vp_vectors[0].v.x = rt->vp_upleft_pos.x - rt->camera.camera_obj->pos.x;
	rt->vp_vectors[0].v.y = rt->vp_upleft_pos.y - rt->camera.camera_obj->pos.y;
	rt->vp_vectors[0].v.z = rt->vp_upleft_pos.z - rt->camera.camera_obj->pos.z;
	// printf("rt->vp_vectors[0] : %f x, %f y, %f z;\n", rt->vp_vectors[0].x, rt->vp_vectors[0].y, rt->vp_vectors[0].z);

	// calcul des vectors pour chaque pixel de l'ecran.
	y = 0;
	x = 1;
	i = 1;
	inc_x = 2.0 / (float)rt->screen_width;
	inc_z = 2.0 / (float)rt->screen_height;
	xref = rt->vp_upleft_pos.x;
	yref = rt->vp_vectors[0].v.y;
	zref = rt->vp_upleft_pos.z;
	while (y < rt->screen_height)
	{
		while (x < rt->screen_width)
		{
			xref += inc_x;
			rt->vp_vectors[i].v.x = xref - rt->camera.camera_obj->pos.x;
			rt->vp_vectors[i].v.y = yref;
			rt->vp_vectors[i].v.z = zref - rt->camera.camera_obj->pos.z;
			rt->vp_vectors[i].touched_objs_list = NULL;
			i++;
			x++;
		}
		xref = rt->vp_upleft_pos.x;
		zref -= inc_z; // changement de hauteur de colonne, donc baisser le z
		x = 0;
		y++;
	}
	/*i = 0;
	int  sc_size = rt->screen_height * rt->screen_width;
	while (i < sc_size) {
		printf("VLength = %f \n", vector_length(rt->vp_vectors[i].v));
		i++;
	}*/
	// printf("rt->vp_vectors[last] : %f x, %f y, %f z;\n", rt->vp_vectors[400 + 200 * 400].x, rt->vp_vectors[400 + 200 * 400].y, rt->vp_vectors[400 + 200 * 400].z);
}

void rotate_viewplane(t_rt *rt) // Incomplet, non fonctionnel.
{
	int y;
	int x;
	int i;

	y = 0;
	x = 0;
	i = 0;
	while (y < rt->screen_height)
	{
		while (x < rt->screen_width)
		{
			rt->vp_vectors[i].v.x = ((rt->vp_vectors[i].v.x * cos(rt->camera.camera_obj->euler_angles.x)) + (rt->vp_vectors[i].v.y - sin(rt->camera.camera_obj->euler_angles.y)) + 0);
			rt->vp_vectors[i].v.y = ((rt->vp_vectors[i].v.x * sin(rt->camera.camera_obj->euler_angles.x)) + (rt->vp_vectors[i].v.y * cos(rt->camera.camera_obj->euler_angles.y)) + 0);
			rt->vp_vectors[i].v.z = (0 + 0 + rt->vp_vectors[i].v.z * 1);

			// //rotate x ;
			// rt->vp_vectors[i].x = ((rt->vp_vectors[i].x * 1) + (rt->vp_vectors[i].y * 0) + (rt->vp_vectors[i].y * 0));
			// rt->vp_vectors[i].y = ((rt->vp_vectors[i].x * 0) + (rt->vp_vectors[i].y * cos(rt->cam_angle_x)) + (rt->vp_vectors[i].y - sin(rt->cam_angle_x)));
			// rt->vp_vectors[i].z = ((rt->vp_vectors[i].x * 0) + (rt->vp_vectors[i].y * sin(rt->cam_angle_x)) + (rt->vp_vectors[i].y * cos(rt->cam_angle_x)));
			// //rotate y ;
			// rt->vp_vectors[i].x = ((rt->vp_vectors[i].x * cos(rt->cam_angle_y)) + (rt->vp_vectors[i].y * 0) + (rt->vp_vectors[i].y * sin(rt->cam_angle_y)));
			// rt->vp_vectors[i].y = ((rt->vp_vectors[i].x * 0) + (rt->vp_vectors[i].y * 1) + (rt->vp_vectors[i].y * 0));
			// rt->vp_vectors[i].z = ((rt->vp_vectors[i].x - sin(rt->cam_angle_y)) + (rt->vp_vectors[i].y * 0) + (rt->vp_vectors[i].y * cos(rt->cam_angle_y)));
			// //rotate z ;
			// rt->vp_vectors[i].x = ((rt->vp_vectors[i].x * cos(rt->cam_angle_z)) + (rt->vp_vectors[i].y - sin(rt->cam_angle_z)) + (rt->vp_vectors[i].y * 0));
			// rt->vp_vectors[i].y = ((rt->vp_vectors[i].x * sin(rt->cam_angle_z)) + (rt->vp_vectors[i].y * cos(rt->cam_angle_z)) + (rt->vp_vectors[i].y * 0));
			// rt->vp_vectors[i].z = ((rt->vp_vectors[i].x * 0) + (rt->vp_vectors[i].y * 0) + (rt->vp_vectors[i].y * 1));
			i++;
			x++;
		}
		x = 0;
		y++;
	}
	printf("rotate -\nrt->vp_vectors[last] : %f x, %f y, %f z;\n",
	rt->vp_vectors[400 + 200 * 400].v.x, rt->vp_vectors[400 + 200 * 400].v.y, rt->vp_vectors[400 + 200 * 400].v.z);
}

void init_var(t_rt *rt) // Definir scene.
{
	t_vector3 pos;
	t_vector3 normale;
	// defining screen var //
	rt->screen_height = SCREEN_H;
	rt->screen_width = SCREEN_W;

	rt->vp_vectors = malloc(sizeof(t_screen_vec) * (rt->screen_height * rt->screen_width)); // allocation viewplane vectors.

	// defining main cam var //
	rt->camera.type = CAM;
	rt->camera.camera_obj = (t_camera *)malloc(sizeof(t_camera));
	rt->camera.camera_obj->pos.x = 0.0;
	rt->camera.camera_obj->pos.y = 0.0;
	rt->camera.camera_obj->pos.z = 1.0;
	rt->camera.camera_obj->euler_angles.x = 0.0;
	rt->camera.camera_obj->euler_angles.y = 0.0;
	rt->camera.camera_obj->euler_angles.z = 0.0;

	rt->camera.camera_obj->dist_cam_screen = 1.0;

	// --- LIGHT
	//pos = set_vec3(-1.5, 5.0, 2.0);
	pos = set_vec3(0.0, 0.0, 0.0);
	add_light_to_scene(rt, pos, 1.0);

	// --- SPHERES 
	
	// adding sphere //
	//pos = set_vec3(0.5, 5.0, 1.0);
	//add_sphere_to_scene(rt, pos, 2.0, 2.0, 0x006600); // sphere verte
	
	// adding sphere //
	pos = set_vec3(2.0, 5.0, 2.0);
	add_sphere_to_scene(rt, pos, 1.0, 1.0, 0x0066FF); // sphere bleu
	
	// adding sphere //
	pos = set_vec3(-0.5, 5.0, 2.0);
	add_sphere_to_scene(rt, pos, 1.0, 0.5, 0x660000); // sphere rouge

	// --- PLANES //
	
	// adding plane //
	normale = set_vec3(0.0, 0.0, 1.0);
	pos = set_vec3(0.0, 0.0, 0.0);
	add_plane_to_scene(rt, pos, normale, 0x669999); // plan vert
	
	// adding plane //
	//normale = set_vec3(1.0, 0.0, 0.0);
	//pos = set_vec3(0.0, 0.0, 0.0);
	//add_plane_to_scene(rt, pos, normale, 0x6699FF); // plan bleu

	// adding plane //
	normale = set_vec3(0.0, 1.0, 0.0);
	pos = set_vec3(0.0, 100, 0.0);
	add_plane_to_scene(rt, pos, normale, 0x663366); // plan violet

	// DEBUG ---------- //
	// OBJ DEBUG
	t_scene_object *tmp;
	int i;

	i = 0;
	tmp = rt->scene_objs;
	while (tmp) {
		i++;
		if (tmp->type == SPHERE) {
			printf("Add sphere to scene \n");
		}
		tmp = tmp->next;
	}
	printf("Scene :\n");
	printf("Nombre d'objets : %d \n", i);
	// LIGHT DEBUG
	t_light *tmp_light;

	i = 0;
	tmp_light = rt->scene_lights;
	while (tmp_light) {
		i++;
		tmp_light = tmp_light->next;
	}
	printf("Nombre de lights : %d \n", i);

	// DEBUG End --------- //
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

	ft_trace_rt(rt);

	mlx_expose_hook(rt->win, expose_hook, rt);
	//mlx_hook(rt->win, 2, (1L<<0), &key_press, rt); // ????? ne semble pas marcher.
	mlx_hook(rt->win, KeyPress, KeyPressMask, key_press, rt);
	mlx_loop_hook(rt->mlx, ft_trace_rt, rt);
	mlx_loop(rt->mlx);
	mlx_destroy_image(rt->mlx, rt->imgv);
}

void RTv1()
{
	t_rt rt;
	rt.scene_objs = NULL; // init list chainee d'objs.
	rt.scene_lights = NULL;
	init_var(&rt);
	calculate_viewplane(&rt);
	//rotate_viewplane(&rt); //  Optionnel : ne fonctionne pas ....
	init_mlx(&rt);
}

int main(void)
{
	RTv1();
	return (0);
}
