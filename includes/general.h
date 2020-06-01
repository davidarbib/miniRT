/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 17:27:22 by darbib            #+#    #+#             */
/*   Updated: 2020/05/30 20:53:58 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GENERAL_H
# define GENERAL_H

# include "libft.h"
# include "vector.h"
# include "spheric.h"
# include "parsing.h"

/*
** ---------------
*/

# define TITLE		"RT scene"
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

int				client_endian(void);
unsigned int	adapt_endian(unsigned int color);

int				label_chr(char **tab, char *label);

void			cpy_next_word(char **s, char *buf);

void			data_visu(t_rt *cfg);
void			destroy_cfg(t_rt *cfg);

void			to_cartesian(t_spheric *spherical, t_vect *cartesian);
#endif
