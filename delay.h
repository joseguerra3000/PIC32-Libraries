/* 
 * File:   delay.h
 * Author: joseguerra
 *
 * Funciones de apoyo utilizadas para facilitar las 
 * operaciones con modulos Pmod. 
 */

#ifndef _DELAY_H
#define	_DELAY_H

#include <xc.h>
#include <stdbool.h>
#include <stdint.h>

#ifdef	__cplusplus
extern "C" {
#endif

/*Macros*/

#ifndef Sys_Clk
# define Sys_Clk (80000000L)
#endif

#ifndef CP0_FREQ
# define CP0_FREQ (Sys_Clk/2)
#endif
    
/*Functions*/
inline void delay_ms( uint32_t msec ){
	uint32_t tWait, tEnd;
	
	tWait = (CP0_FREQ/1000)*msec;
    tEnd = _CP0_GET_COUNT() + tWait;

    while( _CP0_GET_COUNT() < tEnd );
}

void delay_us( uint32_t usec ){
    uint32_t tWait, tEnd;
    tWait = (CP0_FREQ/1000000)*usec;
    tEnd = _CP0_GET_COUNT() + tWait;
    
    while( _CP0_GET_COUNT() < tEnd );
}

void delay_ticks( uint32_t ticks ){//ticks_max = 2^32 - 1
    uint32_t tEnd = _CP0_GET_COUNT() + ticks;
    
    while( _CP0_GET_COUNT() < tEnd );
}



#ifdef	__cplusplus
}
#endif

#endif	/* _PMOD_TOOLS_H */




