/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_int_get_visual.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pqueiroz <pqueiroz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 00:39:02 ol                #+#    #+#             */
/*   Updated: 2020/01/29 00:39:03 by pqueiroz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_int.h"

/*
** We need a private colormap for non-default Visual.
*/

int	mlx_int_get_visual(t_xvar *xvar)
{
	XVisualInfo	*vi;
	XVisualInfo	template;
	int			nb_item;

	xvar->private_cmap = 0;
	xvar->visual = DefaultVisual(xvar->display, xvar->screen);
	if (xvar->visual->class == TrueColor)
		return (0);
	template.class = TrueColor;
	template.depth = xvar->depth;
	if (!(vi = XGetVisualInfo(xvar->display, VisualDepthMask | VisualClassMask,
		&template, &nb_item)))
		return (-1);
	xvar->visual = vi->visual;
	xvar->private_cmap = 1;
	return (0);
}
