/*
 * Rms.c
 *
 *  Created on: May 31, 2018
 *      Author: markos
 */


#include "Rms.h"
//#include "math.h"

int16_t rms(int16_t * buff){

    int i;
    int32_t acc=0;
    int16_t ret;
    for(i=0;i<RMS_BUF_SIZE;i++){
        acc += (int32_t)(*(buff+i))* (*(buff+i));
    }
    _iq acc_iq =_IQ((float)acc),root;
    root = _IQsqrt(_IQdiv(acc_iq,_IQ((float)RMS_BUF_SIZE)));
    ret = (int16_t)_IQtoF(root);
    return ret;
}
