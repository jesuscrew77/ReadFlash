#include <math.h>

#define PI    3.141592653589793
#define PI_2  6.283185307179587
#define RTD   57.29577951308232  /* RTD degries in 1 radian: 180/pi */
#define RTM	  3437.746770784939  /* RTM minuts in 1 radian:  60*180/pi */
#define RTS   206264.8062470964  /* RTS seconds in 1 radian: 3600*180/pi */

double sqrtm(double xf);
double acosm(double xf);
double asinm(double xf);
double atan2m(double yf, double xf);
void quatToMatr(const double Quat[], double M_ornt[3][3]);
void MatrixToEkvAngles(const double Matrix[3][3], double Angles[3]);
