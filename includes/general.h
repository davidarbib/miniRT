/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 17:27:22 by darbib            #+#    #+#             */
/*   Updated: 2020/08/06 22:08:14 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GENERAL_H
# define GENERAL_H

# include "vector.h"
# include "spheric.h"
# include "parsing.h"
# include "scene.h"

/*
** ---------------
*/

typedef struct	s_param
{
	t_mlx		*mlx_cfg;
	t_scene		*scene;
	t_img		*img;
}				t_param;

# define TITLE		"Fantaisie mathematique"
# define SAVEARG	"-save"
# define FILEEXT	".rt"

/*
** ---------------
*/

# define OBJS		"R,A,c,l,pl,sp,sq,cy,tr"
# define SEP		','
# define NB_OBJS	9

/*
** -------------------------------------
*/

int				label_chr(char **tab, char *label);

void			cpy_next_word(char **s, char *buf);

void			data_visu(t_rt *cfg);
void			destroy_cfg(t_rt *cfg);

void			to_cartesian(t_spheric *spherical, t_vect *cartesian);
#endif
