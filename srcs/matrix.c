/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/27 16:45:28 by darbib            #+#    #+#             */
/*   Updated: 2020/04/27 18:40:58 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix.h"

static double	get_object_value(t_matrix *m1, t_matrix *m2, int i, int j)
{
	int x;
	int y;
	double sum;
	
	sum = 0;
	x = 0;
	while (x < m1->rows)
	{
		y = 0;
		while (y < m2->cols)
		{
			sum += m1->obj[i + m1->cols * y] * m2->obj[x + m2->cols * y]  
			y++
		}
		x++;
	}
	return (sum);	
}

void			matrix_product(t_matrix *m1, t_matrix *m2, t_matrix *m_out)
{
	int i;
	int j;
	
	m_out->rows = m1->rows;
	m_out->cols = m2->cols;
	i = 0;
	while (i < m_out->rows)
	{
		j = 0;
		while (j < m_out->cols)
		{
			m_out.obj[i + j * m_out->cols] = get_object_value(m1, m2, i, j);
			j++;
		}
		i++;
	}
}
