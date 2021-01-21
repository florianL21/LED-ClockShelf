#include "misc.h"
double easeInOutCubic(double x)
{
	if(x < 0.5)
	{
		return 4 * x * x * x;
	}
	else
	{
		return 1 - pow(-2 * x + 2, 3) / 2;
	}
}

double map_float(double x, double in_min, double in_max, double out_min, double out_max)
{
    double divisor = (in_max - in_min);
    if(divisor == 0){
        return -1; //AVR returns -1, SAM returns 0
    }
    return (x - in_min) * (out_max - out_min) / divisor + out_min;
}

int SortFunction_SmallerThan(uint16_t &a, uint16_t &b)
{
	return a < b;
}