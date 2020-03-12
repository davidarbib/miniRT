/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 16:03:02 by darbib            #+#    #+#             */
/*   Updated: 2020/03/10 11:51:53 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLANE_H
# define PLANE_H

# include "vector.h"
/*
** --- plane ---
** pos : position vector
** ort : orientation vector [-1;1]
** rgb : rgb color
*/

typedef struct		s_plane
{
	t_vect			*pos;
	t_vect			*ort;
	unsigned char	rgb[3];
}					t_plane;

void	destroy_plane(void *obj);
void	parse_plane(t_rt *cfg, char *line);
void	print_plane(void *obj);

#endif
