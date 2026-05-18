#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define PI 3.14159265358979323846
#define E  2.71828182845904523536

int modeDeg = 1; // 1=DEG, 0=RAD

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

//change mod between deg and rad 
double degToRad(double deg){ return deg*PI/180.0; }
double radToDeg(double rad){ return rad*180.0/PI; }


//absolute value
double abs_custom(double x){ return (x<0)? -x:x; }


//know if it is integer 
bool is_integer(double x) { return (x == (int)x);}  

//squar root 

double sqrt_custom(double x){
    if(x<0) return -9999;
    double g=x/2, eps=1e-9;
    if(x==0) return 0;
    while(abs_custom(g*g-x)>eps) g=(g+x/g)/2;
    return g;
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

//factorial
double factorial_custom(int n){
    if(n<0) return -9999;
    double r=1;
    for(int i=2;i<=n;i++) r*=i;
    return r;
}


//exp 
double exp_custom(double x) {
    double sum = 1.0;
    double term = 1.0;

    for (int i = 1; i < 50; i++) {
        term *= x / i;
        sum += term;
    }
    return sum;
}



//ln
double ln_custom(double x){

    if(x<=0) return -9999;
    double y=(x-1)/(x+1), y2=y*y, sum=y, term=y;
    for(int n=3;n<100;n+=2){ term*=y2; sum+=term/n; }
    return 2*sum;
}

//log
double log_custom(double x){ 
    if(x<=0) return -9999;
    return ln_custom(x)/ln_custom(10.0); 
}

//the power

double power(double base, double exp) {

    //the BASE NEGATIV AND the exp ix float 
    if (base < 0 && !is_integer(exp)) return -9999;
  

   // the base is negativ and the exp is integer    
    if (base < 0) {

        double r = 1;
        int e = (int)exp;
        int neg = 0;

        if (e < 0) { e = -e; neg = 1; }

        double b = -base; 
        for (int i = 0; i < e; i++) r *= b;
        if (((int)exp) % 2 != 0) r = -r; 
        if (neg) return 1.0 / r;
        return r;
    }

    // the base is positive we will use ln + exp ---
    double ln_base = ln_custom(base);
    double result = exp_custom(exp * ln_base);
    return result;
    
}






//sin
double sin_custom(double x){
    double term=x,sum=x;
    for(int n=1;n<20;n++){
        term=-term*x*x/(2*n*(2*n+1));
        sum+=term;
    }
    return sum;
}

//cos
double cos_custom(double x){
    double term=1,sum=1;
    for(int n=1;n<20;n++){
        term=-term*x*x/(2*n*(2*n-1));
        sum+=term;
    }
    return sum;
}
//tan
double tan_custom(double x){
    double c=cos_custom(x);
    //it is undifined 
    if(c==0) return -9999;
    return sin_custom(x)/c;
}

//arcsin
double arcsin_custom(double x){
    if(x<-1 || x>1) return -9999;
    double sum=x,term=x;
    for(int n=1;n<20;n++){
        term=term*x*x*(2*n-1)/(2*n);
        sum+=term/(2*n+1);
    }
    return sum;
}


//arccos
double arccos_custom(double x){ return PI/2 - arcsin_custom(x); }
double arctan_custom(double x){
    double sum=0,term=x;
    for(int n=0;n<20;n++){
        if(n>0) term=-term*x*x*(2*n-1)/(2*n+1);
        sum+=term;
    }
    return sum;
}

//the constant
double parseNumber(const char* str){
    if(strcmp(str,"PI")==0) return PI;
    if(strcmp(str,"E")==0) return E;
    if(strcmp(str,"i")==0) return 0;
    return atof(str);
}










int main(void){
    char *data = getenv("QUERY_STRING");
    if(!data){ printf("Content-type: text/html\n\nNo input"); return 0; }

    char a_str[50],b_str[50],op[20],mode[10]="";
    sscanf(data,"a=%49[^&]&b=%49[^&]&op=%19[^&]&mode=%9s",a_str,b_str,op,mode);


    //to chang between deg and rad
    if(strcmp(mode,"deg")==0) modeDeg=1;
    else modeDeg=0;

    double a=parseNumber(a_str);
    double b=parseNumber(b_str);
    double result = 0;



//to calculate

if(strcmp(op,"add")==0) result = a + b;
else if(strcmp(op,"sub")==0) result = a - b;
else if(strcmp(op,"mul")==0) result = a * b;
else if(strcmp(op,"div")==0) {
    if(b == 0) result = -9999;   
    else result = a / b;
}


else if(strcmp(op,"pow")==0) result = power(a, b);
else if(strcmp(op,"sqrt")==0) result = sqrt_custom(a);
else if(strcmp(op,"abs")==0) result = abs_custom(a);
else if(strcmp(op,"ln")==0) result = ln_custom(a);
else if(strcmp(op,"log")==0) result = log_custom(a);
else if(strcmp(op,"exp")==0) result = exp_custom(a);





else if(strcmp(op,"sin")==0) {
    if(modeDeg) a = degToRad(a);
     result = sin_custom(a);
}
else if(strcmp(op,"cos")==0) {
    if(modeDeg) a = degToRad(a);
    result = cos_custom(a);
}
else if(strcmp(op,"tan")==0) {
    if(modeDeg) a = degToRad(a);
    result = tan_custom(a);
}

else if(strcmp(op,"arcsin")==0) {
    result = arcsin_custom(a);
    if(modeDeg) result = radToDeg(result);
}

else if(strcmp(op,"arccos")==0) {
    result = arccos_custom(a);
    if(modeDeg) result = radToDeg(result);
}

else if(strcmp(op,"arctan")==0) {
    result = arctan_custom(a);
    if(modeDeg) result = radToDeg(result);
}

else if(strcmp(op,"fact")==0)
    result = factorial_custom((int)a);

else if(strcmp(op,"i")==0) {
    printf("imaginary number");
    return 0;
}

else {
    printf("Content-type: text/html\n\nUnknown op");
    return 0;
}



printf("Content-type: text/plain\n\n");



if(result == -9999) {
    printf("UNDEFINED");  
} else {
    printf("%lf", result);
}

return 0;

}
