/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_loop.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pqueiroz <pqueiroz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 01:17:39 ol                #+#    #+#             */
/*   Updated: 2020/01/29 01:17:40 by pqueiroz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_int.h"

extern int	(*(g_mlx_int_param_event[]))();

int			mlx_loop(t_xvar *xvar)
{
	XEvent		ev;
	t_win_list	*win;

	mlx_int_set_win_event_mask(xvar);
	xvar->do_flush = 0;
	while (42)
	{
		while (!xvar->loop_hook || XPending(xvar->display))
		{
			XNextEvent(xvar->display, &ev);
			win = xvar->win_list;
			while (win && (win->window!=ev.xany.window))
				win = win->next;
			if (win && ev.type < MLX_MAX_EVENT)
				if (win->hooks[ev.type].hook)
					g_mlx_int_param_event[ev.type](xvar, &ev, win);
		}
		xvar->loop_hook(xvar->loop_param);
	}
	return (0);
}
