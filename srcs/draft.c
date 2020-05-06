#include "minirt.h"
#include "mlx.h"
#include "colors.h"
#include "aabb.h"
#include "math.h"

typedef struct	s_scene
{
	t_vect			*cam_pos;
	t_vect			*cam_orient;
	t_vect			*ref_orient;
	t_aabb			*aabb1;
	t_aabb			*aabb2;
	t_aabb			*aabb3;
	t_sphere		*sphere;
	unsigned char	background_rgb[3]; 
	int				resx;
	int				resy;
	int				hits;
	double			rot_quater[4];
	double			conjugate_rot_quater[4];
	double			theta;
	double			phi;
}				t_scene;

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
	printf("orientation camera: ");
	scanf("%lf%lf%lf", &scene->cam_orient->x, &scene->cam_orient->y,
			&scene->cam_orient->z);
	printf("\n");
	normalize(scene->cam_orient, scene->cam_orient);
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
	posaabbz1 = 160;
	posaabbx2 = -50;
	posaabby2 = -200;
	posaabbz2 = 160;
	posaabbx3 = -200;
	posaabby3 = -50;
	posaabbz3 = 160;

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

	extract_scene_rotation(scene->cam_orient, scene->ref_orient, &scene->phi,
			&scene->theta);
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
		
	origin.x = scene->cam_pos->x;
	origin.y = scene->cam_pos->y;
	origin.z = scene->cam_pos->z;

	direction.x = scene->resx/2. - dx;
	direction.y = scene->resy/2. - dy;
	direction.z = 150.;	
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
	else if (intersect_aabb(scene->aabb2, &ray))
		apply_color(scene->aabb2->rgb, mlx_cfg, dx, dy);
	else if (intersect_aabb(scene->aabb3, &ray))
		apply_color(scene->aabb3->rgb, mlx_cfg, dx, dy);
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

void	adapt_aabb(t_aabb *aabb, t_vect *cam_pos, double phi, double theta)
{
	t_vect	translation;
	
	scale(-1, cam_pos, &translation);
	add_vect(aabb->corner, &translation, aabb->corner);
	add_vect(aabb->corner + 1, &translation, aabb->corner + 1);
	rotate_point(phi, theta, aabb->corner, aabb->corner); 
	rotate_point(phi, theta, aabb->corner + 1, aabb->corner); 
}

void	adapt_scene(t_scene *scene)
{
	//printf("scene->rot_quater = (%f, %f, %f, %f)\n", scene->rot_quater[A],
	//		scene->rot_quater[B], scene->rot_quater[C], scene->rot_quater[D]);
	/*
	printf("scene->conjugate_rot_quater = (%f, %f, %f, %f)\n",
			scene->conjugate_rot_quater[A],
			scene->conjugate_rot_quater[B], scene->conjugate_rot_quater[C],
			scene->conjugate_rot_quater[D]);
	*/
	printf("corner[0] = (%f, %f, %f)\n", scene->aabb1->corner[0].x,
			scene->aabb1->corner[0].y, scene->aabb1->corner[0].z);
	adapt_aabb(scene->aabb1, scene->cam_pos, scene->phi, scene->theta);
	printf("corner[0] = (%f, %f, %f)\n", scene->aabb1->corner[0].x,
			scene->aabb1->corner[0].y, scene->aabb1->corner[0].z);
	adapt_aabb(scene->aabb2, scene->cam_pos, scene->phi, scene->theta);
	adapt_aabb(scene->aabb3, scene->cam_pos, scene->phi, scene->theta);
}

int main(int ac, char **av)
{

	(void)ac;
	(void)av;
/*
	double q1[4] = {3, 7, -5, 1};
	double q2[4] = {6, -2, 9, 14};
	double q_out[4];

	quater_add(q1, q2, q_out);
	printf("q1 + q2 = (%f, %f, %f, %f)\n",
			q_out[A], q_out[B], q_out[C], q_out[D]);

	mult_quater(q1, q2, q_out);
	printf("q1 x q2 = (%f, %f, %f, %f)\n",
			q_out[A], q_out[B], q_out[C], q_out[D]);
*/
/*
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
*/
	t_scene scene;
	t_mlx	mlx_cfg;

	init_scene(&scene);
	scene.resx = 800;
	scene.resy = 600;
	init_graphics(&mlx_cfg, scene.resx, scene.resy);
	adapt_scene(&scene);
	raytrace(&scene, &mlx_cfg);
	if (!(mlx_put_image_to_window(mlx_cfg.mlx_ptr, mlx_cfg.win_ptr,
		mlx_cfg.img_ptr, 0, 0)))
		return (1);
	mlx_loop(mlx_cfg.mlx_ptr);
/*
	alter_pixel(&mlx_cfg, RED, 10, 10);
	alter_pixel(&mlx_cfg, GREEN, 20, 20);
	alter_pixel(&mlx_cfg, BLUE, 30, 30);
*/
}
