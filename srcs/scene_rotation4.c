/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_rotation4.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 16:13:40 by darbib            #+#    #+#             */
/*   Updated: 2020/08/04 19:15:34 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rotation.h"
#include "print.h"
#include "actions.h"

void	assign_roll_matrices(double *roll, double *inv_roll)
{
	double cosphi;
	double sinphi;

	cosphi = cos(to_radian(ANGLE_SIZE));
	sinphi = sin(to_radian(ANGLE_SIZE));
	roll[0] = cosphi;
	roll[1] = -sinphi;
	roll[2] = 0;
	roll[3] = sinphi;
	roll[4] = cosphi;
	roll[5] = 0;
	roll[6] = 0;
	roll[7] = 0;
	roll[8] = 1;
	inv_roll[0] = cosphi;
	inv_roll[1] = sinphi;
	inv_roll[2] = 0;
	inv_roll[3] = -sinphi;
	inv_roll[4] = cosphi;
	inv_roll[5] = 0;
	inv_roll[6] = 0;
	inv_roll[7] = 0;
	inv_roll[8] = 1;
}
