#include "minirt.h"
#include "mlx.h"
//#include "X11/X.h"
#include "colors.h"
#include "actions.h"
#include "bitmap.h"

int main(int ac, char **av)
{
	(void)ac;
	(void)av;
	t_scene scene;
	t_mlx	mlx_cfg;
	t_param param;
	t_bmp	bmp;

	param.scene = &scene;
	param.mlx_cfg = &mlx_cfg;
	assign_key_fts();
	scene.resx = 800;
	scene.resy = 600;
	init_scene(&scene);
	init_graphics(&mlx_cfg);
	raytrace(&scene, &mlx_cfg);
	bmp.type[0] = 'B';
	bmp.type[1] = 'M';
	bmp.width = scene.resx;
	bmp.height = scene.resy;
	bmp.planes = 1;
	bmp.bitcount = 24;
	bmp.compression = 0;
	if (!(bitmap_output(&bmp, mlx_cfg.img_data)))
		bmp_sys_error(&scene);
	if (!(mlx_put_image_to_window(mlx_cfg.mlx_ptr, mlx_cfg.win_ptr,
		mlx_cfg.img_ptr, 0, 0)))
		return (1);
//	mlx_hook(mlx_cfg.win_ptr, KeyPress, KeyPressMask, key_pressed_hook,
//			&param);
	mlx_loop(mlx_cfg.mlx_ptr);
}
