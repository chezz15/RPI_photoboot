#include "wiringPi.h"
#include "button_lib.h"
#include <iostream>
#include <QDebug>

#define SWITCH_PIN 1

int lib_init()
{
	return wiringPiSetup();
}

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
