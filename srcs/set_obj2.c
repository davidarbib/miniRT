/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_obj2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/29 16:35:51 by darbib            #+#    #+#             */
/*   Updated: 2020/08/09 14:02:52 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"
#include "vector.h"

void	set_current_edges(t_square *squares, int n)
{
	while (n--)
		compute_current_edges(squares + n);
}

void	set_squares(t_square *squares, int n)
{
	t_square	*square;

	while (n--)
	{
		square = squares + n;
		normalize(&square->orient, &square->orient);
		compute_square_edges(square);
		vect_cpy(&square->pos, &square->current_pos);
		vect_cpy(&square->orient, &square->current_orient);
		compute_square_points(square);
		vect_cpy(&square->pt1, &square->current_pt1);
		vect_cpy(&square->pt2, &square->current_pt2);
		vect_cpy(&square->pt3, &square->current_pt3);
	}
}

void	set_cylinders(t_cylinder *cylinders, int n)
{
	t_cylinder	*cylinder;

	while (n--)
	{
		cylinder = cylinders + n;
		normalize(&cylinder->orient, &cylinder->orient);
		vect_cpy(&cylinder->pos, &cylinder->current_pos);
		vect_cpy(&cylinder->orient, &cylinder->current_orient);
	}
}

void	set_olights(t_olight *olights, int n)
{
	while (n--)
		vect_cpy(&olights[n].pos, &olights[n].current_pos);
}

void	set_quadrics_radius(t_cylinder *cyls, int n, t_sphere *spheres, int k)
{
	while (n--)
		cyls[n].radius = cyls[n].diam / 2.;
	while (k--)
		spheres[k].radius = spheres[k].diam / 2.;
}
