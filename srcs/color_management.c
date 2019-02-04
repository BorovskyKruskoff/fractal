#include "fractal.h"

static int compare(char *s1, char *s2)
{
	int a = 0;

	while (s1[a] == s2[a] && isgraph(s1[a]) && isgraph(s2[a]))
		a++;
	if (s1[a] == s2[a])
		return 1;
	return 0;
}

int special_colors(struct info *info, char **argv, int argc)
{
	(void)argc;
	if (compare(argv[1], "purple"))
	{
		info->blue = 1;
		info->red = 1;
	}
	else if (compare(argv[1], "yellow"))
	{
		info->red = 1;
		info->green = 1;
	}
	else if (compare(argv[1], "cyan"))
	{
		info->green = 1;
		info->blue = 1;
	}
	else
		display_error(1);
	return 1;
}

int initiate_colors(struct info *info, char **argv, int argc)
{
	info->red = 0;
	info->blue = 0;
	info->green = 0;
	(void)argc;
	if (compare(argv[1], "white"))
	{
		info->red = 1;
		info->blue = 1;
		info->green = 1;
		return 1;
	}
	else if (compare(argv[1], "red"))
	{
		info->red = 1;
		return 1;
	}
	else if (compare(argv[1], "blue"))
	{
		info->blue = 1;
		return 1;
	}
	else if (compare(argv[1], "green"))
	{
		info->green = 1;
		return 1;
	}
	else
		return (special_colors(info, argv, argc));
}
