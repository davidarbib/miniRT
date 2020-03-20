/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pqueiroz <pqueiroz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 00:17:41 ol                #+#    #+#             */
/*   Updated: 2020/01/29 00:18:50 by pqueiroz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_int.h"

int	mlx_hook(t_win_list *win, int x_event, int x_mask, int (*funct)(),
				void *param)
{
	win->hooks[x_event].hook = funct;
	win->hooks[x_event].param = param;
	win->hooks[x_event].mask = x_mask;
	return (0);
}

/*
** The functions bellow could be inline.
*/

int	mlx_do_key_autorepeatoff(t_xvar *xvar)
{
	XAutoRepeatOff(xvar->display);
	return (0);
}

int	mlx_do_key_autorepeaton(t_xvar *xvar)
{
	XAutoRepeatOn(xvar->display);
	return (0);
}

int	mlx_do_sync(t_xvar *xvar)
{
	XSync(xvar->display, False);
	return (0);
}
