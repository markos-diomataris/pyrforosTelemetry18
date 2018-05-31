/*
 * Rms.c
 *
 *  Created on: May 31, 2018
 *      Author: markos
 */


#include "Rms.h"
#include "math.h"

SIGNAL_TYPE rms(SIGNAL_TYPE * buff){

    int i;
    SIGNAL_TYPE acc=0;
    for(i=0;i<RMS_BUF_SIZE;i++){
        acc += (*(buff+i))* (*(buff+i));
    }

    return sqrt(acc/(double)RMS_BUF_SIZE);
}
