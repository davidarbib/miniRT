/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 18:20:09 by darbib            #+#    #+#             */
/*   Updated: 2020/08/04 22:52:41 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "error.h"

void			parse_amb(t_rt *cfg, char *line)
{
	check_data(line, cfg);
	if (cfg->flags & AMB)
		parse_error(E_TOOAMB, cfg);
	cfg->flags |= AMB;
	line = ft_pass_spaces(line);
	cfg->ambient_ratio = ft_atof_mv(&line);
	if (!is_ratio(cfg->ambient_ratio))
		parse_error(E_BADRATIO, cfg);
	line = ft_pass_spaces(line);
	if (!(get_rgb(cfg->ambient_rgb, &line)))
		parse_error(E_BADRGB, cfg);
	trailing_char_detect(line, cfg);
}

void			parse_res(t_rt *cfg, char *line)
{
	check_data(line, cfg);
	if (cfg->flags & RES)
		parse_error(E_TOORES, cfg);
	cfg->flags |= RES;
	line = ft_pass_spaces(line);
	cfg->resx = ft_atoi_mv(&line);
	line = ft_pass_spaces(line);
	cfg->resy = ft_atoi_mv(&line);
	if (cfg->resx <= 0 || cfg->resy <= 0)
		parse_error(E_BADRES, cfg);
	trailing_char_detect(line, cfg);
}

int				is_ratio(float ratio)
{
	if (ratio >= 0.0 && ratio <= 1.0)
		return (1);
	return (0);
}

static int		is_orientation_value(float value)
{
	if (value >= -1.0 && value <= 1.0)
		return (1);
	return (0);
}

int				is_orientation_vect(t_vect *vect)
{
	int	answer;

	answer = 1;
	answer *= is_orientation_value(vect->x);
	answer *= is_orientation_value(vect->y);
	answer *= is_orientation_value(vect->z);
	return (answer);
}
