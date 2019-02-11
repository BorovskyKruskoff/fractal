#include <fractal.h>

int valid_pixel(int x, int y)
{
	if (x < 0 || x > WINLEN || y < 0 || y > WINHEIGHT)
		return 0;
	return 1;
}

void draw(struct info *info, int x, int y, char color)
{
	int new_x = (WINLEN * 4) * y + x * 4;
	
	if (valid_pixel(x, y))
	{
		info->image[new_x] = color * info->blue;
		info->image[new_x + 1] = color * info->green;
		info->image[new_x + 2] = color * info->red;
		info->image[new_x + 3] = color;
	}
}

void check_pixel(struct info *info, int x, int y)
{
	double tmp = 0;
	double c_r = (x / info->zoomx) + info->part.x1;
	double c_i = (y / info->zoomy) + info->part.y1;
	double z_r = 0;
	double z_i = 0;
	int i = 0;

	while (z_r * z_r + z_i * z_i < 4 && i < info->it_max)
	{
		tmp = z_r;
		z_r = z_r * z_r - z_i * z_i + c_r;
		z_i = 2 * z_i * tmp + c_i;
		i++;
	}
	if (i >= info->it_max)
		draw(info, x, y, 0);
	else
		draw(info, x, y, 255 * (i / info->it_max));
}

// thread 1
void *draw_top_right(void *param)
{
	struct info *info = (struct info*)param;
	int x_max = WINLEN;
	int y_max = WINHEIGHT;
	int x = WINLEN / 2;
	int y = 0;

	while (y < y_max)
	{
		while (x < x_max)
		{
			check_pixel(info, x, y);
			x++;
		}
		x = WINLEN / 2;
		y++;
	}
	pthread_exit((void*)info->thread_1);
}

// thread 2
void *draw_bottom_right(void *param)
{
	struct info *info = (struct info*)param;
	int x_max = WINLEN;
	int y_max = WINHEIGHT;
	int x = WINLEN / 2;
	int y = WINHEIGHT / 2;

	while (y < y_max)
	{
		while (x < x_max)
		{
			check_pixel(info, x, y);
			x++;
		}
		x = WINLEN / 2;
		y++;
	}
	pthread_exit((void*)info->thread_2);
}

// thread 3
void *draw_bottom_left(void *param)
{
	struct info *info = (struct info*)param;
	int x_max = WINLEN / 2;
	int y_max = WINHEIGHT;
	int x = 0;
	int y = WINHEIGHT / 2;

	while (y < y_max)
	{
		while (x < x_max)
		{
			check_pixel(info, x, y);
			x++;
		}
		x = 0;
		y++;
	}
	pthread_exit((void*)info->thread_3);
}

void draw_mandelbrot(struct info *info)
{
	int x = 0;
	int y = 0;

	(void)x;
	(void)y;
	pthread_create(&info->thread_1, NULL, &draw_top_right, info);
	pthread_create(&info->thread_2, NULL, &draw_bottom_right, info);
	pthread_create(&info->thread_3, NULL, &draw_bottom_left, info);
	while (y < WINHEIGHT / 2)
	{
		while (x < WINLEN / 2)
		{
			check_pixel(info, x, y);
			x++;
		}
		x = 0;
		y++;
	}
	mlx_put_image_to_window
		(info->mlx, info->win, info->image_pointer, 0, 0);
}
