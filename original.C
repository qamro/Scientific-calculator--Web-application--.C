#include <stdio.h>
#include <stdlib.h>

#define PI 3.141592653589793
#define E  2.718281828459045

int mode_rad = 1;  // 1 = RAD, 0 = DEG

// BASIC OPERATIONS

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

// PARSER 

char expr[600];
int pos = 0;

double parse_expression();

void skip_spaces() {
    while (expr[pos] == ' ') pos++;
}

int match(char c) {
    skip_spaces();
    if (expr[pos] == c) {
        pos++;
        return 1;
    }
    return 0;
}

double parse_number() {
    skip_spaces();
    double r = 0;
    int sign = 1;

    if (match('-')) sign = -1;

    while (expr[pos] >= '0' && expr[pos] <= '9') {
        r = r * 10 + (expr[pos] - '0');
        pos++;
    }

    if (match('.')) {
        double f = 1;
        while (expr[pos] >= '0' && expr[pos] <= '9') {
            f /= 10;
            r += (expr[pos] - '0') * f;
            pos++;
        }
    }

    return sign * r;
}

int starts_with(const char *s) {
    int i = 0;
    int p = pos;
    while (s[i] != '\0') {
        if (expr[p] != s[i]) return 0;
        p++;
        i++;
    }
    return 1;
}

double parse_factor() {
    skip_spaces();

    if (match('(')) {
        double v = parse_expression();
        match(')');
        return v;
    }

    if (starts_with("pi")) { pos+=2; return PI; }
    if (starts_with("e"))  { pos+=1; return E; }

    if (starts_with("sin(")) { pos+=4; double v=parse_expression(); match(')'); return sin_t(to_radians(v)); }
    if (starts_with("cos(")) { pos+=4; double v=parse_expression(); match(')'); return cos_t(to_radians(v)); }
    if (starts_with("tan(")) { pos+=4; double v=parse_expression(); match(')'); return tan_t(to_radians(v)); }

    if (starts_with("asin(")) { pos+=5; double v=parse_expression(); match(')'); return arcsin_t(v); }
    if (starts_with("acos(")) { pos+=5; double v=parse_expression(); match(')'); return arccos_t(v); }
    if (starts_with("atan(")) { pos+=5; double v=parse_expression(); match(')'); return arctan_t(v); }

    if (starts_with("sqrt(")) { pos+=5; double v=parse_expression(); match(')'); return sqrt_t(v); }
     if (starts_with("cube(")) { pos+=5; double v=parse_expression(); match(')'); return cbrt_custom(v); }
    if (starts_with("ln("))   { pos+=3; double v=parse_expression(); match(')'); return ln_t(v); }
    if (starts_with("log("))  { pos+=4; double v=parse_expression(); match(')'); return ln_t(v)/ln_t(10); }
    if (starts_with("exp("))  { pos+=4; double v=parse_expression(); match(')'); return exp_t(v); }
    if (starts_with("abs("))  { pos+=4; double v=parse_expression(); match(')'); return abs_t(v); }
    if (starts_with("floor("))  { pos+=4; double v=parse_expression(); match(')'); return floor_custom(v); }
    if (starts_with("ceil("))  { pos+=4; double v=parse_expression(); match(')'); return ceil_custom(v); }

    return parse_number();
}

double parse_power() {
    double a = parse_factor();
    while (match('^')) {
        double b = parse_factor();
        a = power(a, (int)b);
    }
    while (match('!'))
        a = factorial((int)a);

    return a;
}

double parse_term() {
    double a = parse_power();
    for (;;) {
        if (match('*')) a *= parse_power();
        else if (match('/')) a /= parse_power();
        else return a;
    }
}

double parse_expression() {
    double a = parse_term();
    for (;;) {
        if (match('+')) a += parse_term();
        else if (match('-')) a -= parse_term();
        else return a;
    }
}


// MAIN TEST 

int main() {
    printf("Enter expression: ");
    fgets(expr, 600, stdin);

    pos = 0;
    double r = parse_expression();

    printf("Result = %f\n", r);
    return 0;
}