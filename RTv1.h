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
# define RAD(x) ((x / 180.0) * M_PI)

// struct d'un objet.
typedef struct				s_scene_object {
	char					*name;
	int						id;
	t_obj_type				type;
	int						color;

	t_camera				*camera_obj;
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
	t_vector3				obj_inter_normale;
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
	double					screen_width_ratio;
	double					screen_height_ratio;

	// scene datas
	int 					scene_number;

	// scene settings
	int 					has_casted_shadows;
	int 					has_casted_shadows_on_self;
	int 					has_inner_shadows;
	int 					has_shining;

	// main objs
	t_scene_object			camera;
	t_light					*scene_lights;

	// datas to save
	t_vector3				vp_center_pos;
	t_vector3				vp_up_pos;
	t_vector3				vp_upleft_pos;
	t_vector3				vp_right_pos;

	t_vector3				vp_pos;

	t_screen_vec			*vp_vectors;

	// OBJECTS
	t_scene_object			*scene_objs;

	// Reusable Vars
	t_scene_object			*tmp;
	int						scan_x;
	int						scan_y;
	int						i;
	int						color;
	t_scene_object			*last_added_obj;
}							t_rt;

// une color
typedef struct				s_rgb 
{
	int						r;
	int						g;
	int						b;
}							t_rgb;

// pour stock variables
typedef struct				s_inner_shadow_calcs
{
	int						obj_color;
	t_rgb					rgb_color;
	int						color_to_set;
	double					diffval_vecs;
	double					vec_angle;
	int						color_incval_precise;
	int						color_incval;
	t_vector3				inter_to_light;
	t_vector3				inter_to_obj_normale;
	double					distance_to_light;
	double					normalized_distance_to_light;
}							t_inner_shadow_calcs;

typedef struct				s_casted_shadow_calcs
{
	double					dist_to_light;
	double					dist_to_obj;
	t_vector3				inter_to_light;
	t_vector3				inter_to_obj_normale;
	double					vec_angle;
}							t_casted_shadow_calcs;

typedef struct				s_shining_calcs
{
	int						obj_color;
	t_rgb					rgb_color;
	int						color_to_set;
	double					vec_angle;
	int						color_incval_precise;
	int						color_incval;
	t_vector3				inter_to_light;
	t_vector3				inter_to_obj_normale;
}							t_shining_calcs;

// protos
void						RTv1(int scene_number);

// entry
void						init_entry(t_rt *rt);
void						init_screen_values(t_rt *rt);
void						init_camera(t_rt *rt);

// scene definitions
void						init_scene1(t_rt *rt);
void						init_scene2(t_rt *rt);
void						init_scene3(t_rt *rt);
void						init_scene4(t_rt *rt);
void						init_scene5(t_rt *rt);
void						init_scene6(t_rt *rt);
void						init_scene7(t_rt *rt);

void						calculate_viewplane(t_rt *rt);

t_scene_object				*clean_obj(t_scene_object	*new_obj);
void						set_cone_rotation(t_scene_object *new_obj, t_vector3 normale);
void						set_cylinder_rotation(t_scene_object *new_obj, t_vector3 normale);

void						add_light_to_scene(t_rt *rt, t_vector3 pos, double intensity, double light_power_distance);


void						add_sphere_to_scene(t_rt *rt, t_vector3 centre, double radius, int color);
void						sphere_check(t_screen_vec *vp_vec, t_scene_object *obj, t_vector3 origine, t_vector3 vec_dir);
int							sphere_check_touch(t_scene_object *obj, t_light *cur_light, t_screen_vec *vp_vector);
void						algo_touching_sphere(t_sphere_algo *algo, t_scene_object *obj,
													t_vector3 origine, t_vector3 vec_dir);
void						algo_sphere_touched(t_sphere_algo *algo, t_vector3 origine, t_vector3 vec_dir);


void						add_plane_to_scene(t_rt *rt, t_vector3 point, t_vector3 normale, int color);
void						plane_check(t_screen_vec *vp_vec, t_scene_object *obj, t_vector3 origine,
								t_vector3 vec_dir);
void						algo_touching_plane (t_plane_algo *algo, t_scene_object *obj,
													t_vector3 origine, t_vector3 vec_dir);
void						algo_plane_touched(t_plane_algo *algo, t_vector3 origine,
												t_vector3 vec_dir);
int							plane_check_touch(t_scene_object *obj, t_light *cur_light,
												t_screen_vec *vp_vector);


void						add_cylinder_to_scene(t_rt *rt, t_vector3 point, t_vector3 normale, double radius, int color);
void						cylinder_check(t_screen_vec *vp_vec, t_scene_object *obj, t_vector3 origine,
											t_vector3 vec_dir);
void						algo_touching_cylinder(t_cylinder_algo *algo, t_scene_object *obj,
													t_vector3 origine, t_vector3 vec_dir);
void						algo_cylinder_touched(t_cylinder_algo *algo, t_vector3 origine,
													t_vector3 vec_dir);
int							cylinder_check_touch(t_scene_object *obj, t_light *cur_light,
													t_screen_vec *vp_vector);


void						add_cone_to_scene(t_rt *rt, t_vector3 point, t_vector3 normale, double angle, int color);
void						cone_check(t_screen_vec *vp_vec, t_scene_object *obj,
										t_vector3 origine, t_vector3 vec_dir);
void						algo_touching_cone(t_cone_algo *algo, t_scene_object *obj,
												t_vector3 origine, t_vector3 vec_dir);
void						algo_cone_touched(t_cone_algo *algo, t_vector3 origine,
												t_vector3 vec_dir);
int							cone_check_touch(t_scene_object *obj, t_light *cur_light, 
												t_screen_vec *vp_vector);


void						add_obj_to_scene_list(t_rt *rt, t_scene_object *obj_to_add);
void						add_touch_to_vp_vec(t_screen_vec *vp_vec, t_scene_object *obj,
													t_vector3 origine, t_vector3 touch_point);
t_scene_object				*get_closest_object(t_screen_vec *vp_vec);
t_vector3					get_normale(t_scene_object *obj, t_vector3 inter_point);
t_vector3					get_cylinder_norm(t_scene_object *obj, t_vector3 inter_point);
t_vector3					get_cone_norm(t_scene_object *obj, t_vector3 inter_point);
t_vector3					get_sphere_norm(t_scene_object *obj, t_vector3 inter_point);

// SHADOWS entry.
void						calculate_casted_shadows(t_rt *rt);
void						run_trough_lights_shadows(t_rt *rt, t_screen_vec *vp_vector);
void						check_is_in_shadow(t_rt *rt, t_screen_vec *vp_vector, t_light *cur_light);
int							check_is_in_shadow_type_filtering (t_scene_object *tmp, 
								t_screen_vec *vp_vector, t_light *cur_light);
int							darken_color(int hex_target_color, int divisor);

void						calculate_inner_shadows(t_rt *rt);
void						run_trough_lights_inner_shadows(t_rt *rt, t_screen_vec *vp_vector);
int							set_inner_color_from_dist(t_light *cur_light, t_screen_vec *vp_vector);
int							set_inner_color_from_normale(t_light *cur_light, t_screen_vec *vp_vector);

// shining
void						calcultate_shining(t_rt *rt);
void						run_trough_lights_shining(t_rt *rt, t_screen_vec *vp_vector);
int							set_shining_color(t_light *cur_light,
												t_screen_vec *vp_vector);


// utils
// utils_vec.c
t_vector3					set_vec3(double x, double y, double z);
double						distance(t_vector3 origine, t_vector3 destination);
t_vector3					translate(t_vector3 p, t_vector3 v);
double						vector_length(t_vector3 vec_dir);
t_vector3					point_from_vecdir(t_vector3 origine, t_vector3 vec_dir);
t_vector3					normalize_vector(t_vector3);
double						norme(t_vector3 v);

t_vector3					vec_dir(t_vector3 origine, t_vector3 destination);
t_vector3					vec_dir_distance_normalized(t_vector3 origine, t_vector3 destination);
void						create_vertical_norm(t_vector3 *norm);
t_vector3					vec_hand_swap(t_vector3 v);

// utils_rotation.c
t_vector3					vector(t_vector3 a, t_vector3 b);
t_vector3					do_rotate(double rot[3][3], t_vector3 p);
void						get_rotate(t_vector3 axe, double cos, double rot[3][3]);
void						get_rotate_angle(t_vector3 axe, double angle, double rot[3][3]);

// utils_angles.c
double						angle_check(double angle);
int							angle_rev(int angle);
double						scalar(t_vector3 a, t_vector3 b);

// utils_obj.c
void						SetObjectName(t_scene_object *Obj, char *Str);
void						SetObjectId(t_scene_object *Obj, int Id);
char						*GetObjectName(t_scene_object *Obj);
char						*GetObjectType(t_scene_object *Obj);
int							GetObjectId(t_scene_object *Obj);

// utils_color.c
t_rgb						hex_to_rgb(int hex_color);
int							rgb_to_hex(t_rgb rgb_color);
void						check_limit_darkening(t_rgb *rgb_color);
void						check_limit_brightening(t_rgb *rgb_color);


#endif
