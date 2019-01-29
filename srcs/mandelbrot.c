#include <fractal.h>

int valid_pixel(int x, int y)
{
	if (x < 0 || x > WINLEN || y < 0 || y > WINHEIGHT)
		return 0;
	return 1;
}

void draw(struct info *info, int x, int y)
{
	int new_x = 3200 * y + x * 4;
	
	if (valid_pixel(x, y))
	{
		info->image[new_x] = 255;
		info->image[new_x + 1] = 255;
		info->image[new_x + 2] = 255;
		info->image[new_x + 3] = 255;
	}
}

void check_pixel(struct info *info, int x, int y)
{
	double tmp = 0;
//	print("%p\n", info
	double c_r = (x / info->zoom) + info->part.x1;
	double c_i = (y / info->zoom) + info->part.y1;
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
		draw(info, x, y);
}

void draw_mandelbrot(struct info *info)
{
	int x = 0;
	int y = 0;
	int btp = 24;
	int size_line = WINLEN * 4;
	int endian = 0;

	info->image_pointer = mlx_new_image(info->mlx, WINLEN, WINHEIGHT);
	info->image = mlx_get_data_addr
		(info->image_pointer, &(btp), &(size_line), &(endian));
	while(y < info->image_y)
	{
		while(x < info->image_x)
		{
			check_pixel(info, x, y);
			x++;
		}
		y++;
		x = 0;
	}
	mlx_put_image_to_window
		(info->mlx, info->win, info->image_pointer, 0, 0);
}
