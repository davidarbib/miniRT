/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 15:54:04 by darbib            #+#    #+#             */
/*   Updated: 2020/03/09 15:01:46 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TRIANGLE_H
# define TRIANGLE_H

# include "vector.h"

/*
** --- triangle ---
** pt1 : 1st point
** pt2 : 2nd point
** pt3 : 3nd point
** rgb : rgb color
** (mb 2 vector only are needed)
*/

typedef struct		s_trig
{
	t_vect			*pt1;
	t_vect			*pt2;
	t_vect			*pt3;
	unsigned char	rgb[3];
}					t_trig;

void	destroy_triangle(void *obj);
int		parse_triangle(t_rt *cfg, char *line);

#endif
