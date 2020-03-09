/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 15:57:55 by darbib            #+#    #+#             */
/*   Updated: 2020/03/09 13:37:14 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERA_H
# define CAMERA_H

# include "vector.h"
/*
** --- camera ---
** pos : position vector
** ort : orientation vector [-1;1]
** fov : sight-field ([0;180] degrees)
*/
typedef struct		s_cam
{
	t_vect			*pos;
	t_vect			*ort;
	int				fov;
}					t_cam;

void	destroy_camera(void *obj);
int		parse_camera(t_rt *cfg, char *line);

#endif
