/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/13 15:54:56 by darbib            #+#    #+#             */
/*   Updated: 2020/08/04 18:35:47 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "libft.h"
#include "error.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

extern void	(*g_parse_ft[NB_OBJS])(t_rt *cfg, char *p_line);

int			label_chr(char **tab, char *label)
{
	int i;

	i = 0;
	while (tab[i] && ft_strcmp(tab[i], label))
		i++;
	if (!tab[i])
		return (-1);
	return (i);
}

static void	dispatch(t_rt *cfg, char *p_line)
{
	int idx;

	cpy_next_word(&p_line, cfg->buf);
	if ((idx = label_chr(cfg->labels_tab, cfg->buf)) < 0)
		parse_error(E_BADOBJ, cfg);
	printf("cfg buf : --%s--\n", cfg->buf);
	printf("idx : --%d--\n", idx);
	g_parse_ft[idx](cfg, p_line);
	cfg->current_obj_type = idx;
}

void		clean_line(char *line)
{
	while (*line)
	{
		if (!(ft_isprint(*line)) && !(ft_isblank(*line)))
			*line = ' ';
		line++;
	}
}

void		handle_line(t_rt *cfg)
{
	char *p_line;
	char *clean_line;

	cfg->current_obj_addr = NULL;
	if (!(clean_line = ft_strdelchar(cfg->line, (char)0x01)))
		sys_error(cfg);
	free(cfg->line);
	cfg->line = clean_line;
	cfg->linenb++;
	p_line = ft_pass_spaces(clean_line);
	if (!*p_line)
	{
		free(clean_line);
		return ;
	}
	dispatch(cfg, p_line);
	free(clean_line);
}
