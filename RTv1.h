/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RTv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <aleung-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/21 13:04:52 by aleung-c          #+#    #+#             */
/*   Updated: 2015/10/05 16:14:05 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
#define RTV1_H

# include "./libft/libft.h"
# include <stdio.h> //
# include <math.h>
# include <mlx.h>
# include "X.h"
# define SCREEN_W 720
# define SCREEN_H 720
# define TOTAL_PX SCREEN_W * SCREEN_H
# define VEC_OBJ_LIMIT 10

typedef enum				e_obj_type
{
	CAM,
	LIGHT,
	PLANE,
	SPHERE,
	CYLINDER,
	CONE,
	INTERSECTION,
	NBOBJTYPE
}							t_obj_type;

typedef struct				s_vector3 // struct dun point dans l'espace a trois coordonnees.
{
	double					x;
	double					y;
	double					z;

}							t_vector3;

typedef struct				s_camera {
	t_vector3				pos;
	t_vector3				euler_angles; // pour rotation de la camera sur elle-meme.
	double					dist_cam_screen;
}							t_camera;

typedef struct				s_light {
	t_vector3				pos;
	double					intensity;

}							t_light;

typedef struct				s_sphere
{
	t_vector3				centre; // x y z
	double					diametre;
	double					radius;
}							t_sphere;

typedef	struct				s_sphere_algo {
	double					a;
	double					b;
	double					c;
	double					det; // determinant du calcul effectué, pour trouver surface de la sphere.
	double					t; //  calcul pour trouver la position du point sur la sphere par rapport au ray lancé.
	double					dist;

	// dist from origin to t.
	double					sx;
	double					sy;
	double					sz;

}							t_sphere_algo;

typedef struct				s_plane
{
	t_vector3				normale;
	t_vector3				point;

}							t_plane;

typedef struct				s_cylinder {


}							t_cylinder;

typedef struct				s_cone {
	
}							t_cone;

typedef struct				s_scene_object {
	t_obj_type				type;

	t_sphere				*sphere;
	t_plane					*plane;
	t_cylinder				*cylinder;
	t_cone					*cone;
	struct s_scene_object	*next;
}							t_scene_object;

typedef struct				s_screen_vec {
	t_vector3				v;
	t_vector3				touchs[VEC_OBJ_LIMIT];
	double					touchs_dists[VEC_OBJ_LIMIT];
}							t_screen_vec;

typedef struct				s_rt 
{
	// MLX //
	void					*mlx;
	void					*win;
	void					*imgv;
	char					*img;
	int						bpp;
	int						sizeline;
	int						endian;

	// Ecran //
	int						screen_width;
	int						screen_height;

	// main objs
	t_camera				camera;
	t_light					light;

	// datas to save
	t_vector3				vp_center_pos;
	t_vector3				vp_up_pos;
	t_vector3				vp_upleft_pos;
	t_vector3				vp_right_pos;

	t_vector3				vp_pos; // pas utilise.

	t_screen_vec			*vp_vectors; // total px.

	// OBJECTS
	t_scene_object			*scene_objs; // liste chainee d'obj.
}	t_rt;

// protos

void add_sphere_to_scene(t_rt *rt, t_vector3 centre, double diametre, double radius);
void sphere_check(t_rt *rt, t_vector3 origine, t_vector3 vec_dir);

// utils
t_vector3					set_pos(double x, double y, double z);
double						angle_check(double angle);
int							angle_rev(int angle);

#endif
