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

// struct dun point dans l'espace a trois coordonnees.
typedef struct				s_vector3 
{
	double					x; // strafe left right
	double					y; // go forward.
	double					z; // altitude.

}							t_vector3;


// CAMERA
typedef struct				s_camera {
	t_obj_type				type;

	t_vector3				pos;
	t_vector3				euler_angles; // pour rotation de la camera sur elle-meme.
	double					dist_cam_screen;
}							t_camera;

// LIGHT LIST
typedef struct				s_light {
	t_vector3				pos;
	double					intensity;
	struct s_light			*next;
}							t_light;

// SPHERE
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
	t_vector3				tpoint;
}							t_sphere_algo;

// PLANE
typedef struct				s_plane
{
	t_vector3				normale;
	t_vector3				point;
}							t_plane;

typedef	struct				s_plane_algo {
	double					t;
	t_vector3				tpoint;
}							t_plane_algo;

// CYLINDER
typedef struct				s_cylinder {


}							t_cylinder;

// CONE
typedef struct				s_cone {
	
}							t_cone;

#endif
