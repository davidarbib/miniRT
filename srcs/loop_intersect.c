/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_intersect.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/20 16:12:37 by darbib            #+#    #+#             */
/*   Updated: 2020/08/04 18:44:02 by darbib           ###   ########.fr       */
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
		if ((t = intersect_plane(*plane, *ray)) > 0 &&
				(t + EPSILON) < near->t)
		{
			near->t = t;
			near->obj = (void *)plane;
			near->type = ray->current_type;
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
		}
	}
}

void	loop_intersect_spheres(t_sphere *spheres, int n, t_ray *ray,
		t_near *near)
{
	double		t;
	t_sphere	*sphere;

	while (--n >= 0)
	{
		sphere = spheres + n;
		if ((t = intersect_sphere(*sphere, *ray)) > 0 &&
				(t + EPSILON) < near->t)
		{
			near->t = t;
			near->obj = (void *)sphere;
			near->type = ray->current_type;
		}
	}
}

void	loop_intersect_squares(t_square *squares, int n, t_ray *ray,
		t_near *near)
{
	double		t;
	t_square	*square;

	while (--n >= 0)
	{
		square = squares + n;
		if ((t = intersect_square(*square, *ray)) > 0 &&
				(t + EPSILON) < near->t)
		{
			near->t = t;
			near->obj = (void *)square;
			near->type = ray->current_type;
		}
	}
}

void	loop_intersect_cylinders(t_cylinder *cylinders, int n, t_ray *ray,
		t_near *near)
{
	double		t;
	t_cylinder	*cylinder;

	while (--n >= 0)
	{
		cylinder = cylinders + n;
		if ((t = intersect_cylinder(*cylinder, *ray)) > 0 &&
				(t + EPSILON) < near->t)
		{
			near->t = t;
			near->obj = (void *)cylinder;
			near->type = ray->current_type;
		}
	}
}
