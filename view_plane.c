/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view_plane.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/16 14:43:01 by aleung-c          #+#    #+#             */
/*   Updated: 2016/05/16 14:43:05 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"
#include <stdio.h> //

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


	rt->vp_upleft_pos.x = rt->camera.camera_obj->pos.x - (rt->screen_width_ratio / 2.0);
	rt->vp_upleft_pos.y = rt->camera.camera_obj->pos.y + rt->camera.camera_obj->dist_cam_screen;
	rt->vp_upleft_pos.z = rt->camera.camera_obj->pos.z + (rt->screen_height_ratio / 2.0);


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
	inc_x = rt->screen_width_ratio / (float)rt->screen_width;
	inc_z = rt->screen_height_ratio / (float)rt->screen_height;
	xref = rt->vp_upleft_pos.x;
	yref = rt->vp_upleft_pos.y;
	zref = rt->vp_upleft_pos.z;
	while (y < rt->screen_height)
	{
		while (x < rt->screen_width)
		{
			xref += inc_x;

			rt->vp_vectors[i].v.x = xref - rt->camera.camera_obj->pos.x;

			rt->vp_vectors[i].v.y = yref - rt->camera.camera_obj->pos.y;
			//rt->vp_vectors[i].v.y = sqrt(pow(rt->vp_center_pos.y - rt->camera.camera_obj->pos.y, 2) + pow((rt->vp_center_pos.x + xref) - rt->vp_center_pos.x, 2));
			//rt->vp_vectors[i].v.y = (rt->vp_center_pos.y - rt->camera.camera_obj->pos.y) + (rt->vp_center_pos.x - xref);

			rt->vp_vectors[i].v.z = zref - rt->camera.camera_obj->pos.z;

			/*rt->vp_vectors[i].v.z = sqrt(pow(rt->vp_center_pos.z - rt->camera.camera_obj->pos.z, 2) + pow((rt->vp_center_pos.z + zref) - rt->vp_center_pos.z, 2));*/

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
		printf("YLength = %f \n", rt->vp_vectors[i].v.y);
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
