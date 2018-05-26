/*
 * DigitalFilters.h
 *
 *  Created on: May 25, 2018
 *      Author: markos
 */

#ifndef DIGITALFILTERS_H_
#define DIGITALFILTERS_H_

struct coeffs_DF2{
    double a[3];
    double b[3];
    double gain;
};

struct state{
    double buf[2];
};

struct Second_order_filter{
    /*
     * filter coefficients as in DIRECT FORM II
     */
    struct coeffs_DF2 coeffs;
    /*
     * Filter's memory footprint of a state (what it needs to remember)
     */
    struct state mem;
};



/*
 * calculate filters response y[n] given  an input x[n]
 */
double step_filter(struct Second_order_filter * filter, double input);

/*
 * Initialize an DFII filter given a coefficient struct
 */
void init_filter(struct Second_order_filter* filter, struct coeffs_DF2 coeffs);

#endif


