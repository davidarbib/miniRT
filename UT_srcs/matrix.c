/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/27 16:45:28 by darbib            #+#    #+#             */
/*   Updated: 2020/06/13 18:53:19 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "matrix.h"

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

int main()
{
	double m1[DN * DN] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
	double m2[DN * DN] = {2, 4, 8, 11, 9, 3, 1, 3, 5};
	double m_out[DN * DN];

	matrix_product(m2, m1, m_out);	
	print_matrix(m_out);
}
