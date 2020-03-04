/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_mv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 13:42:34 by darbib            #+#    #+#             */
/*   Updated: 2020/03/04 17:57:05 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_atoi_mv(const char **str)
{
	long long	nb;
	signed char	sign;

	nb = 0;
	sign = 1;
	while (**str && ft_isblank(**str))
		(*str)++;
	if ((**str == '+' || **str == '-') && ft_isdigit(*(*str + 1)))
	{
		if (**str == '-')
			sign = -1;
		(*str)++;
	}
	while (**str && ft_isdigit(**str))
		nb = nb * 10 + *(*str)++ - '0';
	(*str)--;
	return (sign * nb);
}
