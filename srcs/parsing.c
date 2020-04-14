/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 23:25:41 by darbib            #+#    #+#             */
/*   Updated: 2020/04/13 16:14:46 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"
#include "minirt.h"
#include "error.h"
#include <stdio.h>

void	(*g_parse_ft[NB_OBJS])(t_rt *cfg, char *p_line);

static void assign_fts(void)
{
	g_parse_ft[0] = parse_res;  
	g_parse_ft[1] = parse_amb;  
	g_parse_ft[2] = parse_camera;  
	g_parse_ft[3] = parse_olight;  
	g_parse_ft[4] = parse_plane;  
	g_parse_ft[5] = parse_sphere;  
	g_parse_ft[6] = parse_square;  
	g_parse_ft[7] = parse_cylinder;  
	g_parse_ft[8] = parse_triangle;  
}

static int	arg_control(int ac, char **av, t_rt *cfg)
{
	char	*p_av;
	int		fd;

	if (ac == 1)
		parse_error(E_ARGFILE, cfg);
	if (ac == 3)
	{
		if (ft_strcmp(av[2], SAVEARG))
			parse_error(E_SCNDARG, cfg);
		else
			cfg->flags |= SAVE_REQUESTED;
	}
	p_av = av[1] + ft_strlen(av[1]) - ft_strlen(FILEEXT);
	if (ft_strcmp(p_av, FILEEXT))
		parse_error(E_BADEXT, cfg);
	if (((fd = open(av[1], O_RDONLY)) < 0))
		sys_error(cfg);
	return (fd);
}

static void	check_mandatory_params(t_rt *cfg)
{
	if (!(cfg->flags & RES))
		parse_error(E_NORES, cfg);
	if (!(cfg->flags & AMB))
		parse_error(E_NOAMB, cfg);
	if (!(cfg->flags & CAM))
		parse_error(E_NOCAM, cfg);
}

void		parsing(int ac, char **av, t_rt *cfg)
{
	int		gnl;
	int		fd;

	fd = arg_control(ac, av, cfg);
	if (!(cfg->labels_tab = ft_split(OBJS, SEP)))
		sys_error(cfg);
	assign_fts();
	cfg->flags |= IN_PARSING;
	while ((gnl = get_next_line(fd, &cfg->line)) > 0)
		handle_line(cfg);
	free(cfg->line);
	cfg->flags -= IN_PARSING;
	if (gnl < 0)
		parse_error(E_INVFILE, cfg);
	check_mandatory_params(cfg);
}
