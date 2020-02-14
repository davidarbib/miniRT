/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   endian.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 16:22:28 by darbib            #+#    #+#             */
/*   Updated: 2020/02/14 16:22:41 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int				client_endian(void)
{
	unsigned int nb;

	nb = 0x1;
	if (((unsigned char *)&nb)[0] == 0x1)
		return (0);
	return (1);
}

unsigned int	adapt_endian(unsigned int color)
{
	unsigned int tmp;
	
	tmp = color;
	((unsigned char *)&color)[0] = ((unsigned char *)&tmp)[3];
	((unsigned char *)&color)[1] = ((unsigned char *)&tmp)[2];
	((unsigned char *)&color)[2] = ((unsigned char *)&tmp)[1];
	((unsigned char *)&color)[3] = ((unsigned char *)&tmp)[0];
	return (color);
}
