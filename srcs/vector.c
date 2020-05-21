/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/20 13:49:53 by darbib            #+#    #+#             */
/*   Updated: 2020/05/21 14:18:13 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"
#include "libft.h"

t_vect	*vect_dup(t_vect *v_in)
{
	t_vect *v_out;

	if (!(v_out = (t_vect *)ft_calloc(1, sizeof(t_vect))))
		return (NULL);
	v_out->x = v_in->x;
	v_out->y = v_in->y;
	v_out->z = v_in->z;
	return (v_out);
}
