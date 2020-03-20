/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strlcpy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pqueiroz <pqueiroz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 15:45:39 by pqueiroz          #+#    #+#             */
/*   Updated: 2020/01/29 16:26:04 by pqueiroz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_extra_priv.h"

/*
** Copy up to len - 1 bytes from src to dest then null terminate it, return
** the length of str (unless len is 0, in which case nothing is done and 0 is
** returned).
*/

size_t
	strlcpy(char *dest, const char *src, size_t len)
{
	size_t	res;
	size_t	i;

	if (!dest)
		return (0);
	res = strlen(src);
	if (len == 0)
		return (res);
	i = 0;
	while (i < len - 1 && i < res)
	{
		dest[i] = src[i];
		++i;
	}
	dest[i] = 0;
	return (res);
}
