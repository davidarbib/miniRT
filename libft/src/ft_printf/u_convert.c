/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_convert.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 16:59:36 by darbib            #+#    #+#             */
/*   Updated: 2020/01/21 17:00:15 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

/*
** zero-filling inhibition by dot presence
** dot presence => default precision 0
*/

static char	init_nb(t_conv *conv, va_list args, unsigned int *nb)
{
	if ((conv->flags & ZERO) && (conv->flags & DOT) && (conv->prec >= 0))
		conv->flags -= ZERO;
	if (conv->prec < 0)
		conv->prec = 1;
	*nb = va_arg(args, unsigned int);
	return (*nb < 0);
}

static void	prefield_one(t_buf *buf, t_conv *conv, size_t len)
{
	if (!(conv->flags & ZERO) && !(conv->flags & MINUS))
	{
		if (conv->prec > (signed int)len)
			len = conv->prec;
		if (conv->lmc > (signed int)len)
			fill_buffer(buf, conv->lmc - len, ' ');
	}
}

static void	prefield_two(t_buf *buf, t_conv *conv, size_t len)
{
	if (conv->flags & DOT && conv->prec > (signed int)len)
		fill_buffer(buf, conv->prec - len, '0');
	if (conv->flags & ZERO && conv->lmc > (signed int)len)
		fill_buffer(buf, conv->lmc - len, '0');
}

static char	radical(t_buf *buf, char **p_str)
{
	write_into(buf, p_str);
	check_full(buf);
	return (1);
}

int			u_convert(t_buf *buf, t_conv *conv, va_list args)
{
	char			*str;
	unsigned int	nb;
	size_t			len;

	init_nb(conv, args, &nb);
	if (!(str = ft_utoa(nb)))
		return (0);
	len = ft_strlen(str) - (nb == 0 && conv->flags & DOT && conv->prec == 0);
	prefield_one(buf, conv, len);
	prefield_two(buf, conv, len);
	if (!(nb == 0 && conv->flags & DOT && conv->prec == 0))
	{
		if (!radical(buf, &str))
			return (0);
	}
	if (conv->prec > (signed int)len)
		len = conv->prec;
	if (conv->flags & MINUS && conv->lmc > (signed int)len)
		fill_buffer(buf, conv->lmc - len, ' ');
	return (1);
}
