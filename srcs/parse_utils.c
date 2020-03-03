/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 16:16:25 by darbib            #+#    #+#             */
/*   Updated: 2020/03/03 16:53:52 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "rt_errors.h"

void	check_data(char *line, t_rt *cfg)
{
	while (*line)
	{
		if (!ft_isdigit(*line) && !ft_isblank(*line)
			&& *line != SEP && *line != '.')
			parse_error(E_BADCHAR, cfg);
		line++;
	}
}

/*
** return allocated 3d vector
** from data in file
*/

t_vect	*get_vector(char **line, t_rt *cfg)
{
	t_vect *vect;

	if (!(vect = ((t_vect *)malloc(sizeof(t_vect)))))
		sys_error(cfg);
	vect->x = ft_atof_mv(&line);
	if (!(**line == SEP))
		return (NULL);
	vect->y = ft_atof_mv(&line);
	if (!(**line == SEP))
		return (NULL);
	vect->z = ft_atof_mv(&line);
	if (**line && !(ft_isblank(**line)))
		return (NULL);
	return (vect);
}
