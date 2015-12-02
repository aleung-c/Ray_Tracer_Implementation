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

typedef struct s_pos // struct dun point dans l'espace a trois coordonnees.
{
	double x;
	double y;
	double z;

}				t_pos;

typedef struct	s_sphere
{
	t_pos		centre; // x y z
	double		diametre;
	double		radius;

}				t_sphere;

typedef struct	s_plane
{
	t_pos		normale;
	t_pos		point;

}				t_plane;

typedef struct	s_rt 
{
	// MLX //
	void			*mlx;
	void			*win;
	void			*imgv;
	char			*img;
	int				bpp;
	int				sizeline;
	int				endian;

	// Ecran //
	int screen_width;
	int screen_height;

	//  Camera //
	double cam_x;
	double cam_y;
	double cam_z;

	double cam_angle_y;
	double cam_angle_x;
	double cam_angle_z; // pour rotation de la camera sur elle-meme.

	// OBJECTS
	// sphere
	t_sphere sphere;

	// plane
	t_plane plane;


	double dist_cam_screen;

	// datas to save
	t_pos vp_center_pos;
	t_pos vp_up_pos;
	t_pos vp_upleft_pos;
	t_pos vp_right_pos;

	t_pos vp_pos; // pas utilise.
	t_pos *vp_vectors; // total px.

}	t_rt;



#endif
