/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/15 16:50:10 by darbib            #+#    #+#             */
/*   Updated: 2020/06/15 16:58:27 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

double	to_radian(double degree)
{
	return (degree * M_PI / 180.);
}

double	to_degree(double radian)
{
	return (radian * 180. / M_PI);
}
