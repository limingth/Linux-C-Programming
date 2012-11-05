#ifndef LED_API_H
#define LED_API_H

#include "led_drv.h"

int led_init(void);

int led_on(int);
int led_off(int);

int led_running_horse(void);
int led_two_blink(void);

#endif
