/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 15:57:55 by darbib            #+#    #+#             */
/*   Updated: 2020/02/28 15:07:08 by darbib           ###   ########.fr       */
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

#endif
