

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
#include "IQmathLib.h"

#include "DigitalFilters.h"
#include "Initialization.h"
#include "Communication.h"
#include "Rms.h"

/*
 * defines
 */
#define OFFSET 0x07CD
#define SCALE 0.01785714 //heavily depends on boards op-amp gains
#define BUFFERS_SIZE 20 // !! change also ad DigialFilters.c
/*
 * Function Prototypes
 */
__interrupt void adc_isr(void);

/*
 * Globals
 */
uint8_t counter=0;
volatile uint8_t is_time_to_send = 0;
volatile uint8_t is_time_to_rms =0;
int16_t *rms_buf_ptr;
uint16_t rms_pos=0;
int16_t curr1[BUFFERS_SIZE],curr2[BUFFERS_SIZE],volt1[BUFFERS_SIZE],volt2[BUFFERS_SIZE];
float rms_value;
int16_t rms_send;
int16_t pow_send;
/*
 * enums
 */
enum RMS_STATE RmsState = ACCUMULATING;
/*
 * Handler pointers
 */
ADC_Handle myAdc;
CLK_Handle myClk;
FLASH_Handle myFlash;
GPIO_Handle myGpio;
PIE_Handle myPie;
PWM_Handle myPwm;
SCI_Handle mySci;
CPU_Handle myCpu;
PLL_Handle myPll;
WDOG_Handle myWDog;


/*
 * externals
 */
extern struct NotchFilter_DF2 NotchC1;

/*
 * Main
 */
void main(void){
    int16_t rms_array[RMS_BUF_SIZE];
    rms_buf_ptr = rms_array;

    initialize();

    for(;;){
        DELAY_US(100000);

        if(RmsState == BEING_CALCED){
            rms_send = rms(rms_buf_ptr);
            rms_value = SCALE*(float)rms_send;
            RmsState = ACCUMULATING;
        }
        /*
         * send measurements to arduino
         */
        GPIO_setHigh(myGpio, GPIO_Number_34);   //trigger interrupt to arduino
        scia_xmit(rms_send);
        scia_xmit(rms_send>>8);

        scia_xmit(pow_send);
        scia_xmit(pow_send>>8);
        GPIO_setLow(myGpio, GPIO_Number_34);
        //
//        is_time_to_send=0;

//        is_time_to_send = 1;
    }
}


int16_t cur1_filt,cur2_filt,volt1_filt,volt2_filt;
__interrupt void adc_isr(void){
    GPIO_setHigh(myGpio, GPIO_Number_16);
    ADC_Obj *adc = (ADC_Obj*) myAdc;
    curr1[counter] = ((int16_t)(adc->ADCRESULT[0])-OFFSET);
    curr2[counter] = ((int16_t)(adc->ADCRESULT[1])-OFFSET);
    volt1[counter] = ((int16_t)(adc->ADCRESULT[2])-OFFSET);
    volt2[counter] = ((int16_t)(adc->ADCRESULT[3])-OFFSET);

//    cur1_filt=mov_avg(curr1, 5, counter);
//    cur2_filt=mov_avg(curr2, 5, counter);
//    volt1_filt=mov_avg(volt1, 5, counter);
//    volt2_filt=mov_avg(volt2, 5, counter);

        cur1_filt=curr1[counter];
        cur2_filt=curr2[counter];
        volt1_filt=volt1[counter];
        volt2_filt=volt2[counter];

    pow_send = cur1_filt*volt1_filt + cur2_filt*volt2_filt;

    if(RmsState == ACCUMULATING){
        *(rms_buf_ptr + rms_pos++) = mov_avg(curr1, 20, counter);
    }
    if(rms_pos == RMS_BUF_SIZE){
        rms_pos = 0;
        RmsState = BEING_CALCED;
    }

    if(++counter==BUFFERS_SIZE) counter=0;
    // Acknowledge interrupt to PIE
    PIE_clearInt(myPie, PIE_GroupNumber_10);
    GPIO_setLow(myGpio, GPIO_Number_16);
    return;
}
//
// End of File
//
