/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 18:43:21 by darbib            #+#    #+#             */
/*   Updated: 2020/03/04 17:57:03 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_errors.h"
#include "general.h"
#include "sphere.h"

void	destroy_sphere(void *obj)
{
	t_sphere *sphere;
	
	sphere = (t_sphere *)obj;
	free(sphere->pos);
	sphere->pos = NULL;
}

void	parse_sphere(t_rt *cfg, char *line)
{
	t_sphere	*sphere;
	
	check_data(line, cfg);
	if (!(sphere = (t_sphere *)malloc(sizeof(t_sphere))))
		sys_error(cfg);
	line = ft_pass_spaces(line);
	if (!(sphere->pos = get_vector(&line, cfg)))
		parse_error(E_BADVECT, cfg);
	line = ft_pass_spaces(line);
	sphere->diam = ft_atof_mv(&line);	
	line = ft_pass_spaces(line);
	if (!(get_rgb(sphere->rgb, &line)))
		parse_error(E_BADRGB, cfg); 
}
