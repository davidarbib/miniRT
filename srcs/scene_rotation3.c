/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_rotation3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/24 16:50:22 by darbib            #+#    #+#             */
/*   Updated: 2020/06/24 16:53:07 by darbib           ###   ########.fr       */
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
