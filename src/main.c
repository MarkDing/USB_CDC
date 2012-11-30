//------------------------------------------------------------------------------
// Copyright (c) 2012 by Silicon Laboratories.
// All rights reserved. This program and the accompanying materials
// are made available under the terms of the Silicon Laboratories End User
// License Agreement which accompanies this distribution, and is available at
// http://developer.silabs.com/legal/version/v10/License_Agreement_v10.htm
// Original content and implementation provided by Silicon Laboratories.
//------------------------------------------------------------------------------
// library
#include <stdio.h>
// hal
#include <si32_device.h>
#include <SI32_PBSTD_A_Type.h>
// application
#include "gModes.h"
#include "gCPU.h"
extern void uart_send_data(unsigned char *data, unsigned int count);
extern int uart_get_data(unsigned char *data, unsigned int count);
extern void uart_configuration(uint32_t baud_rate,uint8_t stop_bits,uint8_t parity,uint8_t data_bits);

uint8_t data_buf[16];

/*
 *   baud_rate: baud rate
 *   stop_bits: 0 - 1 stop bit; 1 - 1.5 stop bits; 2 - 2 stop bits
 *   parity: 0 - none; 1 - odd; 2 - even; 3 - mark; 4 - space
 *   data_bits: data bits(5,6,7,8 or 16)
 */
#define BAUD_RATE 115200
void uart_test(void)
{
	uart_configuration(115200,0,0,8);
	while(1)
	{
		if(uart_get_data(data_buf,1) == 0)
		{
			uart_send_data(data_buf,1);
		}
	}
}
extern int vcp_main(void);
//==============================================================================
// myApplication.
//==============================================================================
int main()
{
   // msTicks increments every 1ms (1Khz). Driven by boot osc (myCpu.c)
   // _last variables store the last seen state of variables so we know when they have changed
   uint32_t msTicks_last=0xffffffff;
   uint32_t tmp;
   while(SI32_PBSTD_A_read_pin(SI32_PBSTD_2,8) == 0);

   // Enter the default operating mode for this application
   enter_default_mode_from_reset();
//   uart_test();
   vcp_main();
   while (1)
   {
     // if msTicks has changed
     if (msTicks != msTicks_last)       
     {
           // EVERY 2^10 counts
       if (!(msTicks % 512)) 
       {
         if(msTicks % 1024)
         {
           // TURN ON LED driver (P2.10)
           SI32_PBSTD_A_write_pins_low(SI32_PBSTD_2, 0x400);
         }
         else
         {
           // TURN OFF LED driver (P2.10)
           SI32_PBSTD_A_write_pins_high(SI32_PBSTD_2, 0x400);          
         }
       }
       // save current msTicks value as last seen
       msTicks_last = msTicks;       
     }// if msTicks changed
     
   }//while(1)
}

//-eof--------------------------------------------------------------------------

