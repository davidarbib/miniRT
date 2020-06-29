/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   square.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 18:36:28 by darbib            #+#    #+#             */
/*   Updated: 2020/06/27 23:25:33 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "error.h"
#include "print.h"

void	destroy_square(void *obj)
{
	t_square *square;
	
	square = (t_square *)obj;
	free(square);
	square = NULL;
}

static void	check_square(t_rt *cfg, t_square *square)
{
	if (!is_orientation_vect(&square->orient))
		parse_error(E_ORIENT, cfg);
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
	if (!(get_rgb(square->rgb, &line)))
		parse_error(E_BADRGB, cfg); 
	check_square(cfg, square);
	if (cfg->squares)
		ft_lstadd_back(&(cfg->squares), ft_lstnew(square));
	else
		cfg->squares = ft_lstnew(square);
}

void	compute_square_edges(t_square *square)
{
	t_vect n;
	t_vect p;
	
	n = *square->orient;
	p = *square->pos;
	if (is_zero(n.x) && is_zero(n.y))
		square->edge1 = (t_vect) {1, 1, 0};
	else if (is_zero(n.x) && is_zero(n.z))
		square->edge1 = (t_vect) {1, 0, 1};
	else if (is_zero(n.y) && is_zero(n.z))
		square->edge1 = (t_vect) {0, 1, 1};
	else if (is_zero(n.z))
	{
		square->edge1.x = 1;
		square->edge1.y = (dot(&n, &p) - n.x - n.z) / n.y;
		square->edge1.z = 1;
	}
	else
	{
		square->edge1.x = 1;
		square->edge1.y = 1;
		square->edge1.z = (dot(&n, &p) - n.x - n.y) / n.z;
	}
	cross(&n, square->edge1, square->edge2);
}

void	print_square(void *obj)
{
	t_square *square;

	square = (t_square *)obj;
	printf("Pos : ");
	print_vect(&square->pos);
	printf("Orientation : ");
	print_vect(&square->orient);
	printf("Height : %f\n", square->height);
	printf("RGB : %d,%d,%d\n", square->rgb[0], square->rgb[1],
	 		square->rgb[2]);
	printf("\n");
}
