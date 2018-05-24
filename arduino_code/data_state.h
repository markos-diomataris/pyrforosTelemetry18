#ifndef DATA_STATE_H
#define DATA_STATE_H

#include<SD.h>
#include<SPI.h>

/*
   this class holds/buffers the last measurements sent by the piccolo in
   chronological order, data from the GPS, other measurements and
   is updated when an interrupt ocurrs from the piccolo.
*/

#define BUFF_SIZE 32 //size of data buffers, size matters !!!THIS DETERMINES DYNAMIC MEMORY REMAINING!!!
#define NEW_DATA_INT_PIN 2 //can be 2 or 3
#define SD_SELECT 8 //select pin for sd card
enum BUFF_STATE {FLOP = 0 , FLIP};
enum UPDATE {FLUSHFLOP = 0, FLUSHFLIP, NOFLUSH};
/*
   typical flip buffer structure, when the one fills, flush it while using the other
*/
struct buffers {
  uint16_t flop[BUFF_SIZE];
  uint16_t flip[BUFF_SIZE];
};

/*
   hold the last gps location
*/
struct COORDINATES {
  double x;
  double y;
};
struct G_P_S {
  struct COORDINATES coord;
};

class Data_state {
  public:

    Data_state() {
      b_state = FLOP;
      need_to_flush = NOFLUSH;
      b_pos = 0;
    }

    /*
       we use flip buffers to prevent reading data from buffers
       while updating them
    */
    volatile enum BUFF_STATE b_state; //is it flop or flip ?
    volatile enum UPDATE need_to_flush;
    volatile unsigned int b_pos; //position of buffers next write location , (b_pos -1) or 0 is the last measurment
    volatile struct buffers current; //rms current buffers of a mottors' phase
    volatile struct buffers power; //rms power buffers of the motor
    struct G_P_S gps; //last gps location


    uint16_t get_last_current();
    uint16_t get_last_power(); // get the most fresh data to update the lcd (?)
    struct COORDINATES* get_last_gps(); // get the most fresh data from gps (pointer to COORDINATES struct

    int update_measurments(uint16_t c /*current*/, uint16_t p /*power*/); // get new values from piccolo, trigger SD flush if needed, flip buffers ?
    int update_gps(double x, double y);

    int flush_to_SD(File * filp, enum BUFF_STATE buffer);

};





#endif //data_state.h 

