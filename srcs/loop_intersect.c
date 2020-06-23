/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_intersect.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/20 16:12:37 by darbib            #+#    #+#             */
/*   Updated: 2020/06/23 20:48:24 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytrace.h"

void	loop_intersect_planes(t_plane *planes, int n, t_ray *ray, t_near *near)
{
	double		t;
	t_plane		*plane;
	
	while (--n >= 0)
	{
		plane = planes + n;
		if ((t = intersect_plane(*plane, *ray)) < near->t)
		{
			near->t = t;
			near->obj = (void *)plane;
			near->type = ray->current_type;
			get_obj_rgb(near->obj, near->type, near->rgb); 
		}
	}
}

void	loop_intersect_triangles(t_trig *triangles, int n, t_ray *ray,
		t_near *near)
{
	double	t;
	t_trig	*triangle;
	
	while (--n >= 0)
	{
		triangle = triangles + n;
		if ((t = intersect_triangle(*triangle, *ray)) > 0 &&
				(t + EPSILON) < near->t)
		{
			near->t = t;
			near->obj = (void *)triangle;
			near->type = ray->current_type;
			get_obj_rgb(near->obj, near->type, near->rgb); 
		}
	}
}
