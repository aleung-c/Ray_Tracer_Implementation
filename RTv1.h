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

// struct dun point dans l'espace a trois coordonnees.
typedef struct				s_vector3 
{
	double					x; // strafe left right
	double					y; // go forward.
	double					z; // altitude.

}							t_vector3;


typedef struct				s_camera {
	t_obj_type				type;

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
	t_vector3				pos; // x y z
	double					diametre;
	double					radius;
}							t_sphere;

// struct avc vals de calculs pour passer la norme.
typedef	struct				s_sphere_algo {
	double					a;
	double					b;
	double					c;

	double					det; // determinant du calcul effectué, pour trouver surface de la sphere.
	double					t; //  calcul pour trouver la position du point sur la sphere par rapport au ray lancé.
	double					dist;

	// point from origin to t.
	t_vector3				svec;

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

// struct d'un objet.
typedef struct				s_scene_object {
	t_obj_type				type;
	int						color;

	t_camera				*camera_obj; // il n y aura qu'un sc_obj camera.
	t_sphere				*sphere_obj;
	t_plane					*plane_obj;
	t_cylinder				*cylinder_obj;
	t_cone					*cone_obj;
	struct s_scene_object	*next;
}							t_scene_object;

// liste chainee dobjets touches.
typedef struct				s_touch
{
	t_scene_object			*touched_obj;
	t_vector3				point;
	double					distance;
	int						color;
	struct s_touch			*next;
}							t_touch;

// struct dun pixel de lecran
typedef struct				s_screen_vec {
	t_vector3				v;
	t_touch					*touched_objs_list;
}							t_screen_vec;



// La struct conteneur.
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
	t_scene_object			camera;
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
void						add_sphere_to_scene(t_rt *rt, t_vector3 centre, double diametre, double radius, int color);
void						sphere_check(t_screen_vec *vp_vec, t_scene_object *obj, t_vector3 origine, t_vector3 vec_dir);

void						add_touch_to_vp_vec(t_screen_vec *vp_vec, t_scene_object *obj, t_vector3 origine, t_vector3 touch_point);
t_scene_object				*get_closest_object(t_screen_vec *vp_vec);

// utils
// utils_vec.c
t_vector3					set_vec3(double x, double y, double z);
double						distance(t_vector3 origine, t_vector3 destination);
//double						distance_cmp(t_vector3 origine, t_vector3 destination);
t_vector3					normalize_vector(t_vector3);
double						norme(t_vector3 v);

// utils_angles.c
double						angle_check(double angle);
int							angle_rev(int angle);

#endif
