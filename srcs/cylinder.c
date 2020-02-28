/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 18:50:39 by darbib            #+#    #+#             */
/*   Updated: 2020/02/27 18:32:39 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	destroy_cylinder(void *obj)
{
	t_cyld *plane;
	
	cylinder = (t_cyld *)obj;
	free(cylinder->pos);
	free(cylinder->ort);
	cylinder->pos = NULL;
	cylinder->ort = NULL;
}

int		parse_cylinder(t_rt *cfg, char *line)
{
}
