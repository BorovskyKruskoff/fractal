#include "fractal.h"

static int key_management(int keycode, void *param)
{
	struct info	*info;

	info = (struct info*)param;
	printf("The key pressed is : %d\n.", keycode);
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
	mlx_key_hook(win, key_management, (void*)info);
	mlx_loop(mlx);
	return 0;
}
