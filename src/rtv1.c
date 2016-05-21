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

#include "../includes/rtv1.h"

void	rtv1(int scene_number)
{
	t_rt rt;

	rt.scene_objs = NULL;
	rt.scene_lights = NULL;
	rt.scene_number = scene_number;
	init_entry(&rt);
	calculate_viewplane(&rt);
	init_mlx(&rt);
}

int		main(int argc, char **argv)
{
	if (argc == 2 && (ft_strlen(argv[1]) == 1)
		&& (argv[1][0] >= '1' && argv[1][0] <= '7'))
		rtv1(ft_atoi(argv[1]));
	else
	{
		ft_putendl("Usage: ./RTv1 [1-7]");
		return (-1);
	}
	return (0);
}
