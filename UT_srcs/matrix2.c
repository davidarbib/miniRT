/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/17 15:03:51 by darbib            #+#    #+#             */
/*   Updated: 2020/06/19 13:35:33 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix.h"
#include "vector.h"
#include <stdio.h>

void			print_2dmatrix(double *m);
void			print_matrix(double *m);

double	det2d(double *m)
{
	return (m[0] * m[3] - m[1] * m[2]);
}

double	det3d(double *m)
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

void	fill_submatrix(double *m, double *sub, int ban_row, int ban_col) 
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

void	cofactors(double *m_in, double *m_out, int adj)
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

/*
void	transpose(double *m_in, double *m_out)
{
	int row;
	int col;

	row = 0;
	while (row < DN)
	{
		col = 0;
		while (col < DN)
		{
			m_out[row * DN + col] = 
			col++;
		}
		row++;
	}
}
*/

void	inverse(double *m_in, double *m_out)
{
	double inv_det;
	double adj[9];
	int i;
	
	inv_det = 1 / det3d(m_in);
	printf("det = %lf\n", det3d(m_in));
	print_matrix(m_in);
	cofactors(m_in, adj, 1);
	i = 0;
	while (i < DN * DN)
	{
		m_out[i] = adj[i] * inv_det;
		i++;
	}
}

void	print_matrix(double *m)
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

void	print_2dmatrix(double *m)
{
	printf("%lf ", m[0]);
	printf("%lf\n", m[1]);
	printf("%lf ", m[2]);
	printf("%lf ", m[3]);
}

int main()
{
	double m[9] = {1, 0, 0, 0, 0, 1, 0, 1, 0};
	//double sub[4];
	double cof_m[9];
	double adj_m[9];
	double inv_m[9];
	print_matrix(m);
	//printf("det m = %lf\n", det3d(m));
	/*
	fill_submatrix(m, sub, 2, 2);
	print_2dmatrix(sub);
	*/
	printf("---------comatrice----------\n");
	cofactors(m, cof_m, 0);	
	print_matrix(cof_m);
	printf("-----------adj------------- \n");
	cofactors(m, adj_m, 1);	
	print_matrix(adj_m);
	printf("-----------inverse------------- \n");
	inverse(m, inv_m);
	print_matrix(inv_m);
}
