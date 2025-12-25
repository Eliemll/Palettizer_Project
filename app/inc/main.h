/*
 * main.h
 *
 *  Created on: 16 ao�t 2018
 *      Author: Laurent
 */

#ifndef APP_INC_MAIN_H_
#define APP_INC_MAIN_H_

#include "stm32f0xx.h"
#include "main.h"
#include "bsp.h"
#include "factory_io.h"
#include "delay.h"
#include "FreeRTOSConfig.h"
// #include "tasks.c"

/* Global functions */

int my_printf	(const char *format, ...);
int my_sprintf	(char *out, const char *format, ...);


#endif /* APP_INC_MAIN_H_ */
