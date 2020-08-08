#ifndef PRINT_H
# define PRINT_H

#include "vector.h"
#include "spheric.h"
#include "math.h"
#include <stdio.h>

void 	print_vect(t_vect *v);
void 	print_vect_sph(t_spheric *v);
void 	print_angle(double phi, double theta);

#endif
