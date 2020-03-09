/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 23:25:41 by darbib            #+#    #+#             */
/*   Updated: 2020/03/09 18:15:47 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"
#include "minirt.h"
#include "rt_errors.h"
#include <stdio.h>

void	(*g_parse_ft[NB_OBJS])(t_rt *cfg, char *p_line);

static void assign_fts(void)
{
	g_parse_ft[0] = parse_res;  
	g_parse_ft[1] = parse_amb;  
	g_parse_ft[2] = parse_cam;  
	g_parse_ft[3] = parse_light;  
	g_parse_ft[4] = parse_plane;  
	g_parse_ft[5] = parse_sphere;  
	g_parse_ft[6] = parse_square;  
	g_parse_ft[7] = parse_cyld;  
	g_parse_ft[8] = parse_trig;  
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
			cfg->save = 1;
	}
	p_av = av[1] + ft_strlen(av[1]) - ft_strlen(FILEEXT);
	if (ft_strcmp(p_av, FILEEXT))
		parse_error(E_BADEXT, cfg);
	if (((fd = open(av[1], O_RDONLY)) < 0))
		sys_error(cfg);
	return (fd);
}

static void	handle_empty(char *line, t_rt *cfg)
{
	static int	nb_empty;

	printf("empty line\n");
	free(line);
	if (cfg->data)
		return ;
	if (nb_empty++ > MAXNBLHEAD)
		parse_error(E_INVFILE, cfg);
	nb_empty++;
}


static void dispatch(t_rt *cfg, char *p_line)
{
	int idx;

	cpy_next_word(&p_line, cfg->buf);
	if ((idx = label_chr(cfg->labels_tab, cfg->buf)) < 0)
		parse_error(E_BADOBJ, cfg);	
	cfg->data = 1;
	printf("idx : %d\n", idx);
	g_parse_ft[idx](cfg, p_line);
}

void		parsing(int ac, char **av, t_rt *cfg)
{
	char	*line;
	char	*p_line;
	int		gnl;
	int		fd;

	fd = arg_control(ac, av, cfg);
	if (!(cfg->labels_tab = ft_split(OBJS, SEP)))
		sys_error(cfg);
	assign_fts();
	while ((gnl = get_next_line(fd, &line)) > 0)
	{
		cfg->linenb++;
		if (!(p_line = ft_pass_spaces(line)))
		{
			handle_empty(line, cfg);
			continue;
		}
		dispatch(cfg, p_line);
	}
}
