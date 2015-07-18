#include <ets_sys.h>
#include <osapi.h>
#include <gpio.h>
#include <os_type.h>

/*
 * $Id$
 *
 * A basic template that sets up a native application on the ESP8266.
 * Basically initializes important hardware, and sets up a WiFi connection.
 * It demonstrates how to initialize the application, how you might wish 
 * to use SmartConfig, and some very basic examples.
 *
 * Written by Mark VandeWettering.
 */

static volatile os_timer_t timer0 ;


static volatile int tick=1 ;
void ICACHE_FLASH_ATTR
timer0_interrupt(void *arg)
{
    if (tick == 1) 
 	os_printf("TICK") ;
    else
	os_printf("TOCK\n") ;
    tick = 1 - tick ;
}

void ICACHE_FLASH_ATTR
user_rf_pre_init()
{
}

void ICACHE_FLASH_ATTR
user_init() 
{
    uart_div_modify(0, UART_CLK_FREQ / 9600) ;

    os_printf("SDK version: %s\n", system_get_sdk_version());

    /* Stop the timer, set up and interrupt
     * routine that fires once per second.
     */
    os_timer_disarm(&timer0) ;
    os_timer_setfn(&timer0, (os_timer_func_t *) timer0_interrupt, NULL) ;
    os_timer_arm(&timer0, 1000, 1) ;
}
