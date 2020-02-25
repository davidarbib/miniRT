/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 13:07:22 by darbib            #+#    #+#             */
/*   Updated: 2020/02/24 18:08:05 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
