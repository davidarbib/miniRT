/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_rotation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/21 18:08:31 by darbib            #+#    #+#             */
/*   Updated: 2020/05/21 19:12:44 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rotation.h"
#include "print.h"

void	rotate_planes(t_plane *planes, int n, double phi, double theta)
{
	t_plane *plane;

	while (n)
	{
		plane = planes + n - 1;
		rotate_point(phi, theta, plane->current_pos, plane->current_pos);
		rotate_point(phi, theta, plane->current_orient, plane->current_orient);
		n--;
	}
}

int main()
{
	double phi = 42;
	double theta = 95;
	phi = to_radian(phi);
	theta = to_radian(theta);
	t_plane *plane = malloc(sizeof(t_plane));
	t_vect *pos = malloc(sizeof(t_vect));
	t_vect *orient = malloc(sizeof(t_vect));
	t_vect *ref_pos = malloc(sizeof(t_vect));
	t_vect *ref_orient = malloc(sizeof(t_vect));
	pos->x = 2;	
	pos->y = 7;	
	pos->z = 3;	
	orient->x = 0;
	orient->y = 0;
	orient->z = 0;
	ref_pos->x = 2;	
	ref_pos->y = 7;	
	ref_pos->z = 3;	
	ref_orient->x = 0;
	ref_orient->y = 0;
	ref_orient->z = 0;
	plane->current_pos = pos;
	plane->current_orient = orient;
	print_vect(plane->current_pos);
	print_vect(plane->current_orient);
	print_angle(phi, theta);
	printf("--------------------------\n");
	rotate_planes(plane, 1, phi, theta);	
	extract_scene_rotation(plane->current_orient, ref_orient, &phi, &theta);
	print_angle(phi, theta);
	extract_scene_rotation(plane->current_pos, ref_pos, &phi, &theta);
	print_angle(phi, theta);
}
