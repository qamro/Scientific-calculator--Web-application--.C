#include "func.h"


#define PI 3.141592653589793
#define E  2.718281828459045

int mode_rad = 1;  // 1 = RAD, 0 = DEG

// BASIC 

double add(double a, double b){
  double s;
  s = a+b;
  return s;

}


double sub(double a, double b){
  double s;
  s = a-b;
  return s;

}


double mul(double a, double b){

  double m;
  m = a*b;
  return m;

}


double div(double a, double b){

  double d;
  d = a/b;
  return d;

}

// Percent

double percent(double total, double p){

    return (total * p) / 100;
}

// POWER OF 2

double square(double x){

    return x * x;
}

// Floor

int floor_custom(double x){

    int n = (int)x;

    if (x < 0 && x != n)

    return n - 1; 

    else

    return n;
}

// Ceil

int ceil_custom(double x){

    int n = (int)x; 

    if (x > n)

     return n + 1;

    else

     return n;

}

// POWER

double power(double x, int n) {
    double r = 1.0;
    for (int i = 0; i < n; i++) r *= x;
    return r;
}

// Factorial
int factorial(int n) {
    if (n < 0) return 1;
    int r = 1;
    for (int i = 1; i <= n; i++) r *= i;
    return r;
}


double abs_t(double x) {
    return (x < 0) ? -x : x;
}

// SQRT (Newton Method)

double sqrt_t(double x) {
    double r = x;
    for (int i = 0; i < 25; i++)
        r = 0.5 * (r + x / r);
    return r;
}

// Cube ROOT (Newton Method)

double cbrt_custom(double a)
{
    double x = a;
    double eps = 0.000001;

    if (a == 0)
        return 0;

    while ((x * x * x - a > eps) || (a - x * x * x > eps))
    {
        x = (2 * x + a / (x * x)) / 3;
    }

    return x;
}

// EXP (MERACTOR SERIES)

double exp_t(double x) {
    double s = 1.0;
    for (int n = 1; n < 15; n++)
        s += power(x, n) / factorial(n);
    return s;
}

// LN (Mercator Series)

double ln_t(double x) {
    double y = (x - 1) / (x + 1);
    double s = 0.0;
    for (int n = 0; n < 25; n++)
        s += power(y, 2*n + 1) / (2*n + 1);
    return 2 * s;
}

// TRIG (TAYLOR series) 

double sin_t(double x) {
    double s = 0.0;
    for (int n = 0; n < 12; n++)
        s += power(-1, n) * power(x, 2*n + 1) / factorial(2*n + 1);
    return s;
}

double cos_t(double x) {
    double s = 0.0;
    for (int n = 0; n < 12; n++)
        s += power(-1, n) * power(x, 2*n) / factorial(2*n);
    return s;
}

double tan_t(double x) {
    return sin_t(x) / cos_t(x);
}

// ARCS 

double arctan_t(double x) {
    double s = 0.0;
    for (int n = 0; n < 20; n++)
        s += power(-1, n) * power(x, 2*n + 1) / (2*n + 1);
    return s;
}

double arcsin_t(double x) {
    return arctan_t(x / sqrt_t(1 - x*x));
}

double arccos_t(double x) {
    return (PI/2) - arcsin_t(x);
}

// MODE 

double to_radians(double x) {
    if (mode_rad) return x;
    return x * PI / 180.0;
}