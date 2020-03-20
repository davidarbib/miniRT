/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_xpm.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pqueiroz <pqueiroz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 15:17:52 by pqueiroz          #+#    #+#             */
/*   Updated: 2020/01/30 15:01:41 by pqueiroz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mlx_int.h"
#include "mlx_xpm_priv.h"

bool
	xpm_parse_ctx_finish(t_xpm_parse_ctx *self)
{
	if (self->colors)
		free(self->colors);
	if (self->tab)
		free(self->tab);
	if (self->colors_direct)
		free(self->colors_direct);
	if (self->img)
	{
		XDestroyImage(self->img->image);
		XFreePixmap(self->xvar->display, self->img->pix);
		free(self->img);
	}
	return (false);
}

char	*mlx_int_get_line(char *ptr, int *pos, int size)
{
	int		pos2;
	int		pos3;
	int		pos4;

	if (-1 == (pos2 = mlx_int_str_str(ptr + *pos, "\"", size - *pos)))
		return (NULL);
	if (-1 == (pos3 = mlx_int_str_str(ptr + (*pos + pos2 + 1), "\"",
										size - (*pos - pos2 - 1))))
		return (NULL);
	ptr[*pos + pos2] = 0;
	ptr[*pos + pos2 + 1 + pos3] = 0;
	*pos += pos2 + pos3 + 2;
	pos4 = *pos + pos2 + 1;
	return (ptr + pos4);
}

char
	*mlx_int_static_line(char **xpm_data, int *pos, int size)
{
	static char		*copy = NULL;
	static int		len = 0;
	int				len2;
	char			*str;

	(void)size;
	str = xpm_data[(*pos)++];
	if ((len2 = strlen(str)) > len)
	{
		if (copy)
			free(copy);
		if (!(copy = malloc(len2 + 1)))
			return (NULL);
		len = len2;
	}
	strlcpy(copy, str, len2 + 1);
	return (copy);
}

int
	mlx_int_get_col_name(const char *str, int size)
{
	int res;

	res = 0;
	while (size--)
		res = (res << 8) + *(str++);
	return (res);
}

int
	mlx_int_get_text_rgb(char *name, char *end)
{
	int		i;
	char	buff[64];

	if (*name == '#')
		return (strtol(name + 1, NULL, 16));
	if (end)
	{
		snprintf(buff, 64, "%s %s", name, end);
		name = buff;
	}
	i = 0;
	while (g_mlx_col_name[i].name)
	{
		if (strcasecmp(g_mlx_col_name[i].name, name) == 0)
			return (g_mlx_col_name[i].color);
		++i;
	}
	return (0);
}

int
	mlx_int_xpm_set_pixel(t_xpm_set_pixel_data *data)
{
	int dec;
	int ind;

	dec = data->opp;
	while (dec--)
	{
		ind = data->x * data->opp;
		if (data->img->image->byte_order)
			data->data[ind + dec] = data->col & 0xFF;
		else
			data->data[ind + data->opp - dec - 1] = data->col & 0xFF;
		data->col >>= 8;
	}
	return (0);
}
