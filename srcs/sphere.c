/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 18:43:21 by darbib            #+#    #+#             */
/*   Updated: 2020/03/03 16:53:51 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "rt_errors.h"

void	destroy_sphere(void *obj)
{
	t_sphere *sphere;
	
	sphere = (t_sphere *)obj;
	free(sphere->pos);
	sphere->pos = NULL;
}

int		parse_sphere(t_rt *cfg, char *line)
{
	t_sphere *sphere;
	
	check_data(line, cfg);
	if (!(sphere = (t_sphere *)malloc(sizeof(t_sphere))))
		sys_error(cfg);
	if (!(sphere->pos = get_vector(&line, cfg)))
		parse_error(E_BADVECT, cfg);
}
