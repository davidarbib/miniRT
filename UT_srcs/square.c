/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   square.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 18:36:28 by darbib            #+#    #+#             */
/*   Updated: 2020/06/29 14:00:11 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "error.h"
#include "print.h"

void	compute_square_edges(t_square *square)
{
	t_vect n;
	t_vect p;
	
	n = square->orient;
	p = square->pos;
	if (is_zero(n.x) && is_zero(n.y))
		square->edge1 = (t_vect) {p.x + 1, p.y + 1, p.z};
	else if (is_zero(n.x) && is_zero(n.z))
		square->edge1 = (t_vect) {p.x + 1, p.y, p.z + 1};
	else if (is_zero(n.y) && is_zero(n.z))
		square->edge1 = (t_vect) {p.x, p.y + 1, p.z + 1};
	else if (is_zero(n.z))
	{
		square->edge1.x = p.x + 1;
		square->edge1.y = (n.x * (p.x + 1) + n.z * (p.z + 1) - dot(&n, &p)) / -n.y;
		square->edge1.z = p.z + 1;
	}
	else
	{
		square->edge1.x = p.x + 1;
		square->edge1.y = p.y + 1;
		square->edge1.z = (n.x * (p.x + 1) + n.y * (p.y + 1) - dot(&n, &p)) / -n.z;
	}
	sub_vect(&square->edge1, &p, &square->edge1); 
	cross(&n, &square->edge1, &square->edge2);
}

int main()
{
	t_square square;

	square.pos = (t_vect) {1, 1, 1};
	square.orient = (t_vect) {1, -3, 4};
	compute_square_edges(&square);
	printf("----------\n");
	print_vect(&square.edge1); 
	printf("dot : %.8lf\n", dot(&square.orient, &square.edge1));
	printf("dot : %.8lf\n", dot(&square.orient, &square.edge2));
	printf("dot : %.8lf\n", dot(&square.edge1, &square.edge2));
			
	square.pos = (t_vect) {4, 2, 3};
	square.orient = (t_vect) {8, -2, 1};
	compute_square_edges(&square);
	printf("----------\n");
	print_vect(&square.edge1); 
	printf("dot : %.8lf\n", dot(&square.orient, &square.edge1));
	printf("dot : %.8lf\n", dot(&square.orient, &square.edge2));
	printf("dot : %.8lf\n", dot(&square.edge1, &square.edge2));

	square.pos = (t_vect) {0, 1, 1};
	square.orient = (t_vect) {1, 0, 0};
	compute_square_edges(&square);
	printf("----------\n");
	print_vect(&square.edge1); 
	printf("dot : %.8lf\n", dot(&square.orient, &square.edge1));
	printf("dot : %.8lf\n", dot(&square.orient, &square.edge2));
	printf("dot : %.8lf\n", dot(&square.edge1, &square.edge2));

	square.pos = (t_vect) {1, 0, 1};
	square.orient = (t_vect) {0, 1, 0};
	compute_square_edges(&square);
	printf("----------\n");
	print_vect(&square.edge1); 
	printf("dot : %.8lf\n", dot(&square.orient, &square.edge1));
	printf("dot : %.8lf\n", dot(&square.orient, &square.edge2));
	printf("dot : %.8lf\n", dot(&square.edge1, &square.edge2));

	square.pos = (t_vect) {1, 3, 0};
	square.orient = (t_vect) {0, 0, 1};
	compute_square_edges(&square);
	printf("----------\n");
	print_vect(&square.edge1); 
	printf("dot : %.8lf\n", dot(&square.orient, &square.edge1));
	printf("dot : %.8lf\n", dot(&square.orient, &square.edge2));
	printf("dot : %.8lf\n", dot(&square.edge1, &square.edge2));

	square.pos = (t_vect) {1, 1, 0};
	square.orient = (t_vect) {0, 0, 1};
	compute_square_edges(&square);
	printf("----------\n");
	print_vect(&square.edge1); 
	printf("dot : %.8lf\n", dot(&square.orient, &square.edge1));
	printf("dot : %.8lf\n", dot(&square.orient, &square.edge2));
	printf("dot : %.8lf\n", dot(&square.edge1, &square.edge2));

	square.pos = (t_vect) {2, 2, 2};
	square.orient = (t_vect) {0, 0, 1};
	compute_square_edges(&square);
	printf("----------\n");
	print_vect(&square.edge1); 
	printf("dot : %.8lf\n", dot(&square.orient, &square.edge1));
	printf("dot : %.8lf\n", dot(&square.orient, &square.edge2));
	printf("dot : %.8lf\n", dot(&square.edge1, &square.edge2));

	square.pos = (t_vect) {2, 2, 2};
	square.orient = (t_vect) {1, 1, 0};
	compute_square_edges(&square);
	printf("----------\n");
	print_vect(&square.edge1); 
	printf("dot : %.8lf\n", dot(&square.orient, &square.edge1));
	printf("dot : %.8lf\n", dot(&square.orient, &square.edge2));
	printf("dot : %.8lf\n", dot(&square.edge1, &square.edge2));

	square.pos = (t_vect) {2, 2, 2};
	square.orient = (t_vect) {0, 1, 1};
	compute_square_edges(&square);
	printf("----------\n");
	print_vect(&square.edge1); 
	printf("dot : %.8lf\n", dot(&square.orient, &square.edge1));
	printf("dot : %.8lf\n", dot(&square.orient, &square.edge2));
	printf("dot : %.8lf\n", dot(&square.edge1, &square.edge2));

	square.pos = (t_vect) {2, 2, 2};
	square.orient = (t_vect) {1, 0, 1};
	compute_square_edges(&square);
	printf("----------\n");
	print_vect(&square.edge1); 
	printf("dot : %.8lf\n", dot(&square.orient, &square.edge1));
	printf("dot : %.8lf\n", dot(&square.orient, &square.edge2));
	printf("dot : %.8lf\n", dot(&square.edge1, &square.edge2));
}
