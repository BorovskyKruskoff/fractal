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
		draw(info, x, y, 255);
	else if (i > info->it_max * 0.100)
		draw(info, x, y, 100);
	else
		draw(info, x, y, 35);
}

void draw_mandelbrot(struct info *info)
{
	int x = 0;
	int y = 0;
	int btp = 24;
	int size_line = WINLEN * 4;
	int endian = 0;

//	printf("zoom = %f\nx_total = %f\ny_total = %f\n", info->zoom,
//		info->x_total, info->y_total);
//	printf("x1 = %f\nx2 = %f\ny1 = %f\ny2 = %f\n", info->part.x1,
//		info->part.x2, info->part.y1, info->part.y2);
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
