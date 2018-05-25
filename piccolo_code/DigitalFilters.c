#include "DigitalFilters.h"
/*
 * DigitalFilters.c
 *
 *  Created on: May 25, 2018
 *      Author: markos
 */

double step_filter(struct filter_DF2 * filter, double input){
    double u1,u2,u3;
    u2 = -filter->coeffs.a1*(filter->mem.mem1)
         - filter->coeffs.a2*(filter->mem.mem2);
    u1 = input + u2;

    u3 = filter->coeffs.b1*(filter->mem.mem1)
         +filter->coeffs.b2*(filter->mem.mem2);

    return filter->coeffs.gain*(u1*filter->coeffs.b0 + u3);
}




