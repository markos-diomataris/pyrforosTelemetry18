/*
 * Communication.h
 *
 *  Created on: May 26, 2018
 *      Author: markos
 */

#ifndef COMMUNICATION_H_
#define COMMUNICATION_H_

void scia_echoback_init(void);
void scia_fifo_init(void);
void scia_xmit(int a);
void scia_msg(char *msg);

#endif /* COMMUNICATION_H_ */
