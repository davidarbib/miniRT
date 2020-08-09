/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 18:58:54 by darbib            #+#    #+#             */
/*   Updated: 2020/08/09 17:35:23 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "actions.h"
#include "mlx.h"

void	normal_exit(void *param)
{
	t_mlx	*mlx;

	mlx = ((t_param *)param)->mlx_cfg;
	destroy_scene(((t_param *)param)->scene);
	mlx_destroy_window(mlx->mlx_ptr, mlx->win_ptr);
	mlx_destroy_image(mlx->mlx_ptr, mlx->img_ptr);
	exit(EXIT_SUCCESS);
}

int		normal_exit2(void *param)
{
	t_mlx *mlx;

	mlx = ((t_param *)param)->mlx_cfg;
	destroy_scene(((t_param *)param)->scene);
	mlx_destroy_window(mlx->mlx_ptr, mlx->win_ptr);
	mlx_destroy_image(mlx->mlx_ptr, mlx->img_ptr);
	exit(EXIT_SUCCESS);
}

void	bmp_exit(void *param)
{
	destroy_scene(((t_param *)param)->scene);
	free(((t_param *)param)->img->buf);
	exit(EXIT_SUCCESS);
}
