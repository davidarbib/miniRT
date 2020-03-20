/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_parse_step_1_5.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pqueiroz <pqueiroz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 20:13:17 by pqueiroz          #+#    #+#             */
/*   Updated: 2020/01/30 14:39:38 by pqueiroz         ###   ########.fr       */
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

bool
	mlx_int_parse_xpm_third_step(t_xpm_parse_ctx *self)
{
	int i;
	int j;
	int col;

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
		col = mlx_int_get_col_name(self->line, self->cpp);
		if (self->method)
			self->colors_direct[col] = self->rgb_col;
		else
			self->colors[i] = (t_xpm_col){ .name=col, .col=self->rgb_col };
		free(self->tab);
		self->tab = NULL;
	}
	return (true);
}

bool
	mlx_int_parse_xpm_fourth_step(t_xpm_parse_ctx *self)
{
	if (!(self->img = mlx_new_image(self->xvar, self->width, self->height)))
		return (xpm_parse_ctx_finish(self));
	self->opp = 4;
	return (true);
}
