/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_inversion.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/17 19:14:53 by darbib            #+#    #+#             */
/*   Updated: 2020/06/19 01:48:05 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix.h"
#include "vector.h"
#include <stdio.h>

static double	det2d(double *m)
{
	return (m[0] * m[3] + m[1] * m[2]);
}

static double	det3d(double *m)
{
	double sum;
	double sub_m[4];

	sum = 0;
	sub_m[0] = m[4];
	sub_m[1] = m[5];
	sub_m[2] = m[7];
	sub_m[3] = m[8];
	sum += m[0] * det2d(sub_m);
	sub_m[0] = m[3];
	sub_m[2] = m[6];
	sum += -m[1] * det2d(sub_m);
	sub_m[1] = m[4];
	sub_m[3] = m[7];
	sum += m[2] * det2d(sub_m);
	return (sum);
}

static void	fill_submatrix(double *m, double *sub, int ban_row, int ban_col) 
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (i < DN * DN)
	{
		if (!(i / DN == ban_row || i % DN == ban_col))
			sub[j++] = m[i];
		i++;
	}
}

static void	cofactors(double *m_in, double *m_out, int adj)
{
	int row;
	int col;
	int elem;
	double sub[4];

	row = 0;
	while (row < DN)
	{
		col = 0;
		while (col < DN)
		{
			elem = row * DN + col;
			if (adj)
				elem = col * DN + row;
			fill_submatrix(m_in, sub, row, col);
			m_out[elem] = det2d(sub);
			if (elem % 2)
				m_out[elem] = -m_out[elem];
			col++;
		}
		row++;
	}
}

void	inverse(double *m_in, double *m_out)
{
	double inv_det;
	double adj[9];
	int i;
	
	inv_det = 1 / det3d(m_in);
	cofactors(m_in, adj, 1);
	i = 0;
	while (i < DN * DN)
	{
		m_out[i] = adj[i] * inv_det;
		i++;
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
	double m[9] = {-1, 0, 0, 1, -1, 0, 1, 1, 0};
	double inv_m[9];

	printf("----------------------\n");
	print_matrix(m);
	printf("----------------------\n");
	inverse(m, inv_m);
	print_matrix(inv_m);
	printf("----------------------\n");
	inverse(inv_m, m);
	print_matrix(m);
	printf("----------------------\n");
}
