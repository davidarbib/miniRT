/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_rgb_priv.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pqueiroz <pqueiroz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 17:40:20 by pqueiroz          #+#    #+#             */
/*   Updated: 2020/01/28 19:23:40 by pqueiroz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MLX_RGB_PRIV_H
# define MLX_RGB_PRIV_H

typedef struct		s_col_name
{
	char			*name;
	int				color;
}					t_col_name;

typedef struct		s_xpm_col
{
	int				name;
	int				col;
}					t_xpm_col;

extern t_col_name	g_mlx_col_name[];

#endif
