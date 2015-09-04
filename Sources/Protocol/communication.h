/*
 * communication.h
 *
 *  Created on: Sep 3, 2015
 *      Author: B52932
 */

#ifndef COMMUNICATION_H_
#define COMMUNICATION_H_
#include "MagniV_API.h"

#define USERNAME_MAX_LENGTH 	10
#define MESS_MAX_LENGTH			144

/* Prototypes */
void get_username(unsigned int sci_channel, char* store_string);
void send_message(unsigned int sci_channel_terminal, unsigned int sci_channel_network, char* user_name, char* message);
void get_message(unsigned int sci_channel, char* store_string);

#endif /* COMMUNICATION_H_ */
