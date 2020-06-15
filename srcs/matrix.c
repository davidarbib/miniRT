/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/27 16:45:28 by darbib            #+#    #+#             */
/*   Updated: 2020/06/15 15:56:59 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix.h"
#include "vector.h"
#include "stdio.h"

static double	get_object_value(double *m1, double *m2, int i, int j)
{
	int z;
	double sum;
	
	sum = 0;
	z = 0;
	while (z < DN)
	{
		sum += m1[z + DN * j] * m2[i + DN * z];
		z++;
	}
	return (sum);	
}

void			matrix_product(double *m1, double *m2, double *m_out)
{
	int i;
	int j;
	
	j = 0;
	while (j < DN)
	{
		i = 0;
		while (i < DN)
		{
			m_out[i + j * DN] = get_object_value(m1, m2, i, j);
			i++;
		}
		j++;
	}
}

void			matrix_by_vect(double *m, t_vect *v_in, t_vect *v_out)
{
	v_out->x = v_in->x * m[0] + v_in->y * m[1] + v_in->z * m[2];
	v_out->y = v_in->x * m[3] + v_in->y * m[4] + v_in->z * m[5];
	v_out->z = v_in->x * m[6] + v_in->y * m[7] + v_in->z * m[8];
}

void			print_matrix(double *m)
{
	int i;
	int j;
	
	j = 0;
	while (j < DN)
	{
		i = 0;
		while (i < DN)
		{
			printf("%lf ", m[i + DN * j]);
			i++;
		}
		j++;
		printf("\n");
	}
}
