/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/20 13:49:53 by darbib            #+#    #+#             */
/*   Updated: 2020/07/01 18:48:01 by darbib           ###   ########.fr       */
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

void	vect_cpy(t_vect *v_in, t_vect *v_out)
{
	v_out->x = v_in->x;
	v_out->y = v_in->y;
	v_out->z = v_in->z;
}

int		same_vect(t_vect *v1, t_vect *v2) 
{
	t_vect tmp_v1;
	t_vect tmp_v2;

	scale(10000, v1, &tmp_v1);
	scale(10000, v2, &tmp_v2);
	if ((int)tmp_v1.x == (int)tmp_v2.x
		&& (int)tmp_v1.y == (int)tmp_v2.y
		&& (int)tmp_v1.z == (int)tmp_v2.z)
		return (1);
	return (0);
}

int		opposite_vect(t_vect *v1, t_vect *v2) 
{
	t_vect v1_opposite;
	
	scale(-1., v1, &v1_opposite);
	if (same_vect(&v1_opposite, v2))
		return (1);
	return (0);
}

int		is_null_vect(t_vect v)
{	
	if (is_zero(v.x) && is_zero(v.y) && is_zero(v.z))
		return (1);
	return (0);
}
