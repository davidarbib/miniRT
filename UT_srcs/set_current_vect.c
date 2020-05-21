/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_current_vect.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/21 14:25:07 by darbib            #+#    #+#             */
/*   Updated: 2020/05/21 17:26:11 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "camera.h"
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
