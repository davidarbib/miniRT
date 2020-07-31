/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   square.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 18:36:28 by darbib            #+#    #+#             */
/*   Updated: 2020/07/31 17:15:13 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "square.h"
#include "error.h"
#include "print.h"

void	destroy_square(void *obj)
{
	t_square *square;
	
	square = (t_square *)obj;
	free(square);
	square = NULL;
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
	if (!is_orientation_vect(&square->orient))
		parse_error(E_ORIENT, cfg);
	if (is_null_vect(square->orient))
		parse_error(E_NULLV, cfg);
	if (cfg->squares)
		ft_lstadd_back(&(cfg->squares), ft_lstnew(square));
	else
		cfg->squares = ft_lstnew(square);
}

void	compute_square_points(t_square *square)
{
	add_vect(&square->pos, &square->edge1, &square->pt1); 
	add_vect(&square->pt1, &square->edge2, &square->pt2); 
	add_vect(&square->pos, &square->edge2, &square->pt3); 
	//sub_vect(&square->pt1, &square->pos, &square->edge1); 
	//sub_vect(&square->pt3, &square->pos, &square->edge2); 
}

void	compute_current_edges(t_square *square)
{
	sub_vect(&square->current_pt1, &square->current_pos,
			&square->current_edge1); 
	sub_vect(&square->current_pt3, &square->current_pos,
			&square->current_edge2); 
}

void	compute_square_edges(t_square *square)
{
	t_vect n;
	t_vect p;
	
	n = square->orient;
	p = square->pos;
	if (is_zero(n.x) && is_zero(n.y))
		square->edge1 = (t_vect) {p.x + 1, p.y + 1, p.z};
	else if (is_zero(n.x) && is_zero(n.z))
		square->edge1 = (t_vect) {p.x + 1, p.y, p.z + 1};
	else if (is_zero(n.y) && is_zero(n.z))
		square->edge1 = (t_vect) {p.x, p.y + 1, p.z + 1};
	else if (is_zero(n.z))
	{
		square->edge1.x = p.x + 1;
		square->edge1.y = (n.x * (p.x + 1) + n.z * (p.z + 1) - dot(&n, &p)) 
											/ -n.y;
		square->edge1.z = p.z + 1;
	}
	else
	{
		square->edge1.x = p.x + 1;
		square->edge1.y = p.y + 1;
		square->edge1.z = (n.x * (p.x + 1) + n.y * (p.y + 1) - dot(&n, &p)) 
											/ -n.z;
	}
	sub_vect(&square->edge1, &p, &square->edge1); 
	cross(&n, &square->edge1, &square->edge2);
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
	printf("RGB : %d,%d,%d\n", square->rgb[0], square->rgb[1], square->rgb[2]);
	printf("\n");
}
