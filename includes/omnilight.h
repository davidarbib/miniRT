/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   omnilight.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 16:26:46 by darbib            #+#    #+#             */
/*   Updated: 2020/02/25 17:31:20 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OMNILIGHT_H
# define OMNILIGHT_H

/*
** --- omnilight ---
** pos : position vector
** ratio : luminance ratio [0.0;1.0]
** rgb : rgb color
*/
typedef struct		s_olight
{
	t_vect			*pos;
	float			ratio;
	unsigned char	rgb[3];
}					t_olight;

#endif
