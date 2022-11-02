#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	main(int argc, char **argv)
{
	FILE	*fd;
	int		scan;
	char	a, b;
	float	c, d, e, f;

	fd = fopen(argv[1], "r");
	if (fd == NULL)
		printf("ERROR FD");
	scan = 6;
	while (scan == 6)
	{
		scan = fscanf(fd, "%c %f %f %f %f %c\n", &a, &c, &d, &e, &f, &b);
		printf("scan: %d", scan);
		if (scan != 6)
			break;
		printf("%c %f %f %f %f %c\n", a, c, d, e, f, b);
	}
}
