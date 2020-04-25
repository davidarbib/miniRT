#include "minirt.h"
#include "mlx.h"
#include "colors.h"

typedef struct	s_aabb
{
	t_vect			corner[2];
	unsigned char	rgb[3];
}				t_aabb;

typedef struct	s_scene
{
	t_vect			*pos_cam;
	t_aabb			*aabb;
	unsigned char	background_rgb[3]; 
	int				resx;
	int				resy;
}				t_scene;

typedef struct	s_ray
{
	t_vect			*origin;
	t_vect			*direction;
	t_vect			*inv_direction;
	int				sign[3];
}				t_ray;

static int		intersect_aabb(t_aabb *aabb, t_ray *ray)
{
	double tmin;
	double tmax;
	double tymin;
	double tymax;
	double tzmin;
	double tzmax;
	
	tmin = (aabb->corner[ray->sign[0]].x - ray->origin->x)
			* ray->inv_direction->x;
	tmax = (aabb->corner[1 - ray->sign[0]].x - ray->origin->x)
			* ray->inv_direction->x;
	tymin = (aabb->corner[ray->sign[1]].y - ray->origin->y)
			* ray->inv_direction->y;
	tymax = (aabb->corner[1 - ray->sign[1]].y - ray->origin->y)
			* ray->inv_direction->y;
	if ((tmin > tymax) || (tymin > tymax))
		return (0);
	if (tymin > tmin)
		tmin = tymin;
	if (tymax < tmax)
		tmax = tymax;
	tzmin = (aabb->corner[ray->sign[2]].z - ray->origin->z)
			* ray->inv_direction->z;
	tzmax = (aabb->corner[1 - ray->sign[2]].z - ray->origin->z)
			* ray->inv_direction->z;
	if ((tmin > tzmax) || (tzmin > tmax))
		return (0);
	if (tzmin > tmin)
		tmin = tzmin;
	if (tzmax < tmax)
		tmax = tzmax;
	return (tmax > 0);
}

void	init_scene(t_scene *scene)
{
	t_vect	pos_cam;

	scene->resx = 800;
	scene->resy = 600;

	scene->background_rgb[0] = 255; 
	scene->background_rgb[0] = 255; 
	scene->background_rgb[0] = 255; 
	
	pos_cam.x = 0;
	pos_cam.y = 0;
	pos_cam.z = 0;	
	scene->pos_cam = &pos_cam;

	scene->aabb = malloc(sizeof(t_aabb));

	scene->aabb->corner[0].x = scene->resx/-2;
	scene->aabb->corner[0].y = scene->resy/-2;
	scene->aabb->corner[0].z = 100; 
	scene->aabb->corner[1].x = scene->resx/2;
	scene->aabb->corner[1].y = scene->resy/2;
	scene->aabb->corner[1].z = 200; 

	scene->aabb->rgb[0] = 0; 
	scene->aabb->rgb[1] = 0; 
	scene->aabb->rgb[2] = 255; 
}

void	apply_color(unsigned char *rgb, t_mlx *mlx_cfg, int x, int y)
{
	unsigned char tmp_rgb[3];
	
	tmp_rgb[0] = rgb[2];
	tmp_rgb[1] = rgb[1];
	tmp_rgb[2] = rgb[0];
	alter_pixel(mlx_cfg, *((int *)&tmp_rgb), x, y);
}

void send_ray(t_scene *scene, t_mlx *mlx_cfg, int dx, int dy)
{
	t_ray	ray;
	t_vect	origin;
	t_vect	direction;
	t_vect	inv_direction;
	
	origin.x = scene->pos_cam->x;
	origin.y = scene->pos_cam->y;
	origin.z = scene->pos_cam->z;
	direction.x = scene->resx/-2 + dx;
	direction.y = scene->resy/-2 + dy;
	direction.z = 1;	
	inv_direction.x = 1 / direction.x;
	inv_direction.y = 1 / direction.y;
	inv_direction.z = 1 / direction.z;
	ray.origin = &origin;
	ray.direction = &direction;
	ray.inv_direction = &inv_direction;
	ray.sign[0] = (direction.x < 0);
	ray.sign[1] = (direction.y < 0);
	ray.sign[2] = (direction.z < 0);
	if (intersect_aabb(scene->aabb, &ray))
		//apply_color(scene->aabb->rgb, mlx_cfg, dx, dy);
		alter_pixel(mlx_cfg, RED, dx, dy);
	else
		//apply_color(scene->background_rgb, mlx_cfg, dx, dy);
		alter_pixel(mlx_cfg, BLUE, dx, dy);
}

void	raytrace(t_scene *scene, t_mlx *mlx_cfg)
{
	int dx;
	int dy;

	(void)scene;
/*
	dx = 0;
	while (dx < scene->resx)
	{
		dy = 0;
		while (dy < scene->resy)
		{
			//send_ray(scene, mlx_cfg, dx, dy);		
			alter_pixel(mlx_cfg, BLUE, dx, dy);
			dy++;
		}
		dx++;
	}
*/
	dx = 0;
	while (dx < 3)
	{
		if (dx % 2)
		{
			dx++;
			continue;
		}
		dy = 0;
		while (dy < 600)
		{
			//send_ray(scene, mlx_cfg, dx, dy);		
			alter_pixel(mlx_cfg, BLUE, dx, dy);
			//mlx_pixel_put(mlx_cfg->mlx_ptr, mlx_cfg->win_ptr, dx, dy, BLUE);
			dy++;
		}
		dx++;
	}
}

int main()
{
	t_scene scene;
	t_mlx	mlx_cfg;

	init_scene(&scene);	
	scene.resx = 800;
	scene.resy = 600;
	init_graphics(&mlx_cfg, scene.resx, scene.resy);
	raytrace(&scene, &mlx_cfg);
/*
	alter_pixel(&mlx_cfg, RED, 100, 302);
	alter_pixel(&mlx_cfg, GREEN, 20, 20);
	alter_pixel(&mlx_cfg, BLUE, 30, 30);
*/
	mlx_loop(mlx_cfg.mlx_ptr);
}
