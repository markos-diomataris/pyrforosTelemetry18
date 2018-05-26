/*
 * DigitalFilters.h
 *
 *  Created on: May 25, 2018
 *      Author: markos
 */

#ifndef DIGITALFILTERS_H_
#define DIGITALFILTERS_H_

struct Second_order_filter{
    /*
     * Fixed coefficients
     */
    double a[3];
    double b[3];
    double gain;
    /*
     * filter memory
     */
    double buf[2];
};



/*
 * calculate filters response y[n] given  an input x[n]
 */
double step_filter(struct Second_order_filter * filter, double input);

/*
 * Initialize an DFII filter given a coefficient struct
 */
void init_filter(struct Second_order_filter* filter);

#endif


