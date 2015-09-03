/*
 * communication.c
 *
 *  Created on: Sep 3, 2015
 *      Author: B52932
 */
#include "communication.h"

/**	Gets the username and stores it
 * 
 * */
void get_username(unsigned int sci_channel, char* store_string){
	int i;
	char tmp;
	for(i = 0; i < USERNAME_MAX_LENGTH - 1; ++i){
		tmp = get_char(SCI0);
		put_char(tmp, SCI0);
		if((tmp == '\n') | (tmp == '\r')){
			store_string[i] = 0;
			return;
		} else if (tmp == '\b'){
			i -= 2;					/* Go back current character '\b' and previous to overwrite it */
			put_char(' ', SCI0);	/* Blank space to overwrite previous character in terminal */
			put_char('\b', SCI0);	/* Go Back again */
		} else {
			store_string[i] = tmp;
		}
	}
	store_string[USERNAME_MAX_LENGTH] = 0;
}

/** Gets the message to send
 * 
 * */
void get_message(unsigned int sci_channel, char* store_string){
	int i;
	char tmp;
	for(i = 0; i < MESS_MAX_LENGTH - 1; ++i){
		tmp = get_char(SCI0);
		put_char(tmp, SCI0);
		if((tmp == '\n') | (tmp == '\r')){
			store_string[i] = 0;
			return;
		} else if (tmp == '\b'){
			i -= 2;					/* Go back current character '\b' and previous to overwrite it */
			put_char(' ', SCI0);	/* Blank space to overwrite previous character in terminal */
			put_char('\b', SCI0);	/* Go Back again */
		} else {
			store_string[i] = tmp;
		}
	}
	store_string[USERNAME_MAX_LENGTH] = 0;	
}

/** Sends the message
 * 
 * */
void send_message(unsigned int sci_channel, char* user_name, char* message){
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
