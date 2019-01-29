#include "fractal.h"

//x_percent being 0 means the window was clicked on the far left
//y_percent being 0 means the window was clicked on the top
int zoom_in(int x, int y, struct info *info)
{
	double x_percent;
	double y_percent;
	double x_cut = info->x_total * 0.75;
	double y_cut = info->y_total * 0.75;

	(void)x_percent;
	(void)y_percent;
	(void)x_cut;
	(void)y_cut;
	(void)x;
	(void)y;
	(void)info;
	info->x_total *= 0.75;
	info->y_total *= 0.75;
	if (x < WINLEN / 10)
		x_percent = 0;
	else if (x > WINLEN * 0.9)
		x_percent = 100;
//	else
//		x_percent = 
	return 0;
}

static int key_management(int keycode, void *param)
{
	struct info *info;

	info = (struct info*)param;
	(void)info;
	printf("The key pressed is : %d\n.", keycode);
	if (keycode == 65307)
		exit(0);
	return 0;
}

static int mouse_management(int keycode, int x, int y, void *param)
{
	struct info *info;

	info = (struct info*)param;
	(void)info;
	printf("The mouse keycode is : %d\n.", keycode);
	if (keycode == 1)
		zoom_in(x, y, info);
	return 0;
}

void initiate_mandelbrot(struct info *info)
{
	info->part.x1 = -2.1;
	info->part.x2 = 0.6;
	info->part.y1 = -1.2;
	info->part.y2 = 1.2;
	info->x_total = 2.7;
	info->y_total = 2.4;
	if (WINLEN > WINHEIGHT)
		info->min_length = WINHEIGHT;
	else
		info->min_length = WINLEN;
	info->zoom = info->min_length / info->x_total;
	info->it_max = 100;
	info->image_x = info->x_total * info->zoom;
	info->image_y = info->y_total * info->zoom;
}

int main(int argc, char **argv)
{
	struct info	*info;
	void		*mlx;
	void		*win;

	(void)argc;
	(void)argv;
	if (!(info = (struct info*)malloc(sizeof(struct info))))
		return (display_error(0));
//	if (error_management(argv, argc, info) || check_winsize())
//		return (1);
	initiate_mandelbrot(info);
	mlx = mlx_init();
	win = mlx_new_window(mlx, WINLEN, WINHEIGHT,"Fractal ~ ggay");
	info->mlx = mlx;
	info->win = win;
	draw_mandelbrot(info);
	mlx_key_hook(win, key_management, (void*)info);
	mlx_mouse_hook(win, mouse_management, (void*)info);
	mlx_loop(mlx);
	return 0;
}
