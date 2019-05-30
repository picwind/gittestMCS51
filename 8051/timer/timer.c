/********************************************************************/
/********************************************************************/
/*****                                                          *****/
/*****        L A B C E N T E R    E L E C T R O N I C S        *****/
/*****                                                          *****/
/*****       LABCENTER INTEGRATED SIMULATION ARCHITECTURE       *****/
/*****                                                          *****/
/*****              Interrupt driven Tasker procedure           *****/
/*****                                                          *****/
/********************************************************************/
/********************************************************************/
#include <reg52.h>
#include "cext.h"
#include "timer.h"
#include "taskproc.h"

// interrupt period (1 msec)
#define  tmr_time  1e-3 

static uchar counter ;
static uchar cnt, dpcnt, kbcnt;
static uint timer_counter;

void timer1_ISR (void) interrupt 5 using 1
// Timer2 isr 
 { // Clear interrupt 
   TF2 = 0;
   // Do it at 1ms
   led_mux();  

   // Task procedure. 
   // Each task runs every 10ms multiplied by its own task counter 
   // S0:
   if (counter == 1) 
    { if (cnt == 100)  
       { cnt = 0;   
         led_counter();
       } 
      // Increment of the Timer task counter 
      cnt++;
    } 
   // S1: 
   if (counter == 2) 
    { if (dpcnt == 20) 
       { dpcnt = 0; 
         blink_dp();
       }    
      // Increment of the decimal point task counter 
      dpcnt++;
    } 
   // S2: 
   if (counter == 3) 
    { if (kbcnt == 25) 
       { kbcnt = 0; 
         get_key();
       }    
      // Increment of the keyboard task counter 
      kbcnt++;
    } 

   if (++counter == 10) counter = 0; 

   /*
   State table 
   S0: Timer counts 
   S1: Blink dp
   S2: get keys   
   Other task state are null
   */
 }


void init_timer (float fclk)
// Timer2 initialization
 { int tmr_reload;
   counter = 0;  // initialize state counter

   // initialization T2CON:
   //   CP/RL2 = 0 (autoreload, no capture),
   //   EXEN2 = 0 (disable external input T2EX),
   //   C/T2 = 0 (timer, no counter),
   //   RCLK = TCLK = 0 (timer, no baud rate generator),
   //   TF2 = EXF2 = 0 (interrupt flags cleared) 
   //   TR2 = 0 (timer stop, please)
   T2CON = 4;

   // Load timer2 autoreload bytes
   tmr_reload = (0xFFFF - (uint)((fclk * tmr_time) / 12));
   RCAP2H = high_byte(tmr_reload); 
   RCAP2L = low_byte(tmr_reload);

   // Highest priority for Timer2 interrupts
   PT2 = 1;
   // Enables Timer2 interrupts
   ET2 = 1;
   // Start Timer2
   TR2 = 1;
 }