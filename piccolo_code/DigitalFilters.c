#include "DigitalFilters.h"
/*
 * DigitalFilters.c
 *
 *  Created on: May 25, 2018
 *      Author: markos
 */

double step_filter(struct Second_order_filter * filter, double input){
    double u1,u2,u3;
    u2 = -filter->coeffs.a[1]*(filter->mem.buf[0])
         - filter->coeffs.a[2]*(filter->mem.buf[1]);

    u1 = input + u2;

    u3 = filter->coeffs.b[1]*(filter->mem.buf[0])
         +filter->coeffs.b[2]*(filter->mem.buf[1]);

    filter->mem.buf[1]=filter->mem.buf[0];
    filter->mem.buf[0]=u2;

    return filter->coeffs.gain*(u1*(filter->coeffs.b[0]) + u3);
}

void init_filter(struct Second_order_filter* filter, struct coeffs_DF2 coeffs){
    filter->mem.buf[0] = filter->mem.buf[1] = 0;
    filter->coeffs = coeffs;
    return;
}


