/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_flush_event.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pqueiroz <pqueiroz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 00:13:06 by ol                #+#    #+#             */
/*   Updated: 2020/02/18 14:42:00 by pqueiroz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_int.h"

int	mlx_flush_event(t_xvar *xvar)
{
	XEvent ev;

	while (XPending(xvar->display))
	{
		XNextEvent(xvar->display, &ev);
	}
	return (0);
}
