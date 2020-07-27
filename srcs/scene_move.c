/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_move.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/22 13:20:11 by darbib            #+#    #+#             */
/*   Updated: 2020/07/24 10:30:53 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"
#include "print.h"

void	move_planes(t_plane *planes, int n, t_vect *translation)
{
	t_plane *plane;

	while (n--)
	{
		plane = planes + n;
		add_vect(&plane->current_pos, translation, &plane->current_pos);
	}
}

void	move_triangles(t_trig *triangles, int n, t_vect *translation)
{
	t_trig *triangle;

	while (n--)
	{
		triangle = triangles + n;
		add_vect(&triangle->current_pt1, translation, &triangle->current_pt1);
		add_vect(&triangle->current_pt2, translation, &triangle->current_pt2);
		add_vect(&triangle->current_pt3, translation, &triangle->current_pt3);
	}
}

void	move_spheres(t_sphere *spheres, int n, t_vect *translation)
{
	t_sphere *sphere;

	while (n--)
	{
		sphere = spheres + n;
		add_vect(&sphere->current_pos, translation, &sphere->current_pos);
	}
}

void	move_squares(t_square *squares, int n, t_vect *translation)
{
	t_square *square;

	while (n--)
	{
		square = squares + n;
		add_vect(&square->current_pos, translation, &square->current_pos);
		add_vect(&square->current_pt1, translation, &square->current_pt1);
		add_vect(&square->current_pt2, translation, &square->current_pt2);
		add_vect(&square->current_pt3, translation, &square->current_pt3);
	}
}

void	move_cylinders(t_cylinder *cylinders, int n, t_vect *translation)
{
	t_cylinder *cylinder;

	while (n--)
	{
		cylinder = cylinders + n;
		add_vect(&cylinder->current_pos, translation, &cylinder->current_pos);
	}
}
