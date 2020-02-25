/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 15:57:55 by darbib            #+#    #+#             */
/*   Updated: 2020/02/25 15:58:55 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERA_H
# define CAMERA_H

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

#endif
