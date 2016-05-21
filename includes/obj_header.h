/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_header.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleung-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/23 13:21:38 by aleung-c          #+#    #+#             */
/*   Updated: 2016/01/23 13:28:12 by aleung-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJ_HEADER_H
# define OBJ_HEADER_H

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

typedef struct				s_vector3
{
	double					x;
	double					y;
	double					z;

}							t_vector3;

typedef struct				s_camera {
	t_obj_type				type;
	t_vector3				pos;
	t_vector3				euler_angles;
	double					dist_cam_screen;
}							t_camera;

typedef struct				s_light {
	t_vector3				pos;
	double					intensity;
	double					light_power_distance;
	struct s_light			*next;
}							t_light;

typedef struct				s_sphere
{
	t_vector3				pos;
	double					diametre;
	double					radius;
}							t_sphere;

typedef	struct				s_sphere_algo {
	double					a;
	double					b;
	double					c;
	double					det;
	double					t;
	double					dist;
	t_vector3				tpoint;
}							t_sphere_algo;

typedef struct				s_plane
{
	t_vector3				normale;
	t_vector3				point;
}							t_plane;

typedef	struct				s_plane_algo {
	double					t;
	t_vector3				tpoint;
}							t_plane_algo;

typedef struct				s_cylinder {
	t_vector3				pos;
	double					radius;
	t_vector3				normale;
	double					rot[3][3];
}							t_cylinder;

typedef	struct				s_cylinder_algo {
	double					a;
	double					b;
	double					c;
	double					det;
	double					t;
	double					cyl_radius;
	double					dist;
	t_vector3				vec_rotated;
	t_vector3				origine_rotated;
	t_vector3				tpoint;
}							t_cylinder_algo;

typedef struct				s_cone {
	t_vector3				pos;
	double					angle;
	t_vector3				normale;
	double					rot[3][3];
}							t_cone;

typedef struct				s_cone_algo {
	double					a;
	double					b;
	double					c;
	double					det;
	double					t;
	double					dist;
	t_vector3				vec_rotated;
	t_vector3				origine_rotated;
	t_vector3				tpoint;
}							t_cone_algo;

#endif
