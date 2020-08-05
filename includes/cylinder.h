/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 15:59:58 by darbib            #+#    #+#             */
/*   Updated: 2020/08/05 14:55:14 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CYLINDER_H
# define CYLINDER_H

# include "vector.h"

/*
** --- cylinder ---
** pos : position vector
** orient : orientation vector [-1;1]
** diam : diameter
** height : ...
** rgb : rgb color
*/
typedef struct		s_cylinder
{
	t_vect			pos;
	t_vect			orient;
	t_vect			current_pos;
	t_vect			current_orient;
	double			diam;
	double			radius;
	double			height;
	unsigned char	rgb[3];
}					t_cylinder;

void				destroy_cylinder(void *obj);
void				print_cyl(void *obj);

#endif
