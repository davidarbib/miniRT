/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 15:57:55 by darbib            #+#    #+#             */
/*   Updated: 2020/05/21 17:02:21 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERA_H
# define CAMERA_H

# include "vector.h"

/*
** --- camera ---
** pos : position vector
** orient : orientation vector [-1;1]
** fov : sight-field ([0;180] degrees)
*/
typedef struct		s_cam
{
	t_vect			*pos;
	t_vect			*orient;
	t_vect			*current_pos;
	t_vect			*current_orient;
	int				fov;
}					t_cam;

void	destroy_camera(void *obj);
void	print_cam(void *obj);

#endif
