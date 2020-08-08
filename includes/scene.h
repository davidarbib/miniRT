/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/15 14:31:09 by darbib            #+#    #+#             */
/*   Updated: 2020/08/08 18:54:02 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

# include "aabb.h"
# include "plane.h"
# include "square.h"
# include "triangle.h"
# include "cylinder.h"
# include "sphere.h"
# include "omnilight.h"
# include "camera.h"
# include "parsing.h"

enum	e_pixel			{i, j};
enum	e_bmpmode		{offline, online};

typedef struct			s_mlx
{
	int					bits_per_pixel;
	int					size_line;
	int					endian;
	int					sizex;
	int					sizey;
	void				*mlx_ptr;
	void				*win_ptr;
	void				*img_ptr;
	char				*img_data;
}						t_mlx;

typedef struct			s_scene
{
	t_vect				ambient_rgb;
	t_plane				*planes;
	t_square			*squares;
	t_trig				*triangles;
	t_cylinder			*cylinders;
	t_sphere			*spheres;
	t_olight			*olights;
	t_cam				*cams;
	t_cam				*active_cam;
	t_vect				ref_orient;
	int					lowres;
	int					planes_n;
	int					squares_n;
	int					triangles_n;
	int					cylinders_n;
	int					spheres_n;
	int					olights_n;
	int					cams_n;
	unsigned char		background_rgb[3];
	int					resx;
	int					resy;
	double				ambient_ratio;
	double				left_matrix[9];
	double				right_matrix[9];
	double				up_matrix[9];
	double				down_matrix[9];
	double				roll_matrix[9];
	double				invroll_matrix[9];
}						t_scene;

typedef struct			s_img
{
	int					sizex;
	int					sizey;
	int					size;
	int					sizeline;
	int					bpp;
	unsigned char		*buf;
}						t_img;

void					img_to_mlx(t_img *img, t_mlx *mlx);
int						init_graphics(t_mlx *mlx_cfg, t_rt *rt);
int						create_img(t_mlx *mlx_cfg);
int						refresh_img(t_mlx *mlx_cfg);
void					alter_pixel(t_mlx *cfg, int color, int x, int y);
void					apply_color(t_vect *pix_rgb, t_mlx *mlx_cfg, int x,
						int y);
void					init_img(t_img *img, t_rt *cfg, t_scene *scene);
int						client_endian(void);
int						adapt_endian(int color);
void					place_objs(t_scene *scene);
void					destroy_scene(t_scene *scene);
void					adapt_scene(t_scene *scene);
void					init_scene(t_scene *scene, t_rt *rt);
int						make_array(t_rt *rt, t_scene *scene);
void					move_scene(t_scene *scene, t_vect *translation);
void					move_planes(t_plane *planes, int n,
						t_vect *translation);
void					move_triangles(t_trig *triangles, int n,
						t_vect *translation);
void					move_spheres(t_sphere *spheres, int n,
						t_vect *translation);
void					move_squares(t_square *squares, int n,
						t_vect *translation);
void					move_cylinders(t_cylinder *cylinders, int n,
						t_vect *translation);
void					move_olights(t_olight *olights, int n,
						t_vect *translation);
int						set_cams(t_cam *cams, int n);
int						set_planes(t_plane *plane, int n);
int						set_triangles(t_trig *triangles, int n);
int						set_spheres(t_sphere *spheres, int n);
void					set_squares(t_square *squares, int n);
void					set_cylinders(t_cylinder *cylinders, int n);
void					set_olights(t_olight *olights, int n);
void					compute_triangles_edges(t_trig *triangles, int n);
void					set_squares_edges(t_square *squares, int n);
void					set_current_edges(t_square *squares, int n);
void					set_quadrics_radius(t_cylinder *cyls, int n,
						t_sphere *spheres, int k);
#endif
