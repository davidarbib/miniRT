/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   square2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/04 22:40:45 by darbib            #+#    #+#             */
/*   Updated: 2020/08/04 22:44:29 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "square.h"
#include "error.h"
#include "print.h"

void	compute_square_points(t_square *square)
{
	add_vect(&square->pos, &square->edge1, &square->pt1);
	add_vect(&square->pt1, &square->edge2, &square->pt2);
	add_vect(&square->pos, &square->edge2, &square->pt3);
}

void	compute_current_edges(t_square *square)
{
	sub_vect(&square->current_pt1, &square->current_pos,
			&square->current_edge1);
	sub_vect(&square->current_pt3, &square->current_pos,
			&square->current_edge2);
}

void	compute_square_edges(t_square *sq)
{
	t_vect n;
	t_vect p;

	n = sq->orient;
	p = sq->pos;
	if (is_zero(n.x) && is_zero(n.y))
		sq->edge1 = (t_vect) {p.x + 1, p.y + 1, p.z};
	else if (is_zero(n.x) && is_zero(n.z))
		sq->edge1 = (t_vect) {p.x + 1, p.y, p.z + 1};
	else if (is_zero(n.y) && is_zero(n.z))
		sq->edge1 = (t_vect) {p.x, p.y + 1, p.z + 1};
	else if (is_zero(n.z))
	{
		sq->edge1.x = p.x + 1;
		sq->edge1.y = (n.x * (p.x + 1) + n.z * (p.z + 1) - dot(&n, &p)) / -n.y;
		sq->edge1.z = p.z + 1;
	}
	else
	{
		sq->edge1.x = p.x + 1;
		sq->edge1.y = p.y + 1;
		sq->edge1.z = (n.x * (p.x + 1) + n.y * (p.y + 1) - dot(&n, &p)) / -n.z;
	}
	sub_vect(&sq->edge1, &p, &sq->edge1);
	cross(&n, &sq->edge1, &sq->edge2);
}
