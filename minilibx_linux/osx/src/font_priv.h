/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   font_priv.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pqueiroz <pqueiroz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 12:53:49 by pqueiroz          #+#    #+#             */
/*   Updated: 2020/01/28 13:17:16 by pqueiroz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FONT_PRIV_H
# define FONT_PRIV_H

/*
** bytes_per_pixel: 2:RGB16, 3:RGB, 4:RGBA
*/

typedef struct		s_font_atlas
{
	unsigned int	width;
	unsigned int	height;
	unsigned int	bytes_per_pixel;
	unsigned char	pixel_data[1140 * 20 * 4 + 1];
}					t_font_atlas;

extern t_font_atlas	g_font_atlas;

#endif
