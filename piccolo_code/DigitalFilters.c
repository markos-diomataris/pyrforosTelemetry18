#include "DigitalFilters.h"
/*
 * DigitalFilters.c
 *
 *  Created on: May 25, 2018
 *      Author: markos
 */





/*
 *       SECOND ORDER DIRECT FORM II
 *                  w[n]
 *  x[n]--->+---->---.----b0---+----->y[n]
 *          ^        |         ^
 *          |       1/z        |
 *          |        |         |
 *          |        v         |
 *          +<--a1--mem0--b1-->+
 *          ^        |         ^
 *          |       1/z        |
 *          |        |         |
 *          |        v         |
 *          |<--a2--mem1--b2-->|
 *
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



