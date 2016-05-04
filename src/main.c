#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <button_lib.h>

// the event counter 
volatile int eventCounter = 0;

// -------------------------------------------------------------------------
// button_pressed_callback:  called every time the button is pressed
static void button_pressed_callback(void) {
   eventCounter++;
   printf("Button Pressed!\r\n");
}


int main(void) {
  // sets up the wiringPi library
  if (lib_init() < 0) {
      printf ("Unable to setup wiringPi\r\n");
      return 1;
  }

  button_init(button_pressed_callback);
  // set Pin 17/0 generate an interrupt on high-to-low transitions
  // and attach myInterrupt() to the interrupt

  printf( "Wait for button to be pressed..\n\r" );
  // display counter value every second.
  while ( 1 ) {
  }

  return 0;
}