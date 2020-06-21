/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/13 15:54:56 by darbib            #+#    #+#             */
/*   Updated: 2020/06/21 16:44:37 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "libft.h"
#include "error.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

extern void	(*g_parse_ft[NB_OBJS])(t_rt *cfg, char *p_line);

int		label_chr(char **tab, char *label)
{
	int i;

	i = 0;
	while (tab[i] && ft_strcmp(tab[i], label))
		i++;
	if (!tab[i])
		return (-1);
	return (i);
}

static void dispatch(t_rt *cfg, char *p_line)
{
	int idx;

	cpy_next_word(&p_line, cfg->buf);
	if ((idx = label_chr(cfg->labels_tab, cfg->buf)) < 0)
		parse_error(E_BADOBJ, cfg);	
	cfg->current_obj_type = idx;
	cfg->current_obj_addr = NULL;
	g_parse_ft[idx](cfg, p_line);
}

void		handle_line(t_rt *cfg)
{
	char *p_line;

	cfg->linenb++;
	p_line = ft_pass_spaces(cfg->line);
	if (!*p_line)
	{
		free(cfg->line);
		return ;
	}
	dispatch(cfg, p_line);
	free(cfg->line);
}
