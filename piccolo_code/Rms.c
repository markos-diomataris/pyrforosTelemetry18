/*
 * Rms.c
 *
 *  Created on: May 31, 2018
 *      Author: markos
 */


#include "Rms.h"
#include "math.h"

int16_t rms(int16_t * buff){

    int i;
    double acc=0;
    for(i=0;i<RMS_BUF_SIZE;i++){
        acc += (*(buff+i))* (*(buff+i));
    }

    return (int)sqrt(acc/(double)RMS_BUF_SIZE);
}
