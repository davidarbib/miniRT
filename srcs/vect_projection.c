/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vect_projection.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/21 11:38:03 by darbib            #+#    #+#             */
/*   Updated: 2020/08/04 19:23:26 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"
#include <math.h>
#include <stdio.h>

double	vect_norm(t_vect *vect)
{
	double total;

	total = vect->x * vect->x;
	total += vect->y * vect->y;
	total += vect->z * vect->z;
	return (sqrt(total));
}

void	normalize(t_vect *vect, t_vect *vect_out)
{
	double	norm;
	double	inv_norm;

	norm = vect_norm(vect);
	if (norm == 0.)
		return ;
	inv_norm = 1. / norm;
	vect_out->x = vect->x * inv_norm;
	vect_out->y = vect->y * inv_norm;
	vect_out->z = vect->z * inv_norm;
}

void	add_vect(t_vect *vect1, t_vect *vect2, t_vect *vect_out)
{
	vect_out->x = vect1->x + vect2->x;
	vect_out->y = vect1->y + vect2->y;
	vect_out->z = vect1->z + vect2->z;
}

void	sub_vect(t_vect *vect1, t_vect *vect2, t_vect *vect_out)
{
	vect_out->x = vect1->x - vect2->x;
	vect_out->y = vect1->y - vect2->y;
	vect_out->z = vect1->z - vect2->z;
}

void	ortho_projection(t_vect *v_initial, t_vect *v_support, t_vect *v_out)
{
	double top_product;
	double bot_product;

	top_product = dot(v_initial, v_support);
	bot_product = dot(v_support, v_support);
	scale(top_product / bot_product, v_support, v_out);
}
