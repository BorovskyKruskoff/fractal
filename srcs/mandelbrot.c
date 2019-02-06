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
/*
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
*/
void draw_mandelbrot(struct info *info)
{
	double re_factor = (info->x_total) / WINLEN;
	double im_factor = (info->y_total) / WINHEIGHT;

	for (unsigned y = 0; y < WINHEIGHT; ++y)
	{
		double c_im = info->part.y2 - y * im_factor;
		for (unsigned x = 0; x < WINLEN; ++x)
		{
			double c_re = info->part.x1 + x * re_factor;
			double z_re = c_re;
			double z_im = c_im;
			unsigned int n = 0;
			int isinside = 1;

			while (n < info->it_max)
			{
				double z_re2 = z_re * z_re;
				double z_im2 = z_im * z_im;
				if (z_re2 + z_im2 > 4)
				{
					isinside = 0;
					break;
				}
				z_im = 2 * z_re * z_im + c_im;
				z_re = z_re2 - z_im2 + c_re;
				++n;
			}
			if (isinside)
				draw(info, x, y, 0);
			else
				draw(info, x, y, 255 * (n / info->it_max));
		}
	}
	mlx_put_image_to_window
		(info->mlx, info->win, info->image_pointer, 0, 0);
}
