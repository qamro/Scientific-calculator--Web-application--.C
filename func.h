#ifndef FUNC_H
#define FUNC_H

#include <math.h>

// Basic functions

double add(double a, double b);
double sub(double a, double b);
double mul(double a, double b);
double div(double a, double b);
double percent(double total, double p);
double square(double x);
int floor_custom(double x);
int ceil_custom(double x);
double power(double x, int n);
int factorial(int n);
double abs_t(double x);
double sqrt_t(double x);
double cbrt_custom(double a);
double exp_t(double x);
double ln_t(double x);
double sin_t(double x);
double cos_t(double x);
double tan_t(double x);
double arctan_t(double x);
double arcsin_t(double x);
double arccos_t(double x);

// MODE function

double to_radians(double x);

#endif 