/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 16:16:25 by darbib            #+#    #+#             */
/*   Updated: 2020/08/05 00:11:02 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "error.h"

void		check_data(char *line, t_rt *cfg)
{
	int i = 0;
	(void)i;
	while (*line)
	{
		if (!ft_isdigit(*line) && !ft_isblank(*line)
			&& *line != SEP && *line != '.'
			&& *line != '-' && *line != '+')
			parse_error(E_BADCHAR, cfg);
		line++;
	}
}

static int	check_vector(const char *str)
{
	int n_sep;

	n_sep = 0;
	while (*str && !ft_isblank(*str))
	{
		if (*str == SEP)
		{
			if ((!ft_isdigit(*(str - 1)) && *(str - 1) != '.') 
				|| (!ft_isdigit(*(str + 1)) && *(str + 1) != '-'
					&& *(str + 1) != '+'))
				return (0);
			if ((*(str + 1) == '+' || *(str + 1) == '-')
					&& !ft_isdigit(*(str + 2)))
				return (0);
			n_sep++;
		}
		if ((*str == '.')
			&& !ft_isdigit(*(str - 1))
			&& !ft_isdigit(*(str + 1)))
			return (0);
		str++;
	}
	if (n_sep != 2)
		return (0);
	return (1);
}

void		get_vector(char **line, t_rt *cfg, t_vect *vect)
{
	if (!check_vector(*line))
		parse_error(E_BADVECT, cfg);
	vect->x = ft_atof_mv(line);
	(*line)++;
	vect->y = ft_atof_mv(line);
	(*line)++;
	vect->z = ft_atof_mv(line);
}

static int	check_rgb(const char *str)
{
	int n_sep;

	n_sep = 0;
	while (*str && !ft_isblank(*str))
	{
		if (*str == SEP)
		{
			if (!(ft_isdigit(*(str - 1)) && ft_isdigit(*(str + 1))))
				return (0);
			n_sep++;
		}
		str++;
	}
	if (n_sep != 2)
		return (0);
	return (1);
}

int			get_rgb(unsigned char *rgb, char **line)
{
	int tmp;
	int i;

	if (!(check_rgb(*line)))
		return (0);
	i = -1;
	while (++i < 3)
	{
		tmp = ft_atoi_mv(line);
		if (tmp < 0 || tmp > 255)
			return (0);
		rgb[i] = (unsigned char)tmp;
		if (i < 2)
		{
			if (**line != SEP)
				return (0);
			(*line)++;
		}
		else
		{
			if (**line && !(ft_isblank(**line)))
				return (0);
		}
	}
	return (1);
}
