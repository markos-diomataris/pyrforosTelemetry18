#ifndef PROTOCOL_H
#define PROTOCOL_H


/*
 * handle the interrupt , switch listening port, get data etc
 */
  void interrupt_handler();
 
/*
   we have two serial ports, one for piccolo and one for gps
   we are allways listening at the GPS port but when INTerrupt occurs
   we switch to the piccolo port
*/
class Protocol {
  public:

};

#endif
