/*
*	UART communication on Raspberry Pi using C (WiringPi Library)
*	@author: DzhL
*/

#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <stdint.h>
#include <errno.h>
#include <wiringPi.h>
#include <wiringSerial.h>

static uint8_t run;

//Catch Ctrl C
void intHandler(int dummy){
	run = 0;
	printf("\nBye\n");
}



int main ()
{
  int serial_port ;
  char dat;
  run = 1;

  signal(SIGINT, intHandler);

  if ((serial_port = serialOpen ("/dev/ttyS0", 9600)) < 0)		/* open serial port */
  {
    fprintf (stderr, "Unable to open serial device: %s\n", strerror (errno)) ;
    return 1 ;
  }

  if (wiringPiSetup () == -1)							/* initializes wiringPi setup */
  {
    fprintf (stdout, "Unable to start wiringPi: %s\n", strerror (errno)) ;
    return 1 ;
  }

  while(run){

		 if(serialDataAvail (serial_port) )
		  {
		    dat = serialGetchar (serial_port);		/* receive character serially*/
		    printf ("%c", dat) ;
		    fflush (stdout) ;
		    serialPutchar(serial_port, dat);		/* transmit character serially on port */
		  }
	}

}
