/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rasterize.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/09 11:32:45 by darbib            #+#    #+#             */
/*   Updated: 2020/06/09 12:27:18 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gaphics.h"

void	perspective_proj(t_vect *v_in, )
void	rasterize(t_trig *triangles, int n)
{
	int x;
	int y;
	t_trig *trig;

	while (--n >= 0)
	{
		trig = triangles + n;
		x = trig->current_pt1.x / trig->current_pt1.z * -1;
		y = trig->current_pt1.y / trig->current_pt1.z * -1;
		alter_pixel(
	}
}
