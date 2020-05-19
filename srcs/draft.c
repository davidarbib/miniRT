#include "minirt.h"
#include "mlx.h"
#include "X11/X.h"
#include "colors.h"
#include "actions.h"

int main(int ac, char **av)
{

	(void)ac;
	(void)av;
	t_scene scene;
	t_mlx	mlx_cfg;
	t_param param;

	param.scene = &scene;
	param.mlx_cfg = &mlx_cfg;
	assign_key_fts();
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
	//mlx_key_hook(mlx_cfg.win_ptr, key_pressed_hook, &param);
	mlx_hook(mlx_cfg.win_ptr, KeyPress, KeyPressMask, key_pressed_hook,
			&param);
	mlx_loop(mlx_cfg.mlx_ptr);
}
