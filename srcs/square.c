/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   square.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 18:36:28 by darbib            #+#    #+#             */
/*   Updated: 2020/08/09 14:03:05 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "square.h"
#include "error.h"

void	destroy_square(void *obj)
{
	t_square *square;

	square = (t_square *)obj;
	free(square);
	square = NULL;
}

void	check_square(t_rt *cfg, t_square *square)
{
	if (!is_orientation_vect(&square->orient))
		parse_error(E_ORIENT, cfg);
	if (is_null_vect(square->orient))
		parse_error(E_NULLV, cfg);
	if (square->height <= 0.)
		parse_error(E_HEIGHT, cfg);
}

void	parse_square(t_rt *cfg, char *line)
{
	t_square	*square;

	check_data(line, cfg);
	if (!(square = (t_square *)malloc(sizeof(t_square))))
		sys_error(cfg);
	cfg->current_obj_addr = (void *)square;
	line = ft_pass_spaces(line);
	get_vector(&line, cfg, &square->pos);
	line = ft_pass_spaces(line);
	get_vector(&line, cfg, &square->orient);
	line = ft_pass_spaces(line);
	square->height = ft_atof_mv(&line);
	line = ft_pass_spaces(line);
	if (*line == SEP)
		parse_error(E_MISSPPTY, cfg);
	if (!(get_rgb(square->rgb, &line)))
		parse_error(E_BADRGB, cfg);
	trailing_char_detect(line, cfg);
	check_square(cfg, square);
	if (cfg->squares)
		ft_lstadd_back(&(cfg->squares), ft_lstnew(square));
	else
		cfg->squares = ft_lstnew(square);
}
