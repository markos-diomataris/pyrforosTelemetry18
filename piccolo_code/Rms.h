/*
 * Rms.h
 *
 *  Created on: May 31, 2018
 *      Author: markos
 */

#ifndef RMS_H_
#define RMS_H_

#include "DSP28x_Project.h" //has types
#include "DigitalFilters.h"

#define RMS_BUF_SIZE 100

/*
 * Union of RMS Caltulation state
 */
enum RMS_STATE {BEING_CALCED=0,ACCUMULATING};

/*
 * calculate rms for a buffer
 */
SIGNAL_TYPE rms(SIGNAL_TYPE * buff);



#endif /* RMS_H_ */
