/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vect_operations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/21 11:38:03 by darbib            #+#    #+#             */
/*   Updated: 2020/04/21 18:58:55 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"
#include <math.h>


double	scalar_product(t_vect *vect1, t_vect *vect2)
{
	double total;
	
	total = vect1->x * vect2->x;
	total += vect1->y * vect2->y;
	total += vect1->z * vect2->z;
	return (total);
}

void	cross_product(t_vect *vect1, t_vect *vect2, t_vect *vect_out)
{
	t_vect vect_out;

	vect_out->x = vect1->x * vect2->x;
	vect_out->y = vect1->y * vect2->y;
	vect_out->z = vect1->z * vect2->z;
	return (vect_out);
}

void	add_vect(t_vect *vect1, t_vect *vect2, t_vect *vect_out)
{
	t_vect vect_out;

	vect_out->x = vect1->x + vect2->x;
	vect_out->y = vect1->y + vect2->y;
	vect_out->z = vect1->z + vect2->z;
	return (vect_out);
}

void	sub_vect(t_vect *vect1, t_vect *vect2, t_vect *vect_out)
{
	t_vect vect_out;

	vect_out->x = vect1->x - vect2->x;
	vect_out->y = vect1->y - vect2->y;
	vect_out->z = vect1->z - vect2->z;
	return (vect_out);
}
