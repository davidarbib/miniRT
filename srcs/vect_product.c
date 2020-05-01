/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vect_product.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/21 11:38:03 by darbib            #+#    #+#             */
/*   Updated: 2020/05/01 21:54:38 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"
#include <math.h>

double	dot(t_vect *vect1, t_vect *vect2)
{
	double total;
	
	total = vect1->x * vect2->x;
	total += vect1->y * vect2->y;
	total += vect1->z * vect2->z;
	return (total);
}

void	cross(t_vect *vect1, t_vect *vect2, t_vect *vect_out)
{
	vect_out->x = vect1->y * vect2->z - vect1->z * vect2->y;
	vect_out->y = vect1->z * vect2->x - vect1->x * vect2->z;
	vect_out->z = vect1->x * vect2->y - vect1->y * vect2->x;
}

void	scale(double scalar, t_vect *vect, t_vect *vect_out)
{
	vect_out->x = vect->x * scalar;
	vect_out->y = vect->y * scalar;
	vect_out->z = vect->z * scalar;
}
