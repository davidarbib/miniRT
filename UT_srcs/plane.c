/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 18:32:42 by darbib            #+#    #+#             */
/*   Updated: 2020/05/18 16:07:16 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "ft_printf.h"
#include <assert.h>
#include "plane.h"
#include "raytrace.h"

/*

void	destroy_plane(void *obj)
{
	t_plane *plane;
	
	plane = (t_plane *)obj;
	free(plane->pos);
	free(plane->orient);
	plane->pos = NULL;
	plane->orient = NULL;
	free(plane);
	plane = NULL;
}

static void	check_plane(t_rt *cfg, t_plane *plane)
{
	if (!(is_orientation_vect(plane->orient)))
		parse_error(E_ORIENT, cfg);
}

void	parse_plane(t_rt *cfg, char *line)
{
	t_plane	*plane;
	
	check_data(line, cfg);
	if (!(plane = (t_plane *)malloc(sizeof(t_plane))))
		sys_error(cfg);
	plane->pos = NULL;
	plane->orient = NULL;
	cfg->current_obj_addr = (void *)plane;
	line = ft_pass_spaces(line);
	if (!(plane->pos = get_vector(&line, cfg)))
		parse_error(E_BADVECT, cfg);
	line = ft_pass_spaces(line);
	if (!(plane->orient = get_vector(&line, cfg)))
		parse_error(E_BADVECT, cfg);
	line = ft_pass_spaces(line);
	if (!(get_rgb(plane->rgb, &line)))
		parse_error(E_BADRGB, cfg); 
	check_plane(cfg, plane);
	if (cfg->planes)
		ft_lstadd_back(&(cfg->planes), ft_lstnew(plane));
	else
		cfg->planes = ft_lstnew(plane);
}

void	print_plane(void *obj)
{
	t_plane *plane;
	
	plane = (t_plane *)obj;
	printf("Pos : %f, %f, %f\n", plane->pos->x, plane->pos->y,
	 	plane->pos->z);
	printf("Orientation : %f, %f, %f\n", plane->orient->x, plane->orient->y,
	 	plane->orient->z);
	printf("RGB : %d,%d,%d\n", plane->rgb[0], plane->rgb[1],
	 		plane->rgb[2]);
	printf("\n");
}
*/

int		intersect_plane(t_plane *plane, t_ray *ray)
{
	double	denom;
	double	t;
	t_vect	tmp_v; 

	denom = dot(ray->direction, plane->orient);	
	if (denom <= EPSILON)
		return (0);
	sub_vect(plane->pos, ray->origin, &tmp_v);
	t = dot(&tmp_v, plane->orient) / denom;
	return (t >= 0);
}

int main()
{
	t_plane plane;
	t_ray ray;

	plane.pos = malloc(sizeof(t_vect));
	plane.orient = malloc(sizeof(t_vect));
	ray.origin = malloc(sizeof(t_vect));
	ray.direction = malloc(sizeof(t_vect));
	
// ---- a parallel ray inside plane----
	plane.pos->x = 0;	
	plane.pos->y = 0;	
	plane.pos->z = 10;	
	plane.orient->x = 0;	
	plane.orient->y = 1;
	plane.orient->z = 0;	

	ray.origin->x = 0;	
	ray.origin->y = 0;	
	ray.origin->z = 0;	
	ray.direction->x = 0;	
	ray.direction->y = 0;	
	ray.direction->z = 1;	
	/*
	normalize(plane.pos, plane.pos);
	normalize(plane.orient, plane.orient);
	normalize(ray.origin, ray.origin);
	normalize(ray.direction, ray.direction);
	*/
	assert(!intersect_plane(&plane, &ray));

// ---- a parallel ray outside plane----
	plane.pos->x = 0;	
	plane.pos->y = 1;	
	plane.pos->z = 10;	
	plane.orient->x = 0;	
	plane.orient->y = 1;
	plane.orient->z = 0;	

	ray.origin->x = 0;	
	ray.origin->y = 2;	
	ray.origin->z = 0;	
	ray.direction->x = 0;	
	ray.direction->y = 0;	
	ray.direction->z = 1;	
	/*
	normalize(plane.pos, plane.pos);
	normalize(plane.orient, plane.orient);
	normalize(ray.origin, ray.origin);
	normalize(ray.direction, ray.direction);
	*/
	assert(!intersect_plane(&plane, &ray));

// --- a non parallel ray with inside plane origin ---
	plane.pos->x = 0;
	plane.pos->y = 1;
	plane.pos->z = 10;
	plane.orient->x = 0;
	plane.orient->y = 1;
	plane.orient->z = 0;

	ray.origin->x = 0;
	ray.origin->y = 1;
	ray.origin->z = 0;
	ray.direction->x = 0;
	ray.direction->y = -1;
	ray.direction->z = 1;
	/*
	normalize(plane.pos, plane.pos);
	normalize(plane.orient, plane.orient);
	normalize(ray.origin, ray.origin);
	normalize(ray.direction, ray.direction);
	*/
	assert(!intersect_plane(&plane, &ray));

// --- a non parallel ray with outside plane origin and plane in front
	plane.pos->x = 0;
	plane.pos->y = 1;
	plane.pos->z = 10;
	plane.orient->x = 0;
	plane.orient->y = 0;
	plane.orient->z = 1;

	ray.origin->x = 0;
	ray.origin->y = 0;
	ray.origin->z = 0;
	ray.direction->x = 0;
	ray.direction->y = -1;
	ray.direction->z = 1;
	/*
	normalize(plane.pos, plane.pos);
	normalize(plane.orient, plane.orient);
	normalize(ray.origin, ray.origin);
	normalize(ray.direction, ray.direction);
	*/
	assert(intersect_plane(&plane, &ray));

// --- a non parallel ray with outside plane origin and plane in back
	plane.pos->x = 0;
	plane.pos->y = 1;
	plane.pos->z = -10;
	plane.orient->x = 0;
	plane.orient->y = 0;
	plane.orient->z = 1;

	ray.origin->x = 0;
	ray.origin->y = 0;
	ray.origin->z = 0;
	ray.direction->x = 0;
	ray.direction->y = -1;
	ray.direction->z = 1;
	/*
	normalize(plane.pos, plane.pos);
	normalize(plane.orient, plane.orient);
	normalize(ray.origin, ray.origin);
	normalize(ray.direction, ray.direction);
	*/
	assert(!intersect_plane(&plane, &ray));

// --- a non parallel ray with outside plane origin and non axe-aligned plane in front
	plane.pos->x = 0;
	plane.pos->y = 0;
	plane.pos->z = 10;

	plane.orient->x = 0;
	plane.orient->y = 1;
	plane.orient->z = 1;

	ray.origin->x = 0;
	ray.origin->y = 0;
	ray.origin->z = 0;
	ray.direction->x = 0;
	ray.direction->y = 0;
	ray.direction->z = 1;
	/*
	normalize(plane.pos, plane.pos);
	normalize(plane.orient, plane.orient);
	normalize(ray.origin, ray.origin);
	normalize(ray.direction, ray.direction);
	*/
	assert(intersect_plane(&plane, &ray));

// --- a non parallel ray with outside plane origin and non axe-aligned plane in front
	plane.pos->x = 0;
	plane.pos->y = 0;
	plane.pos->z = 10;

	plane.orient->x = 0;
	plane.orient->y = 1;
	plane.orient->z = 1;

	ray.origin->x = -10;
	ray.origin->y = 0;
	ray.origin->z = 0;
	ray.direction->x = 0;
	ray.direction->y = 0;
	ray.direction->z = 1;
	/*
	normalize(plane.pos, plane.pos);
	normalize(plane.orient, plane.orient);
	normalize(ray.origin, ray.origin);
	normalize(ray.direction, ray.direction);
	*/
	assert(intersect_plane(&plane, &ray));
//
// --- a non parallel ray with outside plane origin and non axe-aligned plane in front
	plane.pos->x = 0;
	plane.pos->y = 0;
	plane.pos->z = 10;

	plane.orient->x = 0;
	plane.orient->y = 1;
	plane.orient->z = 1;

	ray.origin->x = 10;
	ray.origin->y = 0;
	ray.origin->z = 0;
	ray.direction->x = 0;
	ray.direction->y = 0;
	ray.direction->z = 1;
	/*
	normalize(plane.pos, plane.pos);
	normalize(plane.orient, plane.orient);
	normalize(ray.origin, ray.origin);
	normalize(ray.direction, ray.direction);
	*/
	assert(intersect_plane(&plane, &ray));
//
}
