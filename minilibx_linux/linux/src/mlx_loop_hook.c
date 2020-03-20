/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_loop_hook.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pqueiroz <pqueiroz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 01:16:37 ol                #+#    #+#             */
/*   Updated: 2020/01/29 01:16:39 by pqueiroz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_int.h"

int	mlx_loop_hook(t_xvar *xvar, int (*funct)(), void *param)
{
	xvar->loop_hook = funct;
	xvar->loop_param = param;
	return (0);
}
