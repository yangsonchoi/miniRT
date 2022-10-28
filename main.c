#include <stdio.h>

int	main(void)
{
	int x, z;
	double y;

	x = 5;
	z = 2;

	y = (double)x / z;
	printf("double : %f, int : %d\n", y, x);
}
