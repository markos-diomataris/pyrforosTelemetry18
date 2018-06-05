#include "DigitalFilters.h"

//#include "IQmathCPP.h"
/*
 * DigitalFilters.c
 *
 *  Created on: May 25, 2018
 *      Author: markos
 */



/*
 *       SECOND ORDER DIRECT FORM II KERNEL
 *                  w[n]
 *  x[n]--->+---->---.----b0---+--g-->y[n]
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
    SIGNAL_TYPE out=_IQmpy(input,_IQ(0.5)),temp,temp1,temp2,temp3;
    for(i=0;i<S;i++){
        temp1 = _IQmpy(f->a[i][1],f->w[i][1]);
        temp2 = _IQmpy(f->a[i][2],f->w[i][2]);
        f->w[i][0] = out + temp1 + temp2;
        temp1=_IQmpy(f->b[i][0],f->w[i][0]);
        temp2=_IQmpy(f->b[i][1],f->w[i][1]);
        temp3=_IQmpy(f->b[i][2],f->w[i][2]);
        temp= temp1 + temp2 + temp3;
        out = _IQmpy(temp,f->g[i]);
        f->w[i][2] = f->w[i][1];
        f->w[i][1] = f->w[i][0];
    }
    return out;
}

/*
 *
 */

int16_t mov_avg(int16_t * x,uint8_t w,uint8_t pos){
    uint8_t i=0;
    int16_t acc=0,ret;
    _iq temp;
    for(i=0;i<w;i++){
        acc = acc + *(x+pos);
        pos = (pos == 0) ? 99 : pos-1;
    }
    temp=_IQ((float)acc);
    temp = _IQdiv(temp,_IQ((float)w));
    return (int16_t)_IQtoF(temp);
}
