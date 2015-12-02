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
		rt->cam_x += 0.5; 
	else if (keycode == 123) // left
		rt->cam_x -= 0.5;
	else if (keycode == 65362 || keycode == 126) // up
		rt->cam_y += 0.5;
	else if (keycode == 65364 || keycode == 125) // down
		rt->cam_y -= 0.5;
	else if (keycode == 65307)
	{
		ft_putendl("Exit RTv1");
		exit(0);
	}
	return (0);
}

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

void trace_sphere(t_rt *rt) // pour calcuer la sphere dans la scene
{
	int scan_x;
	int scan_y;
	int i;

	double vx;
	double vy;
	double vz;
	double a;
	double b;
	double c;
	double det; // determinant du calcul effectué, pour trouver surface de la sphere.
	double t; //  calcul pour trouver la position du point sur la sphere par rapport au ray lancé.
	double dist;

	double sx;
	double sy;
	double sz;
	t_pos s_vect;
	double sum_vect;
	int color;

	scan_x = 0;
	scan_y = 0;
	i = 0;
	dist = 0.0;
	color = 0x000000; // base color = black;
	while (scan_y < rt->screen_height) // pour chaque colonne.
	{
		while (scan_x < rt->screen_width) // pour chaque ligne de pixel.
		{
			// calculs preliminaires pour la sphere
			// le vec actuel
			vx = rt->vp_vectors[i].x;
			vy = rt->vp_vectors[i].y;
			vz = rt->vp_vectors[i].z;

			a = (vx * vx) + (vy * vy) + (vz * vz);

			b = 2 * vx * (rt->cam_x - rt->sphere.centre.x) + 2 * vy * (rt->cam_y - rt->sphere.centre.y) + 2 * vz *(rt->cam_z - rt->sphere.centre.z);

			c = rt->sphere.centre.x * rt->sphere.centre.x + rt->sphere.centre.y * rt->sphere.centre.y + rt->sphere.centre.z * rt->sphere.centre.z + 
				rt->cam_x * rt->cam_x + rt->cam_y * rt->cam_y + rt->cam_z * rt->cam_z
				+ -2*(rt->sphere.centre.x * rt->cam_x + rt->sphere.centre.y * rt->cam_y + rt->sphere.centre.z * rt->cam_z) 
				- rt->sphere.diametre * rt->sphere.radius;

			// regarder si touche une sphere en calculant le determinant;
			det = b * b - 4 * a * c;
			// printf("det abc = %f\n", det);
			
			// calculer la position touchée;
			t = (-b - sqrt((b * b) - 4 * a * c)) / 2 * a;
			sx = rt->cam_x + t * vx;
			sy = rt->cam_y + t * vy;
			sz = rt->cam_z + t * vz;
			//printf("sx = %f, sy = %f, sz = %f \n", sx, sy , sz); 
			s_vect.x = (sx - rt->sphere.centre.x) / rt->sphere.radius;
			s_vect.y = (sy - rt->sphere.centre.y) / rt->sphere.radius;
			s_vect.z = (sz - rt->sphere.centre.z) / rt->sphere.radius;
			sum_vect = fabs(s_vect.x) + fabs(s_vect.y) + fabs(s_vect.z); // somme des vect, indique une distance comparée.
			// printf("sum sphere vect = %f\n",  sum_vect);

			color = set_color(sum_vect);
			if (det >= 0.0)
				pixel_put_to_image(rt, scan_x, scan_y, color);
			else
				pixel_put_to_image(rt, scan_x, scan_y, 0x000000); // ne touche pas la sphere => black.
			//printf("a = %f, b = %f, c = %f \n", a, b , c);
			scan_x++;
			i++;
		}
		scan_y++;
		scan_x = 0;
	}
}

void trace_plane(t_rt *rt) {
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
			else
			{
				

			}
			scan_x++;
			i++;
		}
		scan_y++;
		scan_x = 0;
	}
}

int ft_trace_rt(t_rt *rt)
{
	trace_sphere(rt);
	trace_plane(rt);
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
	rt->vp_center_pos.x = rt->cam_x;
	rt->vp_center_pos.y = rt->cam_y + rt->dist_cam_screen;
	rt->vp_center_pos.z = rt->cam_z;

	rt->vp_up_pos.x = rt->cam_x;
	rt->vp_up_pos.y = rt->cam_y + rt->dist_cam_screen;
	rt->vp_up_pos.z = rt->cam_z + 1.0;

	rt->vp_right_pos.x = rt->cam_x + 1.0;
	rt->vp_right_pos.y = rt->cam_y + rt->dist_cam_screen;
	rt->vp_right_pos.z = rt->cam_z;

	rt->vp_upleft_pos.x = rt->cam_x - 1.0;
	rt->vp_upleft_pos.y = rt->cam_y + rt->dist_cam_screen;
	rt->vp_upleft_pos.z = rt->cam_z + 1.0;

	// CHECK LOGS //
	// printf("rt->vp_center_pos : %f x, %f y, %f z;\n", rt->vp_center_pos.x, rt->vp_center_pos.y, rt->vp_center_pos.z);
	// printf("rt->vp_up_pos : %f x, %f y, %f z;\n", rt->vp_up_pos.x, rt->vp_up_pos.y, rt->vp_up_pos.z);
	// printf("rt->vp_right_pos : %f x, %f y, %f z;\n", rt->vp_right_pos.x, rt->vp_right_pos.y, rt->vp_right_pos.z);
	// printf("rt->vp_upleft_pos : %f x, %f y, %f z;\n", rt->vp_upleft_pos.x, rt->vp_upleft_pos.y, rt->vp_upleft_pos.z);

	rt->vp_vectors[0].x = rt->vp_upleft_pos.x - rt->cam_x;
	rt->vp_vectors[0].y = rt->vp_upleft_pos.y - rt->cam_y;
	rt->vp_vectors[0].z = rt->vp_upleft_pos.z - rt->cam_z;
	// printf("rt->vp_vectors[0] : %f x, %f y, %f z;\n", rt->vp_vectors[0].x, rt->vp_vectors[0].y, rt->vp_vectors[0].z);

	// calcul des vectors pour chaque pixel de l'ecran.
	y = 0;
	x = 1;
	i = 1;
	inc_x = 2.0 / rt->screen_width;
	inc_z = 2.0 / rt->screen_height;
	xref = rt->vp_upleft_pos.x;
	yref = rt->vp_vectors[0].y; // juste a copier dans chaque case, l'ecran est plat.
	zref = rt->vp_upleft_pos.z;
	while (y < rt->screen_height)
	{
		while (x < rt->screen_width)
		{
			xref += inc_x;
			rt->vp_vectors[i].x = xref - rt->cam_x;
			rt->vp_vectors[i].y = yref;
			rt->vp_vectors[i].z = zref - rt->cam_z;
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
			rt->vp_vectors[i].x = ((rt->vp_vectors[i].x * cos(rt->cam_angle_x)) + (rt->vp_vectors[i].y - sin(rt->cam_angle_y)) + 0);
			rt->vp_vectors[i].y = ((rt->vp_vectors[i].x * sin(rt->cam_angle_x)) + (rt->vp_vectors[i].y * cos(rt->cam_angle_y)) + 0);
			rt->vp_vectors[i].z = (0 + 0 + rt->vp_vectors[i].z * 1);

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
	rt->vp_vectors[400 + 200 * 400].x, rt->vp_vectors[400 + 200 * 400].y, rt->vp_vectors[400 + 200 * 400].z);
}

void init_var(t_rt *rt) // Definir scene.
{

	// defining screen var //
	rt->screen_height = SCREEN_H;
	rt->screen_width = SCREEN_W;

	rt->vp_vectors = malloc(sizeof(t_pos) * (rt->screen_height * rt->screen_width)); // allocation viewplane vectors.

	// defining cam var //
	rt->cam_x = 1.0;
	rt->cam_y = 1.0;
	rt->cam_z = 3.0;
	rt->cam_angle_x = 0.0;
	rt->cam_angle_y = 0.0;
	rt->cam_angle_z = 0.0;

	rt->dist_cam_screen = 1.0;

	// positionning sphere //
	rt->sphere.centre.x = 1.5;
	rt->sphere.centre.y = 4.0;
	rt->sphere.centre.z = 1.0;
	rt->sphere.diametre = 2.0;
	rt->sphere.radius = 2.0;

	// positionning plane //
	rt->plane.point.x = 0.0;
	rt->plane.point.y = 3.0;
	rt->plane.point.z = 0.0;
	rt->plane.normale.x = 0.0;
	rt->plane.normale.y = 0.0;
	rt->plane.normale.z = 1.0;
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
