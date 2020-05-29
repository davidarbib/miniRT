/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_objs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/21 14:25:07 by darbib            #+#    #+#             */
/*   Updated: 2020/05/29 13:43:23 by darbib           ###   ########.fr       */
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
