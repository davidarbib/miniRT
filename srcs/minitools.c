/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/15 16:50:10 by darbib            #+#    #+#             */
/*   Updated: 2020/08/04 18:53:26 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <vector.h>
#include <raytrace.h>

double	to_radian(double degree)
{
	return (degree * M_PI / 180.);
}

double	to_degree(double radian)
{
	return (radian * 180. / M_PI);
}

int		is_zero(double coord)
{
	return ((int)(coord * 100000) == 0);
}

void	get_hit_point(double t, t_vect direction, t_vect origin, t_vect *v_out)
{
	t_vect tmp;

	scale(t, &direction, &tmp);
	add_vect(&tmp, &origin, v_out);
}

void	to_rgb_ratio(unsigned char *rgb_in, t_vect *rgb_out)
{
	rgb_out->x = rgb_in[r] / 255.;
	rgb_out->y = rgb_in[g] / 255.;
	rgb_out->z = rgb_in[b] / 255.;
}
