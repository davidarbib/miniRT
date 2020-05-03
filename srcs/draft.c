#include "minirt.h"
#include "mlx.h"
#include "colors.h"
#include "aabb.h"
#include "quaternion.h"
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
}				t_scene;

static void set_local_quaternion(double semi_angle, t_vect *axis,
		double *quater_z)
{
	double semi_angle_sinus;

	semi_angle_sinus = sin(semi_angle);
	quater_z[A] = cos(semi_angle);
	quater_z[B] = semi_angle_sinus * axis->x;
	quater_z[C] = semi_angle_sinus * axis->y;
	quater_z[D] = semi_angle_sinus * axis->z;
}

static void	xz_projection(t_vect *cam_orient, t_vect *proj_xz, double *quater_z)
{
	t_vect	axis_orient;    
	t_vect  proj_z;
	t_vect  proj_x;
	double	angle;

	axis_orient.x = 1;
	axis_orient.y = 0;
	axis_orient.z = 0;
	ortho_projection(cam_orient, &axis_orient, &proj_x);	
	axis_orient.x = 0;
	axis_orient.y = 0;
	axis_orient.z = 1;
	ortho_projection(cam_orient, &axis_orient, &proj_z);  
	add_vect(&proj_x, &proj_z, proj_xz);
	normalize(proj_xz, proj_xz); 
	angle = acos(dot(cam_orient, proj_xz));
	set_local_quaternion(angle / 2, &axis_orient, quater_z); 
}

void		set_global_quaternions(double *global_quater,
		double *global_quater_conjugate, t_vect *cam_orient, t_vect *ref_orient)
{
	double	quater_z[4];
	double	quater_y[4];
	t_vect	proj_xz;
	t_vect	proj_ref;
	t_vect	y_axis;

	xz_projection(cam_orient, &proj_xz, quater_z);
	ortho_projection(&proj_xz, ref_orient, &proj_ref);
	normalize(&proj_ref, &proj_ref); 
	y_axis.x = 0;	
	y_axis.y = 1;	
	y_axis.z = 0;
	set_local_quaternion(acos(dot(&proj_xz, &proj_ref)) / 2, &y_axis, quater_y);
	mult_quater(quater_y, quater_z, global_quater);	
	conjugate_quater(global_quater, global_quater_conjugate);
}

void	init_scene(t_scene *scene)
{
	t_vect		cam_pos;
	t_vect		cam_orient;
	//double		posaabbx1;
	//double		posaabby1;
	//double		posaabbz1;
	double		posaabbx2;
	double		posaabby2;
	double		posaabbz2;
	//double		posaabbx3;
	//double		posaabby3;
	//double		posaabbz3;

	scene->resx = 800;
	scene->resy = 600;

	scene->background_rgb[0] = 0xd6; 
	scene->background_rgb[1] = 0xd9; 
	scene->background_rgb[2] = 0xce; 
	
	cam_pos.x = 0;
	cam_pos.y = 0;
	cam_pos.z = 0;
	cam_orient.x = 0;
	cam_orient.y = 0;
	cam_orient.z = 1;
	/*
	printf("position camera: ");
	scanf("%lf%lf%lf", &cam_pos.x, &cam_pos.y, &cam_pos.z);
	printf("\n");
	printf("orientation camera: ");
	scanf("%lf%lf%lf", &cam_orient.x, &cam_orient.y, &cam_orient.z);
	printf("\n");
	*/

	scene->cam_pos = &cam_pos;
	scene->cam_orient = &cam_orient;

	//scene->aabb1 = malloc(sizeof(t_aabb));
	scene->aabb2 = malloc(sizeof(t_aabb));
	//scene->aabb3 = malloc(sizeof(t_aabb));

	//printf("position cube bleu: ");
	//scanf("%lf%lf%lf", &posaabbx1, &posaabby1, &posaabbz1);
	//printf("\n");
	//printf("position cube orange : ");
	//scanf("%lf%lf%lf", &posaabbx2, &posaabby2, &posaabbz2);
	//printf("\n");
	//printf("position cube vert: ");
	//scanf("%lf%lf%lf", &posaabbx3, &posaabby3, &posaabbz3);
	//printf("\n");

	/*
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
	*/
	
	posaabbx2 =	-200;
	posaabby2 = -200;
	posaabbz2 = 160;

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
	
	/*
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
	*/
	//set_global_quaternions(scene->rot_quater, scene->conjugate_rot_quater,
	//		scene->cam_orient, scene->ref_orient);
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
	/*
	if (intersect_aabb(scene->aabb1, &ray))
		apply_color(scene->aabb1->rgb, mlx_cfg, dx, dy);
		//mlx_pixel_put(mlx_cfg->mlx_ptr, mlx_cfg->win_ptr, dx, dy, BLUE);
	*/
	if (intersect_aabb(scene->aabb2, &ray))
	{
		scene->hits++;
		apply_color(scene->aabb2->rgb, mlx_cfg, dx, dy);
	}
	else
		apply_color(scene->background_rgb, mlx_cfg, dx, dy);
		//mlx_pixel_put(mlx_cfg->mlx_ptr, mlx_cfg->win_ptr, dx, dy, RED);
	/*
	else if (intersect_aabb(scene->aabb3, &ray))
		apply_color(scene->aabb3->rgb, mlx_cfg, dx, dy);
		//mlx_pixel_put(mlx_cfg->mlx_ptr, mlx_cfg->win_ptr, dx, dy, GREEN);
	else
		apply_color(scene->background_rgb, mlx_cfg, dx, dy);
		//mlx_pixel_put(mlx_cfg->mlx_ptr, mlx_cfg->win_ptr, dx, dy, WHITE);
	*/
}

void	raytrace(t_scene *scene, t_mlx *mlx_cfg)
{
	int dx;
	int dy;

	scene->hits = 0;
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

void	rotate_point(t_vect *point, double *rot_quater,
		double *conjugate_rot_quater)
{
	double	quater1[4];
	double	quater2[4];

	to_quater(point, quater1);
	mult_quater(rot_quater, quater1, quater2);
	mult_quater(quater2, conjugate_rot_quater, quater1);
	to_point(quater1, point);
}

void	adapt_aabb(t_aabb *aabb, t_vect *cam_pos, double *rot_quater,
		double *conjugate_rot_quater)
{
	t_vect	translation;
	
	scale(-1, cam_pos, &translation);
	add_vect(aabb->corner, &translation, aabb->corner);
	add_vect(aabb->corner + 1, &translation, aabb->corner + 1);
	rotate_point(aabb->corner, rot_quater, conjugate_rot_quater); 
	rotate_point(aabb->corner + 1, rot_quater, conjugate_rot_quater);
}

void	adapt_scene(t_scene *scene)
{
	adapt_aabb(scene->aabb1, scene->cam_pos, scene->rot_quater,
			scene->conjugate_rot_quater);
	adapt_aabb(scene->aabb2, scene->cam_pos, scene->rot_quater,
			scene->conjugate_rot_quater);
	adapt_aabb(scene->aabb3, scene->cam_pos, scene->rot_quater,
			scene->conjugate_rot_quater);
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
	//adapt_scene(&scene);
	raytrace(&scene, &mlx_cfg);
	if (!(mlx_put_image_to_window(mlx_cfg.mlx_ptr, mlx_cfg.win_ptr,
		mlx_cfg.img_ptr, 0, 0)))
		return (1);
	printf("nb de hits : %d\n", scene.hits);
	mlx_loop(mlx_cfg.mlx_ptr);
/*
	alter_pixel(&mlx_cfg, RED, 10, 10);
	alter_pixel(&mlx_cfg, GREEN, 20, 20);
	alter_pixel(&mlx_cfg, BLUE, 30, 30);
*/
}
