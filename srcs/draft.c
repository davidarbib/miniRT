#include "minirt.h"
#include "mlx.h"
#include "colors.h"
#include "aabb.h"

typedef struct	s_scene
{
	t_vect			*pos_cam;
	t_aabb			*aabb;
	t_sphere		*sphere;
	unsigned char	background_rgb[3]; 
	int				resx;
	int				resy;
}				t_scene;

/*
void	set_quaternion(t_vect *cam_orient, t_vect *ref_orient, double *quater)
{
	//ramener veceur sur xz	
		//projection sur xz
	
		//calcul angle de la rotation z
		//construction 1er quaternion
	//ramener sur reference
		//projection sur la reference
		//calcul angle de la rotation y
		//construction 2e quaternion
	//multiplication de quaternions
}
*/
void	init_scene(t_scene *scene, int posaabbx, int posaabby, int posaabbz)
{
	t_vect		pos_cam;

	scene->resx = 800;
	scene->resy = 600;

	scene->background_rgb[0] = 0xd6; 
	scene->background_rgb[1] = 0xd9; 
	scene->background_rgb[2] = 0xce; 
	
	pos_cam.x = 0;
	pos_cam.y = 0;
	pos_cam.z = 0;	
	scene->pos_cam = &pos_cam;
	scene->aabb = malloc(sizeof(t_aabb));

	scene->aabb->corner[0].x = posaabbx + 0;
	scene->aabb->corner[0].y = posaabby + 0;
	scene->aabb->corner[0].z = posaabbz + 0; 
	scene->aabb->corner[1].x = posaabbx + 100;
	scene->aabb->corner[1].y = posaabby + 100;
	scene->aabb->corner[1].z = posaabbz + 100; 

	scene->aabb->rgb[0] = 0x71; 
	scene->aabb->rgb[1] = 0xa9; 
	scene->aabb->rgb[2] = 0xf7; 
/*
	scene->sphere = &sphere;
	sphere.pos = &pos; 
	pos.x = posaabbx;
	pos.y = posaabby;
	pos.z = posaabbz;
	sphere.diam = diam;
	sphere.rgb[0] = 255;
	sphere.rgb[1] = 255;
	sphere.rgb[2] = 255;	
*/
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
	direction.z = 150;	
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
		apply_color(scene->aabb->rgb, mlx_cfg, dx, dy);
	else
		apply_color(scene->background_rgb, mlx_cfg, dx, dy);
}

void	raytrace(t_scene *scene, t_mlx *mlx_cfg)
{
	int dx;
	int dy;

	dx = 0;
	while (dx < scene->resx)
	{
		dy = 0;
		while (dy < scene->resy)
		{
			send_ray(scene, mlx_cfg, dx, dy);	
			dy++;
		}
		dx++;
	}
}

int main(int ac, char **av)
{
	t_vect v1;
	t_vect v2;
	t_vect v_out;
	//double scalar;

	(void)ac;
	(void)av;
	v1.x = 2;
	v1.y = 7;
	v1.z = -1;
	v2.x = -9;
	v2.y = 1;
	v2.z = 5;
	//scale(scalar, &v1, &v_out);
	cross(&v1, &v2, &v_out);
	printf("v1 ^ v2= (%f, %f, %f)\n", v_out.x, v_out.y, v_out.z);
	printf("v1 . v2= %f\n", dot(&v1, &v2));
	printf("||v1|| = %f\n", vect_norm(&v1));
	normalize(&v1, &v_out);
	printf("normalize(v1)= (%f, %f, %f)\n", v_out.x, v_out.y, v_out.z);
	add_vect(&v1, &v2, &v_out);
	printf("v1 + v2 = (%f, %f, %f)\n", v_out.x, v_out.y, v_out.z);
	sub_vect(&v1, &v2, &v_out);
	printf("v1 - v2 = (%f, %f, %f)\n", v_out.x, v_out.y, v_out.z);
	ortho_projection(&v1, &v2, &v_out);
	printf("proj(v1,v2) = (%f, %f, %f)\n", v_out.x, v_out.y, v_out.z);
/*
	t_scene scene;
	t_mlx	mlx_cfg;

	if (ac != 4)
		return (0);
	init_scene(&scene, atoi(av[1]), atoi(av[2]), atoi(av[3]));	
	scene.resx = 800;
	scene.resy = 600;
	init_graphics(&mlx_cfg, scene.resx, scene.resy);
	raytrace(&scene, &mlx_cfg);
	if (!(mlx_put_image_to_window(mlx_cfg.mlx_ptr, mlx_cfg.win_ptr,
		mlx_cfg.img_ptr, 0, 0)))
		return (1);
*/
/*
	alter_pixel(&mlx_cfg, RED, 10, 10);
	alter_pixel(&mlx_cfg, GREEN, 20, 20);
	alter_pixel(&mlx_cfg, BLUE, 30, 30);
	mlx_loop(mlx_cfg.mlx_ptr);
*/
}
