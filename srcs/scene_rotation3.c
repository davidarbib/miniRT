/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_rotation3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/24 16:50:22 by darbib            #+#    #+#             */
/*   Updated: 2020/06/29 16:54:05 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rotation.h"
#include "actions.h"

void	rotate_spheres(t_sphere *spheres, int n, double *matrix)
{
	t_sphere	*sphere;

	while (n)
	{
		sphere = spheres + n - 1;
		rotate_point(matrix, &sphere->current_pos, &sphere->current_pos);
		n--;
	}
}

void	rotate_squares(t_square *squares, int n, double *matrix)
{
	t_square	*square;

	while (n)
	{
		square = squares + n - 1;
		rotate_point(matrix, &square->current_pos, &square->current_pos);
		n--;
	}
}

void	rotate_cylinders(t_cyld *cylinders, int n, double *matrix)
{
	t_cyld	*cylinder;

	while (n)
	{
		cylinder = cylinders + n - 1;
		rotate_point(matrix, &cylinder->current_pos, &cylinder->current_pos);
		n--;
	}
}
