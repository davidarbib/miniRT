/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 15:59:58 by darbib            #+#    #+#             */
/*   Updated: 2020/02/25 16:02:12 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CYLINDER_H
# define CYLINDER_H

/*
** --- cylinder ---
** pos : position vector
** ort : orientation vector [-1;1]
** diam : diameter
** height : ...
** rgb : rgb color
*/
typedef struct		s_cyld
{
	t_vect			*pos;
	t_vect			*ort;
	float			height;
	unsigned char	rgb[3];
}					t_cyld;

#endif
