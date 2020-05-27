/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rayplane.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/23 14:47:38 by darbib            #+#    #+#             */
/*   Updated: 2020/05/27 17:52:44 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytrace.h"

int		intersect_plane(t_vect plane_pos, t_vect plane_orient,
		t_vect ray_origin, t_vect ray_direction)
{
	double	denom;
	double	t;
	t_vect	tmp_v; 

	normalize(&plane_pos, &plane_pos);
	normalize(&ray_origin, &ray_origin);
	normalize(&ray_direction, &ray_direction);
	denom = dot(&ray_direction, &plane_orient);	
	if (ft_double_abs(denom) > EPSILON)
	{
		sub_vect(&plane_pos, &ray_origin, &tmp_v);
		t = dot(&tmp_v, &plane_orient) / denom;
		return (t >= EPSILON);
	}
	return (0);
}

/*
int		intersect_square()
{
}
*/
