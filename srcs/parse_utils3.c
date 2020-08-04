/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/04 22:34:24 by darbib            #+#    #+#             */
/*   Updated: 2020/08/04 22:50:43 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "error.h"

void	trailing_char_detect(char *line, t_rt *cfg)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (!ft_isblank(line[i]))
			parse_error(E_TRCHAR, cfg);
		i++;
	}
}
