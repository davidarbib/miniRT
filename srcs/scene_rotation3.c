/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_rotation3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/24 16:50:22 by darbib            #+#    #+#             */
/*   Updated: 2020/08/04 19:15:48 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "print.h"
#include "rotation.h"
#include "actions.h"

void	rotate_spheres(t_sphere *spheres, int n, double *matrix)
{
	t_sphere	*sphere;

	while (n--)
	{
		sphere = spheres + n;
		rotate_point(matrix, &sphere->current_pos, &sphere->current_pos);
	}
}

void	rotate_squares(t_square *squares, int n, double *matrix)
{
	t_square	*square;

	while (n--)
	{
		square = squares + n;
		rotate_point(matrix, &square->current_pos, &square->current_pos);
		rotate_point(matrix, &square->current_orient, &square->current_orient);
		rotate_point(matrix, &square->current_pt1, &square->current_pt1);
		rotate_point(matrix, &square->current_pt2, &square->current_pt2);
		rotate_point(matrix, &square->current_pt3, &square->current_pt3);
		compute_current_edges(square);
	}
}

void	rotate_cylinders(t_cylinder *cylinders, int n, double *matrix)
{
	t_cylinder	*cylinder;

	while (n--)
	{
		cylinder = cylinders + n;
		rotate_point(matrix, &cylinder->current_pos, &cylinder->current_pos);
		rotate_point(matrix, &cylinder->current_orient,
				&cylinder->current_orient);
	}
}

void	rotate_olights(t_olight *olights, int n, double *matrix)
{
	while (n--)
		rotate_point(matrix, &olights[n].current_pos, &olights[n].current_pos);
}
