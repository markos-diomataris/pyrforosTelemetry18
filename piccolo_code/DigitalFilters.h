/*
 * DigitalFilters.h
 *
 *  Created on: May 25, 2018
 *      Author: markos
 */

#ifndef DIGITALFILTERS_H_
#define DIGITALFILTERS_H_

struct coeffs_DF2{
    double a0;
    double a1;
    double a2;
    double b0;
    double b1;
    double b2;
    double gain;
};

struct state{
    double mem1;
    double mem2;
};

struct filter_DF2{
    struct coeffs_DF2 coeffs;
    struct state mem;
};

double step_filter(struct filter_DF2 * filter, double input);


#endif


