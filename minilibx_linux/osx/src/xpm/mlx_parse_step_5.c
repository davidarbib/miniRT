/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_parse_step_6.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pqueiroz <pqueiroz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 20:16:29 by pqueiroz          #+#    #+#             */
/*   Updated: 2020/01/28 20:27:18 by pqueiroz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_xpm_priv.h"

static void
	mlx_int_parse_xpm_fifth_step_inner_while(t_xpm_parse_ctx *self)
{
	int x;

	x = 0;
	while (x < self->width)
	{
		self->col_name = mlx_int_get_col_name(self->line + self->cpp * x,
												self->cpp);
		if (self->method)
			self->col = self->colors_direct[self->col_name];
		else
		{
			self->j = self->nc;
			while (self->j--)
				if (self->colors[self->j].name == self->col_name)
				{
					self->col = self->colors[self->j].col;
					self->j = 0;
				}
		}
		self->col = (self->col == -1) ? 0xFF000000 : self->col;
		mlx_int_xpm_set_pixel(self->data, self->col, x);
		++x;
	}
}

bool
	mlx_int_parse_xpm_fifth_step(t_xpm_parse_ctx *self)
{
	int i;

	i = self->height;
	self->data = self->img->buffer;
	while (i--)
	{
		if (!(self->line = self->f(self->info, &self->pos, self->info_size)))
			return (xpm_parse_ctx_finish(self));
		mlx_int_parse_xpm_fifth_step_inner_while(self);
		self->data += self->img->width * 4;
	}
	if (self->colors)
		free(self->colors);
	if (self->colors_direct)
		free(self->colors_direct);
	return (true);
}
