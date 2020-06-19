/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/20 13:49:53 by darbib            #+#    #+#             */
/*   Updated: 2020/06/19 14:07:25 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"
#include "libft.h"
#include "print.h"

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
	if (v1->x == v2->x
		&& v1->y == v2->y
		&& v1->z == v2->z)
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

int		main()
{
	t_vect v1 = (t_vect){1, 0, 0};
	t_vect v2 = (t_vect){0, 0, 0};
	
	printf("same : %d\n", same_vect(&v1, &v2));
	printf("opposite : %d\n", opposite_vect(&v1, &v2));
}
