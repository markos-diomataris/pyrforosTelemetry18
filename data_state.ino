#include"data_state.h"

/*
   the last value available is in b_pos-1
   if b_pos == 0 then it is in the last position
*/
uint16_t Data_state::get_last_current() {
  if (this->b_state == FLOP) {
    return (this->b_pos == 0) ? this->current.flop[BUFF_SIZE - 1] : this->current.flop[this->b_pos - 1];
  }
  return (this->b_pos == 0) ? this->current.flip[BUFF_SIZE - 1] : this->current.flip[this->b_pos - 1];
}

/*
   the last value available is in b_pos-1
   if b_pos == 0 then it is in the last position
*/
uint16_t Data_state::get_last_power() {
  if (this->b_state == FLOP) {
    return (this->b_pos == 0) ? this->power.flop[BUFF_SIZE - 1] : this->power.flop[this->b_pos - 1];
  }
  return (this->b_pos == 0) ? this->power.flip[BUFF_SIZE - 1] : this->power.flip[this->b_pos - 1];
}


struct COORDINATES* Data_state::get_last_gps() {
  return &this->gps.coord;
}

/*
   just update the gps coordinates
*/
int Data_state::update_gps(double x, double y) {
  this->gps.coord.x = x;
  this->gps.coord.y = y;
  return 0;
}

/*
   update measurements , flip buffers, trigger SD write
*/
int Data_state::update_measurments(uint16_t c /*current*/, uint16_t p /*power*/) {

  if (this->b_state == FLOP) {
    this->current.flop[b_pos] = c;
    this->power.flop[b_pos] = p;
  } else {
    this->current.flip[b_pos] = c;
    this->power.flip[b_pos] = p;
  }

  this->b_pos += 1;

  if (this->b_pos == BUFF_SIZE) { //buffer just filled, switch flip buffers
//    Serial.println("FLIPPED buffer");
    this->b_pos = 0;  //reset buffer pointer
    this->need_to_flush = (this->b_state == FLOP) ? FLUSHFLOP : FLUSHFLIP; //turn on indicator for flushing the apropriate buffer in the main loop
    this->b_state = (this->b_state == FLOP) ? FLIP : FLOP;  //switch buffers
  }


  return 0;
}


/*
   flush the apropriate buffer
*/

int Data_state::flush_to_SD(File * filp, enum BUFF_STATE buf) {
//  Serial.println("flushing");
  uint16_t* c;
  uint16_t* p;
  c = (buf == FLIP) ? this->current.flip : this->current.flop;
  p = (buf == FLIP) ? this->power.flip : this->power.flop;
  int i = 0;
  for (i = 0; i < BUFF_SIZE; i++) {
    filp->println(String(c[i]) + "," + String(p[i]));
//    Serial.println(String(c[i]) + "," + String(p[i]));
    delay(10);
  }
//  Serial.println("done");
  return 0;
}

