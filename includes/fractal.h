#ifndef FRACTAL_H
# define FRACTAL_H

# ifndef M_PI
#  define M_PI 3.1415926535
# endif

# include <ctype.h>
# include <math.h>
# include <mlx.h>
# include <fcntl.h>
# include <strings.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>

# define WINLEN 800
# define WINHEIGHT 600

struct info
{
	void *mlx;
	void *win;
	void *image_pointer;
	char *image;
};

int display_error(int usage);
int error_management(char **argv, int argc, struct info *info);
int check_winsize(void);

#endif
