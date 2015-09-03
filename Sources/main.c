#include <hidef.h> /* for EnableInterrupts macro */
#include "derivative.h" /* include peripheral declarations */
#include "MagniV_API.h"

#define BUSCLK	25000000


void main(void) {
	char* user_name;
	
	clock_init(BUSCLK);
	EnableInterrupts;
	/* include your code here */
	sci_init(115200, BUSCLK, SCI0);
	send_string("Insert user name, press enter to send: \n\r", SCI0);
	
	for(;;) {
		echo(SCI0);
	} /* loop forever */
	/* please make sure that you never leave main */

}
