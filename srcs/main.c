#include "fdf.h"

static int key_management(int keycode, void *param)
{
	struct info	*info;

	info = (struct info*)param;
	printf("The key pressed is : %d\n.", keycode);
	if (keycode == 113)
		info->rot_z += M_PI / 16;
	else if (keycode == 119)
		info->rot_y += M_PI / 16;
	else if (keycode == 101)
		info->rot_z -= M_PI / 16;
	else if (keycode == 97)
		info->rot_x -= M_PI / 16;
	else if (keycode == 115)
		info->rot_y -= M_PI / 16;
	else if (keycode == 100)
		info->rot_x += M_PI / 16;
	else
		other_keys(keycode, info);
	if (!(empty_window(info)))
		return 1;
	return 0;
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
	mlx = mlx_init();
	win = mlx_new_window(mlx, WINLEN, WINHEIGHT, "FdF ~ ggay");
	info->mlx = mlx;
	info->win = win;
//	reset_parameters(info);
	if (!(create_image(info)))
		return (display_error(0));
	mlx_key_hook(win, key_management, (void*)info);
	mlx_loop(mlx);
	return 0;
}
