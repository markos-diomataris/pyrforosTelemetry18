

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
uint16_t packet;
int16_t curr1[100],curr2[100],volt1[100],volt2[100];
float rms_value;
int16_t rms_plot;
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
            rms_plot = rms(rms_buf_ptr);
            rms_value = SCALE*(float)rms_plot;
            RmsState = ACCUMULATING;
        }

        is_time_to_send = 1;
    }
}


__interrupt void adc_isr(void){
    GPIO_setHigh(myGpio, GPIO_Number_16);
    ADC_Obj *adc = (ADC_Obj*) myAdc;
    curr1[counter] = ((int16_t)(adc->ADCRESULT[0])-OFFSET);
//    curr2[counter] = (int16_t)_IQtoF((stepNotch(&NotchC1, _IQ((float) curr1[counter]))));
    curr2[counter] = mov_avg(curr1, 8, counter);
    volt1[counter] = ((int16_t)(adc->ADCRESULT[1])-OFFSET);
//    curr2[counter] = ((int16_t)(adc->ADCRESULT[2])-OFFSET);
    volt2[counter] = ((int16_t)(adc->ADCRESULT[3])-OFFSET);

    if(RmsState == ACCUMULATING){
        *(rms_buf_ptr + rms_pos++) = (SIGNAL_TYPE) curr2[counter];
    }
    if(rms_pos == RMS_BUF_SIZE){
        rms_pos = 0;
        RmsState = BEING_CALCED;
    }
    //add filter code here//



    //
    if(++counter==100) counter=0;

    if(is_time_to_send == 1){
        GPIO_setHigh(myGpio, GPIO_Number_34);   //trigger interrupt to arduino
        scia_xmit(packet++);
        scia_xmit(42);
        GPIO_setLow(myGpio, GPIO_Number_34);
        is_time_to_send=0;
    }
    // Acknowledge interrupt to PIE
    PIE_clearInt(myPie, PIE_GroupNumber_10);
    GPIO_setLow(myGpio, GPIO_Number_16);
    return;
}
//
// End of File
//
