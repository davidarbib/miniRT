/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   square.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 16:12:03 by darbib            #+#    #+#             */
/*   Updated: 2020/02/28 15:07:50 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SQUARE_H
# define SQUARE_H

# include "vector.h"
/*
** --- square ---
** pos : position vector
** ort : orientation vector [-1;1]
** height : ...
** rgb : rgb color
*/
typedef struct		s_square
{
	t_vect			*pos;
	t_vect			*ort;
	float			height;
	unsigned char	rgb[3];
}					t_square;

#endif
