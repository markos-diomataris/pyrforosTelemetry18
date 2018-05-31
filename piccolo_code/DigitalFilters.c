#include "DigitalFilters.h"
/*
 * DigitalFilters.c
 *
 *  Created on: May 25, 2018
 *      Author: markos
 */





/*
 *       SECOND ORDER DIRECT FORM II KERNEL
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


SIGNAL_TYPE stepNotch(struct NotchFilter_DF2 * f,COEFF_TYPE input){
    uint8_t i;
    uint8_t S = f->stages;
    SIGNAL_TYPE temp=input;
    for(i=0;i<S;i++){
        f->w[i][0] = temp + f->a[i][1]*f->w[i][1] + f->a[i][2]*f->w[i][2];
        temp = f->g[i]*(f->b[i][0]*f->w[i][0] + f->b[i][1]*f->w[i][1] + f->b[i][2]*f->w[i][2]);
        f->w[i][1] = f->w[i][0];
        f->w[i][2] = f->w[i][1];
    }


    return temp;
}
