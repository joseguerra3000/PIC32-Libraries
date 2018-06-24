/* 
 * File:   delay.h
 * Author: joseguerra
 *
 * Summary:
 *  This file have the definition, constants and functions usesful for
 *  delay generations.
 */

#ifndef _DELAY_H
#define	_DELAY_H

#include "cerebot32MX4.h"
#include <xc.h>
#include <stdint.h>

#ifdef	__cplusplus
extern "C" {
#endif

/* CONSTANTS */

#ifndef Sys_Clk
# define Sys_Clk (80000000L)
#endif

#ifndef CP0_FREQ
# define CP0_FREQ (Sys_Clk/2)
#endif
    
/* FUNCTIONS */ 

    
/* ------------------------------------------------------------ */
/*        inline void delay_ms( uint32_t msec )

          @Synopsis
            delay_ms( msec );
 
          @Parameters
            uint32_t msec - amount of time [miliseconds]

          @Return Values
            None

          @Errors
            None
 
          @Description
            Pauses the program for the amount of time (in miliseconds) 
           specified as parameter.	
*/
inline void delay_ms( uint32_t msec ){
	uint32_t tWait, tEnd;
	
	tWait = (CP0_FREQ/1000)*msec;
    tEnd = _CP0_GET_COUNT() + tWait;

    while( _CP0_GET_COUNT() < tEnd );
}

/* ------------------------------------------------------------ */
/*        inline void delay_us( uint32_t usec )

          @Synopsis
            delay_us( usec );
 
          @Parameters
            uint32_t usec - amount of time [microseconds]
  
          @Return Values
            None
  
          @Errors
            None
   
          @Description
            Pauses the program for the amount of time (in microseconds) 
           specified as parameter.	
*/
inline void delay_us( uint32_t usec ){
    uint32_t tWait, tEnd;
    tWait = (CP0_FREQ/1000000)*usec;
    tEnd = _CP0_GET_COUNT() + tWait;
    
    while( _CP0_GET_COUNT() < tEnd );
}

/* ------------------------------------------------------------ */
/*        inline void delay_ticks( uint32_t ticks)

          @Synopsis
            delay_ticks( ticks );
   
          @Parameters
            uint32_t ticks - amount of Co-processor pulses
  
          @Return Values
            None
  
          @Errors
            None
   
          @Description
            Pauses the program for the amount of Co-processor pulses 
           specified as parameter.	
*/
inline void delay_ticks( uint32_t ticks ){//ticks_max = 2^32 - 1
    uint32_t tEnd = _CP0_GET_COUNT() + ticks;
    
    while( _CP0_GET_COUNT() < tEnd );
}

/* ------------------------------------------------------------ */
/*        inline void delay( uint32_t msec )
        
          @Description
 		    Pauses the program for the amount of time (in miliseconds) 
          specified as parameter.	
         
          @Note
            Just like delay_ms function. See delay_ms function for reference
*/
inline void delay( uint32_t msec ){ delay_ms( msec ); }

/* ------------------------------------------------------------ */
/*        inline void delay( uint32_t msec )
        
          @Description
            Pauses the program for the amount of time (in microseconds) 
           specified as parameter.	
        
          @Note
           Just like delay_us function. See delay_us function for reference
*/
inline void delayMicroseconds( uint32_t usec ){ delay_us( usec ); }

#ifdef	__cplusplus
}
#endif

#endif	/* _PMOD_TOOLS_H */




