/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/21 18:44:26 by darbib            #+#    #+#             */
/*   Updated: 2020/07/04 22:08:04 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ROTATION_H
# define ROTATION_H

# include "scene.h"
# include "vector.h"
# include "spheric.h"

double	to_radian(double degree);
double	to_degree(double radian);
void	assign_turn_matrices(double *left, double *right);
void	assign_turn_matrices2(double *up, double *down);
void	to_spherical(t_vect *cartesian, t_spheric *spherical);
void	rotate_scene(t_scene *scene, double *matrix);
void	rotate_planes(t_plane *planes, int n, double *matrix);
void	rotate_triangles(t_trig *triangles, int n, double *matrix);
void	rotate_spheres(t_sphere *spheres, int n, double *matrix);
void	rotate_squares(t_square *squares, int n, double *matrix);
void	rotate_cylinders(t_cylinder *cylinders, int n, double *matrix);
void	extract_scene_rotation(t_vect *cam_orient, t_vect *ref_orient,
		double *rot_matrix);
void	rotate_point(double *matrix, t_vect *v_in, t_vect *v_out);
void	rot_from_anti_ref_orient(double *m);
#endif
