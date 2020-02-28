/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   square.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 18:36:28 by darbib            #+#    #+#             */
/*   Updated: 2020/02/27 18:36:18 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	destroy_square(void *obj)
{
	t_square *square;
	
	square = (t_square *)obj;
	free(square->pos);
	free(square->ort);
}

int		parse_square(t_rt *cfg, char *line)
{
}
