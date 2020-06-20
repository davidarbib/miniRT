/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 16:03:02 by darbib            #+#    #+#             */
/*   Updated: 2020/06/20 15:59:12 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLANE_H
# define PLANE_H

# include "vector.h"
/*
** --- plane ---
** pos : position vector
** orient : orientation vector [-1;1]
** rgb : rgb color
*/

typedef struct		s_plane
{
	t_vect			pos;
	t_vect			orient;
	t_vect			current_pos;
	t_vect			current_orient;
	unsigned char	rgb[3];
}					t_plane;

void	destroy_plane(void *obj);
void	print_plane(void *obj);
void	move_plane(t_plane *plane, t_vect *translation);

#endif
