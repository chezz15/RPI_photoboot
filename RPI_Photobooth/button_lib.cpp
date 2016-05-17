#include "wiringPi.h"
#include "button_lib.h"
#include <iostream>
#include <QDebug>

#define GPIO1       1
#define GPIO4       4
#define SWITCH_PIN  GPIO1
#define PIR_PIN     GPIO4


/**
RPI PINOUT (WIRINGPI LAYOUT)
 3V3     1|2    5V
 SDA     3|4    5V
 SCL     5|6    GND
 GPIO7   7|8    TxD
 GND     9|10   RxD
 GPIO0  11|12   GPIO1
 GPIO2  13|14   GND
 GPIO3  15|16   GPIO4
 3V3    17|18   GPIO5
 MOSI   19|20   GND
 MISO   21|22   GPIO6
 SCLK   23|24   CE0
 GND    25|26   CE1
*/



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
int PIR_init(void (*motion_start_callback)(void), void (*motion_end_callback)(void))
{
  pinMode(PIR_PIN, INPUT);
  pullUpDnControl (PIR_PIN, PUD_DOWN);


  if ( wiringPiISR (PIR_PIN, INT_EDGE_RISING, motion_start_callback) < 0 ) {
      qDebug() << "Error setting motion start callback";
      return 1;
  }

  if ( wiringPiISR (PIR_PIN, INT_EDGE_FALLING, motion_end_callback) < 0 ) {
      qDebug() << "Error setting motion end callback";
      return 2;
  }

  return 0;
}
