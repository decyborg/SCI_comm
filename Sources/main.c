#include <hidef.h> /* for EnableInterrupts macro */
#include "derivative.h" /* include peripheral declarations */
#include "MagniV_API.h"
#include "communication.h"

#define BUSCLK	25000000


void main(void) {
	char user_name[USERNAME_MAX_LENGTH];
	
	clock_init(BUSCLK);
	EnableInterrupts;
	/* include your code here */
	sci_init(115200, BUSCLK, SCI0);
	send_string("Insert user name, press enter to send: \n\r", SCI0);
	get_username(SCI0, user_name);
	send_string("\n\rYour user name is: \n\r", SCI0);
	send_string(user_name, SCI0);
	
	for(;;) {
		echo(SCI0);
	} /* loop forever */
	/* please make sure that you never leave main */

}
