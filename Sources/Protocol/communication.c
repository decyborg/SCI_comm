/*
 * communication.c
 *
 *  Created on: Sep 3, 2015
 *      Author: B52932
 */
#include "communication.h"

/**	Gets the username and stores it
 * 
 * @param sci_channel 	SCI channel connected to terminal used to get the user name
 * @param sci_channel	store_string String used to store the user name
 * */
void get_username(unsigned int sci_channel, char* store_string){
	int i;
	char tmp;
	for(i = 0; i < USERNAME_MAX_LENGTH - 1; ++i){
		tmp = get_char(sci_channel);
		put_char(tmp, sci_channel);
		if((tmp == '\n') | (tmp == '\r')){
			store_string[i] = 0;
			return;
		} else if (tmp == '\b'){
			i -= 2;					/* Go back current character '\b' and previous to overwrite it */
			put_char(' ', sci_channel);	/* Blank space to overwrite previous character in terminal */
			put_char('\b', sci_channel);	/* Go Back again */
		} else {
			store_string[i] = tmp;
		}
	}
	store_string[USERNAME_MAX_LENGTH] = 0;
}

/** Gets the message to send
 * 
 * @param	sci_channel	SCI channel connected to terminal used to get the message
 * @param store _string String that will store the message
 * */
void get_message(unsigned int sci_channel, char* store_string){
	int i;
	char tmp;
	for(i = 0; i < MESS_MAX_LENGTH - 1; ++i){		/* Maximum length minus NULL character */
		tmp = get_char(sci_channel);
		put_char(tmp, sci_channel);						/* Echo to terminal */
		if((tmp == '\n') | (tmp == '\r')){			/* End of message */
			store_string[i] = 0;
			return;
		} else if (tmp == '\b'){	/* Delete character */
			i -= 2;					/* Go back current character '\b' and previous to overwrite it */
			put_char(' ', sci_channel);	/* Blank space to overwrite previous character in terminal */
			put_char('\b', sci_channel);	/* Go Back again */
		} else {					/* Maximum length reached terminate message */
			store_string[i] = tmp;
			store_string[USERNAME_MAX_LENGTH] = 0;
		}
	}	
}

/** Sends the message
 *  Echoes the message to the terminal and sends it to the network
 *  
 *  @param sci_channel_terminal	SCI_channel used to communicate with the terminal
 *  @param sci_channel_network	SCI channel used to communicate with the network
 *  @param user_name	User name used to send the message
 *  @param message	Message to be send
 * */
void send_message(unsigned int sci_channel_terminal, unsigned int sci_channel_network, char* user_name, char* message){
	/* Echo to terminal */
	send_string(user_name, SCI0);
	send_string(" says: ", SCI0);
	send_string(message, SCI0);
	send_string("\n\r", SCI0);
	/* Send to another device */
	send_string(user_name, SCI1);
	send_string(" says: ", SCI1);
	send_string(message, SCI1);
	send_string("\n\r", SCI1);
}
