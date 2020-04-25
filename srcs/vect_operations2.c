/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vect_operations2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/21 11:38:03 by darbib            #+#    #+#             */
/*   Updated: 2020/04/21 15:39:21 by darbib           ###   ########.fr       */
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
	if (norm == 0)
		return ;
	inv_norm = 1 / norm;
	vect_out->x = vect->x * inv_norm;
	vect_out->y = vect->y * inv_norm;
	vect_out->z = vect->z * inv_norm;
}

void	mult_vector(double scalar, t_vect *vect, t_vect *vect_out)
{
	vect_out->x = vect->x * scalar;
	vect_out->y = vect->y * scalar;
	vect_out->z = vect->z * scalar;
}

void	div_vector(double scalar, t_vect *vect, t_vect *vect_out)
{
	vect_out->x = vect->x / scalar;
	vect_out->y = vect->y / scalar;
	vect_out->z = vect->z / scalar;
}

int main()
{
	t_vect v1;
	t_vect out;

	v1.x = 2;
	v1.y = 2;
	v1.z = 2;
	mult_vector(2, &v1, &out);
	printf("resultat : %f, %f, %f\n", out.x, out.y, out.z);
}
