#ifndef FRACTAL_H
# define FRACTAL_H

# ifndef M_PI
#  define M_PI 3.1415926535
# endif

# define WINLEN 800
# define WINHEIGHT 600


# include <ctype.h>
# include <math.h>
# include <mlx.h>
# include <fcntl.h>
# include <strings.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>

struct part
{
	double x1;
	double x2;
	double y1;
	double y2;
};

struct info
{
	struct part part;
	double it_max;
	double zoomx;
	double zoomy;
	double x_total;
	double y_total;
	int min_length;
	int image_x;
	int image_y;
	int red;
	int blue;
	int green;
	void *mlx;
	void *win;
	void *image_pointer;
	char *image;
};

void draw_mandelbrot(struct info *info);
int display_error(int usage);
int error_management(char **argv, int argc, struct info *info);
int check_winsize(void);
int initiate_colors(struct info *info, char **argv, int argc);

#endif
