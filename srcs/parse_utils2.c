/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 18:20:09 by darbib            #+#    #+#             */
/*   Updated: 2020/03/10 11:22:45 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "rt_errors.h"

void	parse_amb(t_rt *cfg, char *line)
{
	check_data(line, cfg);
	line = ft_pass_spaces(line);
	cfg->ambient_ratio = ft_atof_mv(&line);
	if (cfg->ambient_ratio < 0.0 || cfg->ambient_ratio > 1.0)
		parse_error(E_BADRATIO, cfg);
	line = ft_pass_spaces(line);
	if (!(get_rgb(cfg->ambient_rgb, &line)))
		parse_error(E_BADRGB, cfg);
}

void	parse_res(t_rt *cfg, char *line)
{
	check_data(line, cfg);
	line = ft_pass_spaces(line);
	cfg->resx = ft_atoi_mv(&line);
	line = ft_pass_spaces(line);
	cfg->resy = ft_atoi_mv(&line);
	if (cfg->resx < 0 || cfg->resy < 0)
		parse_error(E_BADRES, cfg);
}
