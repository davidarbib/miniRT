/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_current_vect.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/21 14:25:07 by darbib            #+#    #+#             */
/*   Updated: 2020/05/21 23:59:18 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"
#include "vector.h"

int	set_current_vect_cam(t_cam *cams, int n)
{
	t_cam	*cam;

	while (n)
	{
		cam = cams + n - 1;
		if (!(cam->current_pos = vect_dup((cam->pos))))
			return (0);
		if (!(cam->current_orient = vect_dup((cam->orient))))
			return (0);
		n--;
	}
	return (1);
}

int	set_current_vect_plane(t_plane *planes, int n)
{
	t_plane	*plane;

	while (n)
	{
		plane = planes + n - 1;
		if (!(plane->current_pos = vect_dup((plane->pos))))
			return (0);
		if (!(plane->current_orient = vect_dup((plane->orient))))
			return (0);
		n--;
	}
	return (1);
}
