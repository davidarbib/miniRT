/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   square.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 16:12:03 by darbib            #+#    #+#             */
/*   Updated: 2020/06/26 16:24:47 by darbib           ###   ########.fr       */
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
	t_vect			current_pos;
	t_vect			current_orient;
	t_vect			edge1;
	t_vect			edge2;
	float			height;
	unsigned char	rgb[3];
}					t_square;

void	destroy_square(void *obj);
void	print_square(void *obj);

#endif
