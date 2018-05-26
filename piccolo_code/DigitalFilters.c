#include "DigitalFilters.h"
/*
 * DigitalFilters.c
 *
 *  Created on: May 25, 2018
 *      Author: markos
 */

double step_filter(struct Second_order_filter * filter, double input){
    double u1,u2,u3;
    u2 = -filter->a[1]*(filter->buf[0])
         - filter->a[2]*(filter->buf[1]);

    u1 = input + u2;

    u3 = filter->b[1]*(filter->buf[0])
         +filter->b[2]*(filter->buf[1]);

    filter->buf[1]=filter->buf[0];
    filter->buf[0]=u2;

    return filter->gain*(u1*(filter->b[0]) + u3);
}

void init_filter(struct Second_order_filter* filter){
    filter->buf[0] = filter->buf[1] = 0;

    return;
}


