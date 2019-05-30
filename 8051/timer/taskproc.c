/********************************************************************/
/********************************************************************/
/*****                                                          *****/
/*****        L A B C E N T E R    E L E C T R O N I C S        *****/
/*****                                                          *****/
/*****       LABCENTER INTEGRATED SIMULATION ARCHITECTURE       *****/
/*****                                                          *****/
/*****                      Tasks Processes                     *****/
/*****                                                          *****/
/********************************************************************/
/********************************************************************/

#include <reg52.h> 
#include "cext.h"

char num[ ] = {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};   // 7-seg codes 
char add[ ] = {0x0fe,0x0fd,0x0fb,0x0f7};                             // Multiplexing address
char dpn[ ] = {0,0,0,0};                                             // Dots matrix
char buf[ ] = {0,0,0,0};                                             // Counter buffer
char alm[ ] = {0,0,0,0};                                             // Alarm sets buffer
char value, key_mask, new_key;

static uchar d0, d1, d2, d3, d5;
static uchar flag;
static uchar digit_counter;

static char set_flag;
static char set_count;
static char set_alm;
static char stop_counter = true;

char un, th;
uint timer;
uint alarm;
uchar del;

// P2.7. Alarm output
sbit alm_out = P2^7;   

// processor switch contest.
#pragma registerbank (1)      

// Multiplexing Task. Do it every 10ms
void led_mux ()
 { if (!set_flag) 
    { // Normal counting. Display the counts.
      value = buf[digit_counter];   
      P1 = num[value] | dpn[digit_counter] ; 
    }
   else 
    { // Display alarm values 
      value = alm[digit_counter];   
      P1 = num[value] | dpn[digit_counter] ; 
    }     
   
   if (set_alm) 
    { // Timer and alarm value
      timer = buf[0] * 1000 + buf[1] * 100 + buf[2] * 10 + buf[3];
      alarm = alm[0] * 1000 + alm[1] * 100 + alm[2] * 10 + alm[3];
      // Check whether the alarm condition is occured or not  
      if ((alarm - timer) <= 0) 
       { alm_out = false;           // Make alarm out low.
         stop_counter = true  ;     // Stop the counter. 
       }
    }

   // Drive the digit actually multiplexed.
   P0 = add[digit_counter];
   for (del=0; del<100; del++) ;
   // Increase multiplexer address to the next digit
   digit_counter++ ;

   // Did you diplay all digit ? 
   if (digit_counter >= 4) 
      // Start again.
      digit_counter = 0;      

   // Pulse high P0.0, P0.1, P0.2 and P0.3
   P0 = P0 | 0x0f;
 }


// Blink on and off the dots when counting and alarm is on.  
void blink_dp ()
 { if (!set_flag && !stop_counter) 
    { if (flag) 
         dpn[1] = 0x80; 
      else 
         dpn[1] = 0x0;
      
      flag = !flag;
    }  
 }

// Counter. Counts from 00.00 to 59.59 min.sec. 
// The Timer interrupt is driven every 1 sec.
void led_counter ()
 { if (!stop_counter) buf[3]++;
   
   if (buf[3] > 9) 
    { buf[3] = 0; 
      d3 = true; 
    }
   
   if (d3) 
    { ++buf[2]; 
      d3 = false; 
    }
   
   if (buf[2] > 5) 
    { buf[2] = 0; 
      d2 = true; 
    }

   if (d2) 
    { ++buf[1]; 
      d2 = false; 
    }
   
   if (buf[1] > 9) 
    { buf[1] = 0; 
      d1 = true; 
    }

   if (d1) 
    { ++buf[0]; 
      d1 = false; 
    }
   
   if (buf[0] > 5) 
    { buf[0] = 0; 
      d0 = true; 
    }
 }




// Four keys Task manager. 
// Timer interrupt driven every 250ms
void get_key ()
 { char valid_key; 
   char delay = 127;
   key_mask = P0 & 0xf0;   
   while (--delay >= 0) ;
   valid_key =  P0 & 0xf0;
   if (key_mask != valid_key) valid_key = 0;
   while ((P0 & 0xf0) != (0 | (valid_key & 0x40))) ;

   switch (valid_key) 
    { case 0x10:              // Reset Timer
         buf[0] = 0;
         buf[1] = 0;
         buf[2] = 0;
         buf[3] = 0;
         alm_out = true;
         stop_counter = !stop_counter;
         break;      

      case 0x20:              // Set alarm
         ++set_count;
         if (set_count == 1) 
          { // First time SET is pressed. Sets seconds
            set_flag = true;           
            dpn[0] = 0; dpn[1] = 0; dpn[2] = 0x80; dpn[3] = 0x80;
          }
         else if (set_count == 2) 
          { // Second time SET is pressed. Set minutes
            set_flag = true;           
            dpn[0] = 0x80; dpn[1] = 0x80; dpn[2] = 0; dpn[3] = 0;
          }
         else if (set_count == 3) 
          { // Latest time SET is pressed. Return to timer functions.
            set_flag = false;          
            set_count = 0;
            dpn[0] = 0; dpn[1] = 0; dpn[2] = 0; dpn[3] = 0;
          }
         un = 0;
         th = 0;
         break;

      case 0x40:              // Set seconds/minutes
         if (set_count == 1) 
          { ++un;
            if (un > 9) 
             { th++; 
               un = 0; 
               if(th > 5) 
                  th = 0;
             } 
            alm[3] = un;
            alm[2] = th;                  
          }
         else if (set_count == 2) 
          { ++un;
            if (un > 9) 
             { th++; 
               un = 0; 
               if(th > 5) 
                  th = 0;
             } 
            alm[1] = un;
            alm[0] = th;                  
          }
         break;
   
      case 0x80:              // Set alarm on/off
         set_alm = !set_alm;
         if (set_alm) 
          { dpn[0] = 0x80; dpn[1] = 0x80; dpn[2] = 0x80; dpn[3] = 0x80;
          }
         else 
          { dpn[0] = 0x0; dpn[1] = 0x80; dpn[2] = 0x0; dpn[3] = 0x0;
          }
         break;      
     }  
 }        
