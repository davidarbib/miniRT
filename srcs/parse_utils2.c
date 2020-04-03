/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 18:20:09 by darbib            #+#    #+#             */
/*   Updated: 2020/04/03 20:41:32 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "error.h"

void	parse_amb(t_rt *cfg, char *line)
{
	check_data(line, cfg);
	if (cfg->flags & AMB)
		parse_error(E_TOOAMB, cfg);
	cfg->flags |= AMB;
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
	if (cfg->flags & RES)
		parse_error(E_TOORES, cfg);
	cfg->flags |= RES;
	line = ft_pass_spaces(line);
	cfg->resx = ft_atoi_mv(&line);
	line = ft_pass_spaces(line);
	cfg->resy = ft_atoi_mv(&line);
	if (cfg->resx < 0 || cfg->resy < 0)
		parse_error(E_BADRES, cfg);
}
