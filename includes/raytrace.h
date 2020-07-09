/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/15 14:08:02 by darbib            #+#    #+#             */
/*   Updated: 2020/07/09 14:32:56 by darbib           ###   ########.fr       */
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

enum			e_var_sphere {t_ca, t_hc, d, t0, t1};
enum			e_var_cylinder {dc, len_rxa, s, tc, t1c, t2c};
enum			e_type {plane, square, triangle, sphere, cylinder};
enum			e_colorchan {r, g, b};

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
	double			rgb_ratio[3];
	t_vect			hit;
	t_vect			normal;
	void			*obj;
	enum e_type		type;
	unsigned char 	rgb[3];
	
}					t_near;

void	get_obj_rgb(void *obj, enum e_type type, unsigned char *rgb);
void	get_hit_point(double t, t_vect direction, t_vect origin, t_vect *v_out);
void	get_hit_plane(t_near *near, t_ray ray);
void	get_hit_triangle(t_near *near, t_ray ray);
void	get_hit_square(t_near *near, t_ray ray);
void	get_hit_sphere(t_near *near, t_ray ray);
void	get_hit_cylinder(t_near *near, t_ray ray);
void	raytrace(t_scene *scene, t_mlx *mlx_cfg);
void	browse_scene(t_scene *scene, t_ray *ray, t_near *near);
double	intersect_plane(t_plane plane, t_ray ray);
double	intersect_triangle(t_trig triangle, t_ray ray);
double	intersect_sphere(t_sphere sphere, t_ray ray);
double	intersect_square(t_square square, t_ray ray);
double	intersect_cylinder(t_cylinder cylinder, t_ray ray);
int		intersect_aabb(t_aabb *aabb, t_ray *ray);
void	loop_intersect_planes(t_plane *planes, int n, t_ray *ray,
		t_near *near);
void	loop_intersect_triangles(t_trig *triangles, int n, t_ray *ray,
		t_near *near);
void	loop_intersect_spheres(t_sphere *spheres, int n, t_ray *ray,
		t_near *near);
void	loop_intersect_squares(t_square *squares, int n, t_ray *ray,
		t_near *near);
void	loop_intersect_cylinders(t_cylinder *cylinders, int n, t_ray *ray,
		t_near *near);
#endif
