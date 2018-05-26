/*
 * Initialization.h
 *
 *  Created on: May 26, 2018
 *      Author: markos
 */

#ifndef INITIALIZATION_H_
#define INITIALIZATION_H_


#include "DSP28x_Project.h"     // Device Headerfile and Examples Include File
#include "common/include/adc.h"
#include "common/include/clk.h"
#include "common/include/flash.h"
#include "common/include/gpio.h"
#include "common/include/pie.h"
#include "common/include/pll.h"
#include "common/include/pwm.h"
#include "common/include/wdog.h"
#include "common/include/sci.h"


void initialize();
extern void scia_echoback_init(void);
extern void scia_fifo_init(void);
extern __interrupt void adc_isr(void);
extern ADC_Handle myAdc;
extern CLK_Handle myClk;
extern FLASH_Handle myFlash;
extern GPIO_Handle myGpio;
extern PIE_Handle myPie;
extern PWM_Handle myPwm;
extern SCI_Handle mySci;
extern CPU_Handle myCpu;
extern PLL_Handle myPll;
extern WDOG_Handle myWDog;


void initialize();

#endif /* INITIALIZATION_H_ */
