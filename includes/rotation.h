/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/21 18:44:26 by darbib            #+#    #+#             */
/*   Updated: 2020/06/02 12:25:47 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ROTATION_H
# define ROTATION_H

# include "scene.h"
# include "vector.h"
# include "spheric.h"

void	rotate_scene(t_scene *scene, double phi, double theta);
void	rotate_planes(t_plane *planes, int n, double phi, double theta);
void	rotate_triangles(t_trig *triangles, int n, double phi, double theta);
void	extract_scene_rotation(t_vect *cam_orient, t_vect *ref_orient,
		double *phi, double *theta);
void	rotate_point(double phi, double theta, t_vect *v_in, t_vect *v_out);
#endif
