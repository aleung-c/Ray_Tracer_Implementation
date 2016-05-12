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
# include "obj_header.h"

# define SCREEN_W 720
# define SCREEN_H 720
# define TOTAL_PX SCREEN_W * SCREEN_H
# define VEC_OBJ_LIMIT 10

// struct d'un objet.
typedef struct				s_scene_object {
	char					*name;
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
	int 					display_color;
	struct s_touch			*next;
}							t_touch;

// struct dun pixel de lecran
typedef struct				s_screen_vec 
{
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
	t_light					*scene_lights;

	// datas to save
	t_vector3				vp_center_pos;
	t_vector3				vp_up_pos;
	t_vector3				vp_upleft_pos;
	t_vector3				vp_right_pos;

	t_vector3				vp_pos; // pas utilise.

	t_screen_vec			*vp_vectors; // total px.

	// OBJECTS
	t_scene_object			*scene_objs; // liste chainee d'obj.

	// Reusable Vars
	t_scene_object			*tmp; // to access objects;
	int						scan_x;
	int						scan_y;
	int						i;
	int						color;
}							t_rt;

typedef struct s_rgb 
{
	int						r;
	int						g;
	int						b;
}				t_rgb;

// protos

void						add_light_to_scene(t_rt *rt, t_vector3 pos, double intensity, double light_power_distance);

void						add_sphere_to_scene(t_rt *rt, t_vector3 centre, double diametre, double radius, int color);
void						sphere_check(t_screen_vec *vp_vec, t_scene_object *obj, t_vector3 origine, t_vector3 vec_dir);
int							sphere_check_touch(t_scene_object *obj,
								t_vector3 origine, t_vector3 vec_dir);

void						algo_touching_sphere(t_sphere_algo *algo, t_scene_object *obj,
								t_vector3 origine, t_vector3 vec_dir);
void						algo_sphere_touched(t_sphere_algo *algo, t_vector3 origine, t_vector3 vec_dir);

void						add_plane_to_scene(t_rt *rt, t_vector3 point, t_vector3 normale, int color);
void						plane_check(t_screen_vec *vp_vec, t_scene_object *obj, t_vector3 origine,
								t_vector3 vec_dir);
int							plane_check_touch(t_scene_object *obj, t_vector3 origine,
								t_vector3 vec_dir);

void						add_touch_to_vp_vec(t_screen_vec *vp_vec, t_scene_object *obj, t_vector3 origine, t_vector3 touch_point);
t_scene_object				*get_closest_object(t_screen_vec *vp_vec);

void						calculate_casted_shadows(t_rt *rt);
void						run_trough_lights_shadows(t_rt *rt, t_screen_vec *vp_vector);
int							check_is_in_shadow(t_rt *rt, t_screen_vec *vp_vector, t_light *cur_light);

void						calculate_inner_shadows(t_rt *rt);
void						run_trough_lights_inner_shadows(t_rt *rt, t_screen_vec *vp_vector);

// utils
// utils_vec.c
t_vector3					set_vec3(double x, double y, double z);
double						distance(t_vector3 origine, t_vector3 destination);
double						vector_length(t_vector3 vec_dir);
t_vector3					point_from_vecdir(t_vector3 origine, t_vector3 vec_dir);
// double					distance_cmp(t_vector3 origine, t_vector3 destination);
t_vector3					normalize_vector(t_vector3);
double						norme(t_vector3 v);
t_vector3					vec_dir(t_vector3 origine, t_vector3 destination);

// utils_angles.c
double						angle_check(double angle);
int							angle_rev(int angle);

// utils_obj.c
void						SetObjectName(t_scene_object *Obj, char *Str);
char						*GetObjectName(t_scene_object *Obj);
char						*GetObjectType(t_scene_object *Obj);

#endif
