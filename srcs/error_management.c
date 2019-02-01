#include "fractal.h"

int display_error(int usage)
{
	if (usage == 1)
	{
		printf("usage: ./fdf fractal color\nPossible colors are :");
		printf("white, red, blue, green\n");
		printf("Possible fractals are : mandelbrot, \n");
		return 0;
	}
	if (usage == 2)
	{
		printf("The window's size is between 200 and 2500\n");
		return 0;
	}
	printf("error\n");
	return 0;
}

int error_management(char **argv, int argc, struct info *info)
{
	(void)argv;
	(void)info;
	if (argc != 2)
		return display_error(1);
	if (!(check_winsize()))
		return display_error(2);
	return 0;
}

int check_winsize(void)
{
	if (WINLEN > 2500 || WINHEIGHT > 2500)
		return 0;
	if (WINLEN < 200 || WINHEIGHT < 200)
		return 0;
	return 1;
}
