#include "print.h"

double	to_radian(double degree)
{
	return (degree * M_PI / 180.);
}

double	to_degree(double radian)
{
	return (radian * 180. / M_PI);
}

void print_vect(t_vect *v)
{
	printf("%lf, %lf, %lf\n", v->x, v->y, v->z);
}

void print_vect_sph(t_spheric *v)
{
	printf("%lf, %lf, %lf\n", v->rho, to_degree(v->phi), to_degree(v->theta));
}      

void print_angle(double phi, double theta)
{
	printf("phi = %lf, theta = %lf\n", to_degree(phi), to_degree(theta));
}
