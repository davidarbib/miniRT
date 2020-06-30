/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_obj2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/29 16:35:51 by darbib            #+#    #+#             */
/*   Updated: 2020/06/30 15:11:04 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"
#include "vector.h"
#include "print.h"

void	set_squares_edges(t_square *squares, int n)
{
	while (n--)
		compute_square_edges(squares + n);
} 

void	set_squares(t_square *squares, int n)
{
	t_square	*square;

	while (n--)
	{
		square = squares + n;
		normalize(&square->orient, &square->orient);
		vect_cpy(&square->pos, &square->current_pos);
		vect_cpy(&square->orient, &square->current_orient);
		vect_cpy(&square->edge1, &square->current_edge1);
		vect_cpy(&square->edge2, &square->current_edge2);
	}
}
