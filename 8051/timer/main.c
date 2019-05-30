/********************************************************************/
/********************************************************************/
/*****                                                          *****/
/*****        L A B C E N T E R    E L E C T R O N I C S        *****/
/*****                                                          *****/
/*****       LABCENTER INTEGRATED SIMULATION ARCHITECTURE       *****/
/*****                                                          *****/
/*****                     Programmable Timer                   *****/
/*****                                                          *****/
/********************************************************************/
/********************************************************************/

#include <reg52.h> 
#include "cext.h"
#include "timer.h"

void main( void )
 { // initializes internal 8052 timer. 
   // Clock Frequency = 12 MHz
   init_timer(12e6);  
   // enables interrupts
   EA = 1;
   // loop for ever
   while (1);
 }
