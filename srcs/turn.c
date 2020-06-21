/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   turn.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/08 22:39:51 by darbib            #+#    #+#             */
/*   Updated: 2020/06/22 00:04:24 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "actions.h"
#include "update.h"
#include "print.h"
#include "general.h"
#include "rotation.h"
#include "matrix.h"

void			print_matrix(double *m)
{
	int i;
	int j;
	
	j = 0;
	while (j < DN)
	{
		i = 0;
		while (i < DN)
		{
			printf("%lf ", m[i + DN * j]);
			i++;
		}
		j++;
		printf("\n");
	}
}

void	turn_cam(t_param *param, double *matrix)
{
	t_vect *current_orient;

	//------------------
	t_vect v_test = (t_vect){1., 0., 0.};
	t_vect res;
	print_vect(&v_test);
	printf("---------matrix--------\n");
	print_matrix(matrix);
	printf("-----------------------\n");
	rotate_point(matrix, &v_test, &res);
	print_vect(&res);
	//------------------
	current_orient = &param->scene->active_cam->current_orient;
	//------------------
	printf("same : %d\n", same_vect(&v_test, current_orient));
	//------------------
	normalize(current_orient, current_orient);
	//------------------
	printf("orientation camera in turn_cam after normalize :\n");
	print_vect(current_orient);
	printf("------\n");
	printf("orientation camera before rotation :\n");
	print_vect(current_orient);
	printf("------\n");
	//------------------
	printf("---------matrix--------\n");
	print_matrix(matrix);
	printf("-----------------------\n");
	rotate_point(matrix, current_orient, current_orient); 
	printf("orientation camera after rotation :\n");
	print_vect(current_orient);
	printf("------\n");
}

void	turn_left(void *param)
{
	t_param	*pm;

	pm = (t_param *)param;
	printf("orientation camera in turn_left :\n");
	print_vect(&pm->scene->active_cam->current_orient);
	printf("------\n");
	turn_cam(pm, pm->scene->left_matrix);
	rotate_scene(pm->scene, pm->scene->right_matrix);
	if (!(update_display(pm->scene, pm->mlx_cfg)))
		return ;
}

void	turn_right(void *param)
{
	t_param	*pm;

	pm = (t_param *)param;
	turn_cam(pm, pm->scene->right_matrix);
	rotate_scene(pm->scene, pm->scene->left_matrix);
	if (!(update_display(pm->scene, pm->mlx_cfg)))
		return ;
}

void	turn_up(void *param)
{
	t_param	*pm;

	pm = (t_param *)param;
	turn_cam(pm, pm->scene->up_matrix);
	rotate_scene(pm->scene, pm->scene->down_matrix);
	if (!(update_display(pm->scene, pm->mlx_cfg)))
		return ;
}

void	turn_down(void *param)
{
	t_param	*pm;

	pm = (t_param *)param;
	turn_cam(pm, pm->scene->down_matrix);
	rotate_scene(pm->scene, pm->scene->up_matrix);
	if (!(update_display(pm->scene, pm->mlx_cfg)))
		return ;
}
