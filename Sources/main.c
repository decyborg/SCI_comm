#include <hidef.h> /* for EnableInterrupts macro */
#include "derivative.h" /* include peripheral declarations */
#include "MagniV_API.h"
#include "communication.h"

#define BUSCLK	25000000
int mess_point = 0;
char mess_flag = 0;
char received_message[MESS_MAX_LENGTH];

void main(void) {
	char user_name[USERNAME_MAX_LENGTH];
	char message2send[MESS_MAX_LENGTH];
	
	clock_init(BUSCLK);
	EnableInterrupts;
	/* include your code here */
	sci_init(115200, BUSCLK, SCI0);
	send_string("Insert user name, press enter to send: \n\r", SCI0);
	get_username(SCI0, user_name);
	send_string("\n\rYour user name is: \n\r", SCI0);
	send_string(user_name, SCI0);
	send_string("\n\rTo use this terminal simply write your message and press enter to send it\n\r", SCI0);
	sci_init(115200, BUSCLK, SCI1);
	SCI1CR2_RIE = 1;	/* Enable receive interrupt */
	
	for(;;) {
		get_message(SCI0, message2send);
		send_message(SCI0, SCI1, user_name, message2send);
	} /* loop forever */
	/* please make sure that you never leave main */

}

interrupt VectorNumber_Vsci1 void SCI1_ISR(){
	int tmp_reg = SCI1SR1; /* Read register */
	char tmp = SCI1DRL;
	if(tmp != '\r'){
		if(mess_point < MESS_MAX_LENGTH - 3){		/* Maximum length minus terminating sequence \r\a NULL */ 
			received_message[mess_point++] = tmp;	/* Write character and advance buffer pointer */
		} else{
			received_message[mess_point++] = '\r';	/* Write carriage return and advance buffer pointer */	
			received_message[mess_point++] = '\a';	/* Concatenate beep at end of string and advance buffer pointer */
			received_message[mess_point] = 0;		/* End message with NULL character */
			mess_point = 0;							/* Reset buffer pointer */
			send_string(received_message, SCI0);		/* Send received message to terminal */
		}
	} else{
		received_message[mess_point++] = '\r';		
		received_message[mess_point++] = '\a';		/* Concatenate beep at end of string */
		received_message[mess_point] = 0;			/* End message with NULL character */
		mess_point = 0;								/* Reset buffer pointer */
		send_string(received_message, SCI0);		/* Send received message to terminal */
	}
}
