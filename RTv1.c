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

void run_trough_objs(t_rt *rt, t_screen_vec *vp_vector) {
	t_scene_object	*tmp;

	tmp = rt->scene_objs;

	// parcourir tous les objs.
	while (tmp) {
		if (tmp->type == SPHERE) {
			sphere_check(vp_vector, tmp, rt->camera.camera_obj->pos, vp_vector->v);
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
				// sphere_check(rt, rt->camera.pos, vec_dir); // a changé.
			
			
			scan_x++;
			i++;
		}
		scan_y++;
		scan_x = 0;
	}

}



/*void trace_sphere(t_rt *rt) // pour calculer la sphere dans la scene
{
	int scan_x;
	int scan_y;
	int i;

	

	scan_x = 0;
	scan_y = 0;
	i = 0;
	color = 0x000000; // base color = black;
	while (scan_y < rt->screen_height) // pour chaque colonne.
	{
		while (scan_x < rt->screen_width) // pour chaque ligne de pixel.
		{
			// calculs preliminaires pour la sphere
			// le vec actuel
			double vx;
		double vy;
		double vz;
		
		t_sphere_algo algo; // contient toutes les val pour calculer.

		t_vector3 s_vect;
		double sum_vect;
		int color;


		vx = rt->vp_vectors[i].x;
		vy = rt->vp_vectors[i].y;
		vz = rt->vp_vectors[i].z;

		algo.a = (vx * vx) + (vy * vy) + (vz * vz);

		algo.b = 2 * vx * (rt->cam_x - rt->sphere.centre.x) + 2 * vy * (rt->cam_y - rt->sphere.centre.y) + 2 * vz *(rt->cam_z - rt->sphere.centre.z);

		algo.c = rt->sphere.centre.x * rt->sphere.centre.x + rt->sphere.centre.y * rt->sphere.centre.y + rt->sphere.centre.z * rt->sphere.centre.z + 
			rt->cam_x * rt->cam_x + rt->cam_y * rt->cam_y + rt->cam_z * rt->cam_z
			+ -2*(rt->sphere.centre.x * rt->cam_x + rt->sphere.centre.y * rt->cam_y + rt->sphere.centre.z * rt->cam_z) 
			- rt->sphere.diametre * rt->sphere.radius;

		// regarder si touche une sphere en calculant le determinant;
		algo.det = algo.b * algo.b - 4 * algo.a * algo.c;
		// printf("det abc = %f\n", det);

		// calculer la position touchée;
		algo.t = (-algo.b - sqrt((algo.b * algo.b) - 4 * algo.a * algo.c)) / 2 * algo.a;
		algo.sx = rt->cam_x + algo.t * vx;
		algo.sy = rt->cam_y + algo.t * vy;
		algo.sz = rt->cam_z + algo.t * vz;
		//printf("sx = %f, sy = %f, sz = %f \n", sx, sy , sz); 
		s_vect.x = (sx - rt->sphere.centre.x) / rt->sphere.radius;
		s_vect.y = (sy - rt->sphere.centre.y) / rt->sphere.radius;
		s_vect.z = (sz - rt->sphere.centre.z) / rt->sphere.radius;
		sum_vect = fabs(s_vect.x) + fabs(s_vect.y) + fabs(s_vect.z); // somme des vect, indique une distance comparée.
		// printf("sum sphere vect = %f\n",  sum_vect);

		color = set_color(sum_vect);
		if (det >= 0.0)
			pixel_put_to_image(rt, scan_x, scan_y, color);

		
			
			
			scan_x++;
			i++;
		}
		scan_y++;
		scan_x = 0;
	}
}*/

// a conserver pour les formules.
/*void trace_plane(t_rt *rt) {
	int scan_x;
	int scan_y;
	int i;

	float dist;
	int color;

	double	t;
	double vx;
	double vy;
	double vz;
	//float sum_vect;

	scan_x = 0;
	scan_y = 0;
	i = 0;
	dist = 0.0;
	color = 0x000000; // base color = black;
	while (scan_y < rt->screen_height) // pour chaque colonne.
	{
		while (scan_x < rt->screen_width) // pour chaque ligne de pixel.
		{
			// le vec actuel;
			vx = rt->vp_vectors[i].x;
			vy = rt->vp_vectors[i].y;
			vz = rt->vp_vectors[i].z;

			// calcul dist plane - point;
			t = -(((rt->plane.normale.x * rt->cam_x) + (rt->plane.normale.y * rt->cam_y)
			+ (rt->plane.normale.z * rt->cam_z) + rt->plane.point.z)
			/ ((rt->plane.normale.x * vx) + (rt->plane.normale.y * vy)
			+ (rt->plane.normale.z * vz)));

			//sum_vect = fabs(s_vect.x) + fabs(s_vect.y) + fabs(s_vect.z); // somme des vect, indique une distance comparée.

			//color = set_color(sum_vect);
		
			if (t >= 0.0) {
				color = 0x00FF00;
				pixel_put_to_image(rt, scan_x, scan_y, color);
			}
			scan_x++;
			i++;
		}
		scan_y++;
		scan_x = 0;
	}
}*/

void display_rt(t_rt *rt) // pb avc les distances ....
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
			else {
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
	// trace_sphere(rt);
	// trace_plane(rt);
	

	raytrace_objs(rt);
	display_rt(rt); // parcours les vec et affiche les touchs calculés.


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

	rt->vp_up_pos.x = rt->camera.camera_obj->pos.x;
	rt->vp_up_pos.y = rt->camera.camera_obj->pos.y + rt->camera.camera_obj->dist_cam_screen;
	rt->vp_up_pos.z = rt->camera.camera_obj->pos.z + 1.0;

	rt->vp_right_pos.x = rt->camera.camera_obj->pos.x + 1.0;
	rt->vp_right_pos.y = rt->camera.camera_obj->pos.y + rt->camera.camera_obj->dist_cam_screen;
	rt->vp_right_pos.z = rt->camera.camera_obj->pos.z;

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
	inc_x = 2.0 / rt->screen_width;
	inc_z = 2.0 / rt->screen_height;
	xref = rt->vp_upleft_pos.x;
	yref = rt->vp_vectors[0].v.y; // juste a copier dans chaque case, l'ecran est plat.
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

	// defining screen var //
	rt->screen_height = SCREEN_H;
	rt->screen_width = SCREEN_W;

	rt->vp_vectors = malloc(sizeof(t_screen_vec) * (rt->screen_height * rt->screen_width)); // allocation viewplane vectors.

	// defining main cam var //
	rt->camera.type = CAM;
	rt->camera.camera_obj = (t_camera *)malloc(sizeof(t_camera)); // alloue l'obj.
	rt->camera.camera_obj->pos.x = 1.0;
	rt->camera.camera_obj->pos.y = 1.0;
	rt->camera.camera_obj->pos.z = 1.0;
	rt->camera.camera_obj->euler_angles.x = 0.0;
	rt->camera.camera_obj->euler_angles.y = 0.0;
	rt->camera.camera_obj->euler_angles.z = 0.0;

	rt->camera.camera_obj->dist_cam_screen = 1.0;

	// defining light values;
	rt->light.pos.x = 0.0;

	// adding sphere //
	//pos = set_vec3(0.5, 5.0, 1.0);
	//add_sphere_to_scene(rt, pos, 2.0, 2.0, 0x006600); // sphere verte
	// adding sphere //
	pos = set_vec3(1.5, 8.0, 1.0);
	add_sphere_to_scene(rt, pos, 2.0, 2.0, 0x0066FF); // sphere bleu
	// adding sphere //
	pos = set_vec3(-0.5, 8.5, 1.0);
	add_sphere_to_scene(rt, pos, 2.0, 2.0, 0x660000); // sphere rouge



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
	rt.scene_objs = NULL; // init list chainee dobjs.
	init_var(&rt);
	calculate_viewplane(&rt);
	//rotate_viewplane(&rt); // FONCTIONNE PAS ....
	init_mlx(&rt);
}

int main(void)
{
	RTv1();
	return (0);
}
