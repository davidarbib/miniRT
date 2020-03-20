/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_parse_steps_5_6.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pqueiroz <pqueiroz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 14:46:45 by pqueiroz          #+#    #+#             */
/*   Updated: 2020/02/18 14:55:15 by pqueiroz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_xpm_priv.h"

static void
	mlx_int_parse_xpm_sixth_step_inner_while(t_xpm_parse_ctx *self, int i)
{
	int x;

	x = -1;
	while (++x < self->width)
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
		if (self->col == -1)
			XPutPixel(self->clip_img, self->x, self->height - 1 - i, 0);
		else
			mlx_int_xpm_set_pixel(&(t_xpm_set_pixel_data){
				self->img, self->data, self->opp, self->col, x });
	}
}

bool
	mlx_int_parse_xpm_sixth_step(t_xpm_parse_ctx *self)
{
	int i;

	i = self->height;
	self->data = self->img->data;
	while (i--)
	{
		if (!(self->line = self->f(self->info, &self->pos, self->info_size)))
			return (xpm_parse_ctx_finish(self));
		self->col = 0;
		mlx_int_parse_xpm_sixth_step_inner_while(self, i);
		self->data += self->img->size_line;
	}
	if (self->colors)
		free(self->colors);
	if (self->colors_direct)
		free(self->colors_direct);
	return (true);
}
