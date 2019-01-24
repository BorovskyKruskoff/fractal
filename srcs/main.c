#include "fractal.h"

static int key_management(int keycode, void *param)
{
	struct info	*info;

	info = (struct info*)param;
	printf("The key pressed is : %d\n.", keycode);
	return 0;
}

initiate_attributes(struct info *info)
{
	info->part.x1 = -2.1;
	info->part.x2 = 0.6;
	info->part.y1 = -1.2;
	info->part.y2 = 1.2;
	info->zoom = 100;
	info->it_max = info->zoom / 2;
	info->image_x = (info->part.x2 - info->part.x1) * info->zoom;
	info->image_y = (info->part.y2 - info->part.y1) * info->zoom;
}

int main(int argc, char **argv)
{
	struct info	*info;
	void		*mlx;
	void		*win;

	if (!(info = (struct info*)malloc(sizeof(struct info))))
		return (display_error(0));
	if (error_management(argv, argc, info) || check_winsize())
		return (1);
	initiate_attributes(info);
	mlx = mlx_init();
	win = mlx_new_window(mlx, info->image_x, info->image_y,
		"Fractal ~ ggay");
	info->mlx = mlx;
	info->win = win;
//	reset_parameters(info);
	mlx_key_hook(win, key_management, (void*)info);
	mlx_loop(mlx);
	return 0;
}
