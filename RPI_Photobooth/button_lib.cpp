#include "wiringPi.h"
#include "button_lib.h"
#include <iostream>
#include <QDebug>

#define SWITCH_PIN  1
#define PIR_PIN     2
/**
 * @brief lib_init
 * @return
 */
int lib_init(void)
{
	return wiringPiSetup();
}

/**
 * @brief button_init
 * @return
 */
int button_init(void (*callback)(void))
{
  pinMode(SWITCH_PIN, INPUT);
  pullUpDnControl (SWITCH_PIN, PUD_UP);	
	
	
  if ( wiringPiISR (SWITCH_PIN, INT_EDGE_FALLING, callback) < 0 ) {
      return 1;
  }	

  return 0;
}

/**
 * @brief PIR_init
 * @return
 */
int PIR_init(void (*callback)(void))
{
  pinMode(PIR_PIN, INPUT);
  pullUpDnControl (PIR_PIN, PUD_DOWN);


  if ( wiringPiISR (PIR_PIN, INT_EDGE_RISING, callback) < 0 ) {
      return 1;
  }

  return 0;
}
