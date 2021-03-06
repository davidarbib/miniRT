/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_objs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/21 14:25:07 by darbib            #+#    #+#             */
/*   Updated: 2020/06/29 16:35:12 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"
#include "vector.h"

int	set_cams(t_cam *cams, int n)
{
	t_cam	*cam;

	while (n)
	{
		cam = cams + n - 1;
		normalize(&cam->orient, &cam->orient);
		vect_cpy(&cam->pos, &cam->current_pos);
		vect_cpy(&cam->orient, &cam->current_orient);
		n--;
	}
	return (1);
}

int	set_planes(t_plane *planes, int n)
{
	t_plane	*plane;

	while (n)
	{
		plane = planes + n - 1;
		normalize(&plane->orient, &plane->orient);
		vect_cpy(&plane->pos, &plane->current_pos);
		vect_cpy(&plane->orient, &plane->current_orient);
		n--;
	}
	return (1);
}

int	set_triangles(t_trig *triangles, int n)
{
	t_trig	*triangle;

	while (n)
	{
		triangle = triangles + n - 1;
		vect_cpy(&triangle->pt1, &triangle->current_pt1);
		vect_cpy(&triangle->pt2, &triangle->current_pt2);
		vect_cpy(&triangle->pt3, &triangle->current_pt3);
		n--;
	}
	return (1);
}

int	set_spheres(t_sphere *spheres, int n)
{
	t_sphere	*sphere;

	while (n)
	{
		sphere = spheres + n - 1;
		vect_cpy(&sphere->pos, &sphere->current_pos);
		n--;
	}
	return (1);
}
