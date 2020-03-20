/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_parse_steps_1_4.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pqueiroz <pqueiroz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 14:18:18 by pqueiroz          #+#    #+#             */
/*   Updated: 2020/02/18 15:00:15 by pqueiroz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_xpm_priv.h"

/*
** mlx_int_parse_xpm_first_step - Does first parsing and validates some
** information.
*/

bool
	mlx_int_parse_xpm_first_step(t_xpm_parse_ctx *self)
{
	if (!(self->line = self->f(self->info, &self->pos, self->info_size)) ||
		!(self->tab = mlx_int_str_to_wordtab(self->line)) ||
		!(self->width = atoi(self->tab[0])) ||
		!(self->height = atoi(self->tab[1])) ||
		!(self->nc = atoi(self->tab[2])) ||
		!(self->cpp = atoi(self->tab[3])))
	{
		return (xpm_parse_ctx_finish(self));
	}
	free(self->tab);
	self->tab = NULL;
	return (true);
}

/*
** mlx_int_parse_xpm_second_step - Initializes colors_direct or colors according
** to cpp.
*/

bool
	mlx_int_parse_xpm_second_step(t_xpm_parse_ctx *self)
{
	size_t	alloc_sz;

	if (self->cpp <= 2)
	{
		self->method = 1;
		alloc_sz = ((self->cpp == 2) ? 65536 : 256) * sizeof(int);
		if (!(self->colors_direct = malloc(alloc_sz)))
			return (xpm_parse_ctx_finish(self));
	}
	else
	{
		if (!(self->colors = malloc(self->nc * sizeof(*self->colors))))
			return (xpm_parse_ctx_finish(self));
	}
	return (true);
}

static bool
	mlx_int_parse_xpm_third_step_aux(t_xpm_parse_ctx *self, int i)
{
	int	col;
	int	rgb_col;

	if (self->rgb_col == -1)
	{
		if (!(self->clip_data = malloc(4 * self->width * self->height)) ||
			!(self->clip_img = XCreateImage(self->xvar->display,
				self->xvar->visual, 1, XYPixmap, 0, self->clip_data,
				self->width, self->height, 8, (self->width + 7) / 8)))
			return (xpm_parse_ctx_finish(self));
		memset(self->clip_data, 0xFF, 4 * self->width * self->height);
	}
	col = mlx_int_get_col_name(self->line, self->cpp);
	rgb_col = (self->rgb_col >= 0) ?
			mlx_get_color_value(self->xvar, self->rgb_col) : self->rgb_col;
	if (self->method)
		self->colors_direct[col] = rgb_col;
	else
		self->colors[i] = (t_xpm_col){ .name=col, .col=self->rgb_col };
	free(self->tab);
	self->tab = NULL;
	return (true);
}

bool
	mlx_int_parse_xpm_third_step(t_xpm_parse_ctx *self)
{
	int i;
	int j;

	i = self->nc;
	while (i--)
	{
		if (!(self->line = self->f(self->info, &self->pos, self->info_size)) ||
			!(self->tab = mlx_int_str_to_wordtab(self->line + self->cpp)))
			return (xpm_parse_ctx_finish(self));
		j = 0;
		while (self->tab[j] && strcmp(self->tab[j++], "c"))
			;
		if (!self->tab[j])
			return (xpm_parse_ctx_finish(self));
		self->rgb_col = mlx_int_get_text_rgb(self->tab[j], self->tab[j + 1]);
		if (!mlx_int_parse_xpm_third_step_aux(self, i))
			return (xpm_parse_ctx_finish(self));
	}
	return (true);
}

bool
	mlx_int_parse_xpm_fourth_step(t_xpm_parse_ctx *self)
{
	if (!(self->img = mlx_new_image(self->xvar, self->width, self->height)))
		return (xpm_parse_ctx_finish(self));
	self->opp = self->img->bpp / 8;
	return (true);
}
