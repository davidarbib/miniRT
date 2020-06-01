/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_triangles_edges.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/01 19:10:45 by darbib            #+#    #+#             */
/*   Updated: 2020/06/01 22:46:15 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "print.h"
#include "triangle.h"

void	compute_triangles_edges(t_trig *triangles, int n)
{
	while (--n >= 0)
	{
		sub_vect(&triangles[n].current_pt1, &triangles[n].current_pt2,
				&triangles[n].current_edge1);
		sub_vect(&triangles[n].current_pt1, &triangles[n].current_pt3,
				&triangles[n].current_edge2);
	}
}

int main()
{
	t_trig triangles[2];
	
	triangles[0].current_pt1.x = 4;
	triangles[0].current_pt1.y = 4;
	triangles[0].current_pt1.z = 4;
	triangles[0].current_pt2.x = 1;
	triangles[0].current_pt2.y = 1;
	triangles[0].current_pt2.z = 1;
	triangles[0].current_pt3.x = -6;
	triangles[0].current_pt3.y = -6;
	triangles[0].current_pt3.z = -6;
	triangles[1].current_pt1.x = 10;
	triangles[1].current_pt1.y = 10;
	triangles[1].current_pt1.z = 10;
	triangles[1].current_pt2.x = 7;
	triangles[1].current_pt2.y = 7;
	triangles[1].current_pt2.z = 7;
	triangles[1].current_pt3.x = 9;
	triangles[1].current_pt3.y = 9;
	triangles[1].current_pt3.z = 9;
	printf("before edges \n");
	for (int i = 0; i < 2;i++)
	{	
		print_vect(&triangles[i].current_pt1);
		print_vect(&triangles[i].current_pt2);
		print_vect(&triangles[i].current_pt3);
	}
	compute_triangles_edges(triangles, 2);
	printf("----------------\n");
	printf("after edges \n");
	for (int i = 0; i < 2;i++)
	{	
		print_vect(&triangles[i].current_pt1);
		print_vect(&triangles[i].current_pt2);
		print_vect(&triangles[i].current_pt3);
		print_vect(&triangles[i].current_edge1);
		print_vect(&triangles[i].current_edge2);
	}
}
