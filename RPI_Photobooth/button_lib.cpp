#include "wiringPi.h"
#include "button_lib.h"
#include <iostream>
#include <QDebug>

#define SWITCH_PIN 1

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
  qDebug() << callback;

  pinMode(SWITCH_PIN, INPUT);
  pullUpDnControl (SWITCH_PIN, PUD_UP);	
	
	
  if ( wiringPiISR (SWITCH_PIN, INT_EDGE_FALLING, callback) < 0 ) {
      return 1;
  }	

  return 0;
}
