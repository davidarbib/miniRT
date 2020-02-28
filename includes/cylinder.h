/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 15:59:58 by darbib            #+#    #+#             */
/*   Updated: 2020/02/28 15:07:15 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CYLINDER_H
# define CYLINDER_H

# include "vector.h"
/*
** --- cylinder ---
** pos : position vector
** ort : orientation vector [-1;1]
** diam : diameter
** height : ...
** rgb : rgb color
*/
typedef struct		s_cyld
{
	t_vect			*pos;
	t_vect			*ort;
	float			height;
	unsigned char	rgb[3];
}					t_cyld;

void	destroy_cylinder(void *obj);

#endif
