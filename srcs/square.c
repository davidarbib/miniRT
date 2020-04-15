/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   square.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 18:36:28 by darbib            #+#    #+#             */
/*   Updated: 2020/04/15 20:15:35 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "error.h"
#include "ft_printf.h"

void	destroy_square(void *obj)
{
	t_square *square;
	
	square = (t_square *)obj;
	free(square->pos);
	free(square->ort);
	square->pos = NULL;
	square->ort = NULL;
	free(square);
	square = NULL;
}


static void	check_square(t_rt *cfg, t_square *square)
{
	if (!is_orientation_vect(square->ort))
		parse_error(E_ORIENT, cfg);
}

void	parse_square(t_rt *cfg, char *line)
{
	t_square	*square;
	
	check_data(line, cfg);
	if (!(square = (t_square *)malloc(sizeof(t_square))))
		sys_error(cfg);
	cfg->current_obj_addr = (void *)square;
	square->pos = NULL;
	square->ort = NULL;
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
	check_square(cfg, square);
	if (cfg->squares)
		ft_lstadd_back(&(cfg->squares), ft_lstnew(square));
	else
		cfg->squares = ft_lstnew(square);
}

void	print_square(void *obj)
{
	t_square *square;

	square = (t_square *)obj;
	printf("square ptr : %p\n", square);
	printf("Pos : %f, %f, %f\n", square->pos->x, square->pos->y,
	 	square->pos->z);
	printf("Orientation : %f, %f, %f\n", square->ort->x, square->ort->y,
	 	square->ort->z);
	printf("Height : %f\n", square->height);
	printf("RGB : %d,%d,%d\n", square->rgb[0], square->rgb[1],
	 		square->rgb[2]);
	printf("\n");
}
