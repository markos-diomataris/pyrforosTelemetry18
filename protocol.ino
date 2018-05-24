#include"protocol.h"
int counter = 0;
void interrupt_handler() {
//  Serial.println("interrupt");
//  Serial_piccolo.listen();
  uint16_t c;
  uint16_t p;

  //wait for incoming data
//  while(!Serial_piccolo.available()){;}
  if (Serial_piccolo.available()) {
    c = Serial_piccolo.read();
    p = Serial_piccolo.read();
//    Serial.print(String(c) + " , ");
//    Serial.print(String(p) + " , ");
    
  }
//  Serial_piccolo.flush();
  state.update_measurments(c, p); //update buffer states
//  Serial_gps.listen();
}

