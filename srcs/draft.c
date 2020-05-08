#include "minirt.h"
#include "mlx.h"
#include "colors.h"
#include "aabb.h"
#include "math.h"
#include "spheric.h"
#include "print.h"
#include "actions.h"
#include "keys_linux.h"

void	(*g_key_pressed_ft[MAX_CODE + 1])(void *param);

static void	null_action(void *param)
{
	(void)param;
	return ;
}

static void assign_fts(void)
{
	int		i;

	i = -1;
	while (++i < MAX_CODE)
		g_key_pressed_ft[i] = null_action;
	g_key_pressed_ft[KEY_W] = move_forward;  
	g_key_pressed_ft[KEY_S] = move_backward; 
	g_key_pressed_ft[KEY_A] = move_left; 
	g_key_pressed_ft[KEY_D] = move_right; 
	//g_key_pressed_ft[KEY_UP] = parse_plane;  
	//g_key_pressed_ft[KEY_DOWN] = parse_sphere;  
	g_key_pressed_ft[KEY_LEFT] = turn_left;  
	g_key_pressed_ft[KEY_RIGHT] = turn_right;  
}

void	init_scene(t_scene *scene)
{
	double		posaabbx1;
	double		posaabby1;
	double		posaabbz1;
	double		posaabbx2;
	double		posaabby2;
	double		posaabbz2;
	double		posaabbx3;
	double		posaabby3;
	double		posaabbz3;
	t_spheric	cam_orient_sph;


	scene->resx = 800;
	scene->resy = 600;

	scene->ref_orient = malloc(sizeof(t_vect));
	scene->ref_orient->x = 0.;
	scene->ref_orient->y = 0.;
	scene->ref_orient->z = 1.;

	scene->background_rgb[0] = 0xd6; 
	scene->background_rgb[1] = 0xd9; 
	scene->background_rgb[2] = 0xce; 
	
	scene->cam_pos = malloc(sizeof(t_vect));
	scene->cam_orient = malloc(sizeof(t_vect));
	printf("position camera: ");
	scanf("%lf%lf%lf", &scene->cam_pos->x, &scene->cam_pos->y, &scene->cam_pos->z);
	printf("\n");
	/*
	printf("orientation camera: ");
	scanf("%lf%lf%lf", &scene->cam_orient->x, &scene->cam_orient->y,
			&scene->cam_orient->z);
	printf("\n");
	*/
	double phi_degree;

	printf("phi : ");
	scanf("%lf", &phi_degree);
	scene->phi = to_radian(phi_degree);

	cam_orient_sph.rho = 1;
	cam_orient_sph.phi = scene->phi;
	cam_orient_sph.theta = 0;
	print_angle(scene->phi, scene->theta);
	to_cartesian(&cam_orient_sph, scene->cam_orient); 
	//normalize(scene->cam_orient, scene->cam_orient);
	scene->aabb1 = malloc(sizeof(t_aabb));
	scene->aabb2 = malloc(sizeof(t_aabb));
	scene->aabb3 = malloc(sizeof(t_aabb));
/*
	printf("position cube bleu: ");
	scanf("%lf%lf%lf", &posaabbx1, &posaabby1, &posaabbz1);
	printf("\n");
	printf("position cube orange : ");
	scanf("%lf%lf%lf", &posaabbx2, &posaabby2, &posaabbz2);
	printf("\n");
	printf("position cube vert: ");
	scanf("%lf%lf%lf", &posaabbx3, &posaabby3, &posaabbz3);
	printf("\n");

*/
	posaabbx1 = 100;
	posaabby1 = -50;
	posaabbz1 = 560;
	posaabbx2 = -50;
	posaabby2 = -200;
	posaabbz2 = 560;
	posaabbx3 = -200;
	posaabby3 = -50;
	posaabbz3 = 560;

	//cube bleu
	scene->aabb1->corner[0].x = posaabbx1 + 0;
	scene->aabb1->corner[0].y = posaabby1 + 0;
	scene->aabb1->corner[0].z = posaabbz1 + 0; 
	scene->aabb1->corner[1].x = posaabbx1 + 100;
	scene->aabb1->corner[1].y = posaabby1 + 100;
	scene->aabb1->corner[1].z = posaabbz1 + 100; 
	scene->aabb1->rgb[0] = 0x71; 
	scene->aabb1->rgb[1] = 0xa9; 
	scene->aabb1->rgb[2] = 0xf7; 
	
	//cube orange
	scene->aabb2->corner[0].x = posaabbx2 + 0;
	scene->aabb2->corner[0].y = posaabby2 + 0;
	scene->aabb2->corner[0].z = posaabbz2 + 0; 
	scene->aabb2->corner[1].x = posaabbx2 + 100;
	scene->aabb2->corner[1].y = posaabby2 + 100;
	scene->aabb2->corner[1].z = posaabbz2 + 100; 
	scene->aabb2->rgb[0] = 0xef; 
	scene->aabb2->rgb[1] = 0x8a; 
	scene->aabb2->rgb[2] = 0x17; 
	
	//cube vert
	scene->aabb3->corner[0].x = posaabbx3 + 0;
	scene->aabb3->corner[0].y = posaabby3 + 0;
	scene->aabb3->corner[0].z = posaabbz3 + 0; 
	scene->aabb3->corner[1].x = posaabbx3 + 100;
	scene->aabb3->corner[1].y = posaabby3 + 100;
	scene->aabb3->corner[1].z = posaabbz3 + 100; 
	scene->aabb3->rgb[0] = 0x4c; 
	scene->aabb3->rgb[1] = 0x9f; 
	scene->aabb3->rgb[2] = 0x70; 

	//print_vect(scene->cam_orient);
	extract_scene_rotation(scene->cam_orient, scene->ref_orient, &scene->phi,
		&scene->theta);
	//print_angle(, acos(scene->cam_orient->z));
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

static void send_ray(t_scene *scene, t_mlx *mlx_cfg, int dx, int dy)
{
	t_ray	ray;
	t_vect	origin;
	t_vect	direction;
	t_vect	inv_direction;
		
	origin.x = scene->cam_pos->x;
	origin.y = scene->cam_pos->y;
	origin.z = scene->cam_pos->z;

	direction.x = scene->resx/2. - dx;
	direction.y = scene->resy/2. - dy;
	direction.z = 550.;	
	inv_direction.x = 1 / direction.x;
	inv_direction.y = 1 / direction.y;
	inv_direction.z = 1 / direction.z;
	ray.origin = &origin;
	ray.direction = &direction;
	ray.inv_direction = &inv_direction;
	ray.sign[0] = (direction.x < 0);
	ray.sign[1] = (direction.y < 0);
	ray.sign[2] = (direction.z < 0);
	if (intersect_aabb(scene->aabb1, &ray))
		apply_color(scene->aabb1->rgb, mlx_cfg, dx, dy);
	/*
	else if (intersect_aabb(scene->aabb2, &ray))
		apply_color(scene->aabb2->rgb, mlx_cfg, dx, dy);
	else if (intersect_aabb(scene->aabb3, &ray))
		apply_color(scene->aabb3->rgb, mlx_cfg, dx, dy);
	*/
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
	printf("cc\n");
}

static void	adapt_aabb(t_aabb *aabb, t_vect *cam_pos, double phi, double theta)
{
	t_vect	translation;
	
	rotate_point(phi, theta, aabb->corner, aabb->corner); 
	rotate_point(phi, theta, aabb->corner + 1, aabb->corner + 1); 
	scale(-1, cam_pos, &translation);
	add_vect(aabb->corner, &translation, aabb->corner);
	add_vect(aabb->corner + 1, &translation, aabb->corner + 1);
}

void	adapt_scene(t_scene *scene)
{
	adapt_aabb(scene->aabb1, scene->cam_pos, scene->phi, scene->theta);
//	adapt_aabb(scene->aabb2, scene->cam_pos, scene->phi, scene->theta);
//	adapt_aabb(scene->aabb3, scene->cam_pos, scene->phi, scene->theta);
}

int main(int ac, char **av)
{

	(void)ac;
	(void)av;
	t_scene scene;
	t_mlx	mlx_cfg;
	t_param param;

	param.scene = &scene;
	param.mlx_cfg = &mlx_cfg;
	assign_fts();
	init_scene(&scene);
	scene.resx = 800;
	scene.resy = 600;
	init_graphics(&mlx_cfg, scene.resx, scene.resy);
	adapt_scene(&scene);
	raytrace(&scene, &mlx_cfg);
	if (!(mlx_put_image_to_window(mlx_cfg.mlx_ptr, mlx_cfg.win_ptr,
		mlx_cfg.img_ptr, 0, 0)))
		return (1);
	//mlx_loop_hook(mlx_cfg.mlx_ptr, loop_hook, &param);
	mlx_key_hook(mlx_cfg.win_ptr, key_pressed_hook, &param);
	mlx_loop(mlx_cfg.mlx_ptr);
}
