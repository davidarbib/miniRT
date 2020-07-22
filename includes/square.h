/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   square.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 16:12:03 by darbib            #+#    #+#             */
/*   Updated: 2020/07/22 17:37:50 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SQUARE_H
# define SQUARE_H

# include "vector.h"
/*
** --- square ---
** pos : position vector
** orient : orientation vector [-1;1]
** height : ...
** rgb : rgb color
*/
typedef struct		s_square
{
	t_vect			pos;
	t_vect			orient;
	t_vect			edge1;
	t_vect			edge2;
	t_vect			pt1;
	t_vect			pt2;
	t_vect			pt3;
	t_vect			current_pt1;
	t_vect			current_pt2;
	t_vect			current_pt3;
	t_vect			current_pos;
	t_vect			current_orient;
	t_vect			current_edge1;
	t_vect			current_edge2;
	float			height;
	unsigned char	rgb[3];
}					t_square;

void	destroy_square(void *obj);
void	print_square(void *obj);
void	compute_square_edges(t_square *square);
void	compute_square_points(t_square *square);
void	compute_current_edges(t_square *square);

#endif
