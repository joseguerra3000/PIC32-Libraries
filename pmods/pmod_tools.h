/* 
 * File:   pmod_tools.h
 * Author: Jose Guerra Carmenate
 *
 * Funciones de apoyo utilizadas para facilitar las 
 * operaciones con modulos Pmod. 
 */

#ifndef _PMOD_TOOLS_H
#define	_PMOD_TOOLS_H
#include <stdbool.h>
#include <xc.h>
#include <stdint.h>
#include <stddef.h>

#include "../delay.h"
typedef short int _port_channel;
typedef volatile unsigned int port;


/********************Set of routines for pin manipulations*********************/
inline void _PinSet( _port_channel ch, int pin ){
	*(&LATBSET + (ch-1) * 0x10) = 1<<pin;
}

inline void _PinClear( _port_channel ch, int pin ){
	*(&LATBCLR + (ch-1) * 0x10) = 1<<pin;
}

inline void _PinToggle( _port_channel ch, int pin ){
	*(&LATBINV + (ch-1) * 0x10) = 1<<pin;
}

inline void _PinWrite( _port_channel ch, int pin, bool v ){
	if(v == true) {
        *(&LATBSET + (ch - 1) * 0x10) = 1<<pin;
    }
    else{
        *(&LATBCLR + (ch - 1) * 0x10) = 1<<pin;
    }
}
inline bool _PinRead( _port_channel ch, int pin ){
	return ((*(&PORTB + (ch -1)*0x10 )) & (1<<pin))?1:0;
}

inline void _PinDirectionOutputSet( _port_channel ch, int pin ){
	*(&TRISBCLR + (ch - 1) * 0x10) = 1<<pin;	
}
inline void _PinDirectionInputSet( _port_channel ch, int pin ){
	*(&TRISBSET + (ch - 1) * 0x10) = 1<<pin;
}
/******************************************************************************/

/**Get port channel*/
#define _GetPortChannel( x ) (((x) - &PORTB + 0x10)/0x10)

#endif	/* _PMOD_TOOLS_H */




