/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/15 14:08:02 by darbib            #+#    #+#             */
/*   Updated: 2020/06/23 20:35:57 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYTRACE_H
# define RAYTRACE_H

# include "scene.h"
# include "graphic.h"
# include "aabb.h"
# include <math.h>

# define EPSILON	0.000001
# define PVEC		0
# define TVEC		1
# define QVEC		2
# define U			0
# define V			1
# define T			2

# define TYPE_NB	5

enum			e_var {t_ca, t_hc, d, t0, t1};
enum			e_type {plane, square, triangle, sphere, cylinder};

typedef struct	s_ray
{
	t_vect			origin;
	t_vect			direction;
	t_vect			inv_direction;
	int				sign[3];
	enum e_type		current_type;
}				t_ray;

typedef struct		s_near
{
	double			t;
	void			*obj;
	enum e_type		type;
	unsigned char 	rgb[3];
}					t_near;

void	get_obj_rgb(void *obj, enum e_type type, unsigned char *rgb);
void	raytrace(t_scene *scene, t_mlx *mlx_cfg);
double	intersect_plane(t_plane plane, t_ray ray);
double	intersect_triangle(t_trig triangle, t_ray ray);
double	intersect_sphere(t_sphere sphere, t_ray ray);
int		intersect_aabb(t_aabb *aabb, t_ray *ray);
void	loop_intersect_planes(t_plane *planes, int n, t_ray *ray,
		t_near *near);
void	loop_intersect_triangles(t_trig *triangles, int n, t_ray *ray,
		t_near *near);
#endif
