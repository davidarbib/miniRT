/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   square.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 18:36:28 by darbib            #+#    #+#             */
/*   Updated: 2020/03/10 15:18:40 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "rt_errors.h"
#include "ft_printf.h"

void	destroy_square(void *obj)
{
	t_square *square;
	
	square = (t_square *)obj;
	free(square->pos);
	free(square->ort);
	square->pos = NULL;
	square->ort = NULL;
}


void	parse_square(t_rt *cfg, char *line)
{
	t_square	*square;
	
	check_data(line, cfg);
	if (!(square = (t_square *)malloc(sizeof(t_square))))
		sys_error(cfg);
	line = ft_pass_spaces(line);
	if (!(square->pos = get_vector(&line, cfg)))
		parse_error(E_BADVECT, cfg);
	line = ft_pass_spaces(line);
	if (!(square->ort = get_vector(&line, cfg)))
		parse_error(E_BADVECT, cfg);
	line = ft_pass_spaces(line);
	square->height = ft_atof_mv(&line);	
	line = ft_pass_spaces(line);
	if (!(get_rgb(square->rgb, &line)))
		parse_error(E_BADRGB, cfg); 
	if (cfg->squares)
		ft_lstadd_back(&(cfg->squares), ft_lstnew(square));
	else
		cfg->squares = ft_lstnew(square);
}

void	print_square(void *obj)
{
	t_square *square;

	square = (t_square *)obj;
	ft_printf("Pos : %f, %f, %f\n", square->pos->x, square->pos->y,
			square->pos->z);
	ft_printf("Orientation : %f, %f, %f\n", square->ort->x, square->ort->y,
			square->ort->z);
	ft_printf("Height : %f\n", square->height);
	ft_printf("RGB : %d,%d,%d\n", square->rgb[0], square->rgb[1],
				square->rgb[2]);
	ft_printf("\n");
}
