/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 13:50:26 by darbib            #+#    #+#             */
/*   Updated: 2020/05/30 21:22:32 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "error.h"
#include "ft_printf.h"
#include "font_color.h"
#include "scene.h"

void	parse_error(char *msg, t_rt *cfg)
{
	if (cfg->flags & IN_PARSING)
	{
		ft_printf(FONT_BOLDRED "Error " FONT_RESET);
		ft_printf("line %d : %s\n", cfg->linenb, msg);
	}
	else
	{
		ft_printf(FONT_BOLDRED "Error " FONT_RESET);
		ft_printf(": %s\n", msg);
	}
	destroy_cfg(cfg);
	exit(EXIT_FAILURE);
}

void	sys_error(t_rt *cfg)
{
	perror(FONT_BOLDRED "Error " FONT_RESET);
	destroy_cfg(cfg);
	exit(EXIT_FAILURE);
}

void	bmp_sys_error(t_scene *scene)
{
	perror(FONT_BOLDRED "Image output error " FONT_RESET);
	destroy_scene(scene);
	exit(EXIT_FAILURE);
}
