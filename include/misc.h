#ifndef __MISC_H_
#define __MISC_H_

#include <Arduino.h>

double map_float(double x, double in_min, double in_max, double out_min, double out_max);
double easeInOutCubic(double x);
int SortFunction_SmallerThan(uint16_t &a, uint16_t &b);

#endif