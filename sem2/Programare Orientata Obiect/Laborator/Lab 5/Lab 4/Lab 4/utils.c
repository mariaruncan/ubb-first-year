#include "utils.h"

#include <math.h>
#include <string.h>

const double EPSILON = 0.0001;

int double_equ(double a, double b)
{
	if (fabs(a - b) < EPSILON)
		return 1;
	return 0;
}

int str_equ(char* a, char* b)
{
	if (strcmp(a, b) == 0)
		return 1;
	return 0;
}
