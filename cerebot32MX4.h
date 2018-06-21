/* 
 * File:   cerebot32MX4.h
 * Author: Jose Guerra Carmenate
 *
 * Created on 19 de mayo de 2018, 4:34
 * 
 * Summary:
 *  This file contain specific definitions and constants, for use with the
 *  CEREBOT32MX4 board, like:
 *   - Frequency related define Macros
 *   - On-board devices define Macros
 *   - Connectors Maps define Macros 
 * 
 */

#ifndef _CEREBOT32MX4_H
#define	_CEREBOT32MX4_H

#ifdef	__cplusplus
extern "C" {
#endif
/******************************************************************************/
/* System Level #define Macros                                                */
/******************************************************************************/

/* Microcontroller MIPs (FCY) */
#ifndef SYS_FREQ
# define SYS_FREQ    80000000L       /* System frequency (80MHz)       */
#endif

#ifndef FCY
#define FCY          SYS_FREQ        /* System frequency (80MHz)       */
#endif
#ifndef Sys_Clk
# define Sys_Clk     SYS_FREQ        /* System Clock (80MHz)           */
#endif

#ifndef CP0_FREQ
# define CP0_FREQ    (SYS_FREQ/2)    /* Co-processor Frequency (40MHz) */
#endif

#ifndef Cp0_Clk
# define Cp0_Clk      CP0_FREQ       /* Co-processor Clock (40MHz)     */
#endif

#ifndef Pb_Clk
# define Pb_Clk       (Sys_Clk/4)    /* Peripherial Clock  (20MHz)     */
#endif
   
#ifndef PB_FREQ
# define PB_FREQ      Pb_Clk         /* Peripherial Frequency (20MHz)  */
#endif

/******************************************************************************/
/* On-Board Device Define Macros                                              */
/******************************************************************************/

/*************************** LEDS-OnBoard *************************/
/* PORT registers */
#define LEDS_PORT PORTB 
#define LEDS_PORTSET PORTBSET
#define LEDS_PORTCLR PORTBCLR
#define LEDS_PORTINV PORTBINV

/* TRIS registers */
#define LEDS_TRIS TRISB
#define LEDS_TRISSET TRISBSET
#define LEDS_TRISCLR TRISBCLR
#define LEDS_TRISINV TRISBINV

/* LAT registers */    
#define LEDS_LAT  LATB    
#define LEDS_LATSET  LATBSET    
#define LEDS_LATCLR  LATBCLR    
#define LEDS_LATINV  LATBINV    

/* BIT MASK */
#define LEDS_MASK 0x3C00
#define LED1_MASK 0x0400
#define LED2_MASK 0x0800
#define LED3_MASK 0x1000
#define LED4_MASK 0x2000
    
/* BIT POSITION */
#define LED1_BIT 10
#define LED2_BIT 11
#define LED3_BIT 12
#define LED4_BIT 13

/* Channels */
#define LEDS_CHANNEL PORT_CHANNEL_B /* PORT CHANNEL for On-Board LEDS: use with peripherial lib */
#define LED1_CHANNEL PORT_CHANNEL_B /* PORT CHANNEL for On-Board LED1: use with peripherial lib */
#define LED2_CHANNEL PORT_CHANNEL_B /* PORT CHANNEL for On-Board LED2: use with peripherial lib */
#define LED3_CHANNEL PORT_CHANNEL_B /* PORT CHANNEL for On-Board LED3: use with peripherial lib */
#define LED4_CHANNEL PORT_CHANNEL_B /* PORT CHANNEL for On-Board LED4: use with peripherial lib */

/* Macros Functions */

/* ------------------------------------------------------------ */
/*        ledsOn( ledsMask )
**
**        @Synopsis:
**          ledsOn( ledsMask );
** 
**        @Parameters:
**          ledsMask - Or-ed convination of LEDx_MASK where x = { 1,2,3,4 } 
**
**        @Return Values:
**          None
**
**        @Errors:
**          None
 * 
**        @Description:
**			Configure the pin has output and put a High Level on it.
**		  
**		  @Example:
**          ledsOn( LED1_MASK | LED2_MASK )
*/
#define ledsOn( ledsMask ) LEDS_TRISCLR = (ledsMask); LEDS_LATSET = (ledsMask);

/* ------------------------------------------------------------ */
/*        ledsOff( ledsMask )
**
**        @Synopsis:
**          ledsOff( ledsMask );
** 
**        @Parameters:
**          ledsMask - Or-ed convination of LEDx_MASK where x = { 1,2,3,4 } 
**        
**		  @Return Values:
**          None
**
**        @Errors:
**          None
 * 
**        @Description:
**			Configure the pin has output and put a Low Level on it.
**
**		  @Example:
**          ledsOff( LED1_MASK | LED2_MASK )
*/
#define ledsOff( ledsMask ) LEDS_TRISCLR = (ledsMask); LEDS_LATCLR = (ledsMask);


/* ------------------------------------------------------------ */
/*        ledsToggle( ledsMask )
**
**        @Synopsis:
**          ledsToggle( ledsMask );
** 
**        @Parameters:
**          ledsMask - Or-ed convination of LEDx_MASK where x = { 1,2,3,4 } 
**
**        @Return Values:
**          None
**
**        @Errors:
**          None
 * 
**        @Description:
**			Configure the pin has output and invert the signal on it.
**
**		  @Example:
**          ledsToggle( LED1_MASK | LED2_MASK )
*/
#define ledsToggle( ledsMask ) LEDS_TRISCLR = (ledsMask); LEDS_LATINV = (ledsMask);

/*************************** Buttons On-Board *************************/
/* PORT registers */
#define BTNS_PORT PORTA
#define BTNS_PORTSET PORTASET
#define BTNS_PORTCLR PORTACLR
#define BTNS_PORTINV PORTAINV
    
/* TRIS registers */
#define BTNS_TRIS TRISA
#define BTNS_TRISSET TRISASET
#define BTNS_TRISCLR TRISACLR
#define BTNS_TRISINV TRISAINV

/* LAT registers */    
#define BTNS_LAT LATA
#define BTNS_LATSET LATASET
#define BTNS_LATCLR LATACLR
#define BTNS_LATINV LATAINV

/* BIT MASK */
#define BTNS_MASK 0xC0
#define BTN1_MASK 0x40
#define BTN2_MASK 0x80

/* BIT POSITION */
#define BTN1_BIT 6
#define BTN2_BIT 7

/* Channels */
#define BTNS_CHANNEL PORT_CHANNEL_A /* PORT CHANNEL for On-Board BTNs: use with peripherial lib */
#define BTN1_CHANNEL PORT_CHANNEL_A /* PORT CHANNEL for On-Board BTN1: use with peripherial lib */
#define BTN2_CHANNEL PORT_CHANNEL_A /* PORT CHANNEL for On-Board BTN2: use with peripherial lib */


/******************************************************************************/
/* Connectors Maps #define Macros                                             */
/******************************************************************************/

#define CONNECTOR_JA_UPPER &PORTE,0, &PORTE,1, &PORTE,2, &PORTE,3
#define CONNECTOR_JA_LOWER &PORTE,4, &PORTE,5, &PORTE,6, &PORTE,7
#define CONNECTOR_JA CONNECTOR_JA_UPPER, CONNECTOR_JA_LOWER 

#define CONNECTOR_JB_UPPER &PORTG,9, &PORTG,8, &PORTG,7, &PORTG,6
#define CONNECTOR_JB_LOWER &PORTB,15,&PORTD,5, &PORTD,4, &PORTB,14
#define CONNECTOR_JB CONNECTOR_JB_UPPER, CONNECTOR_JB_LOWER 

#define CONNECTOR_JC_UPPER &PORTG,12, &PORTG,13, &PORTG,14, &PORTG,15
#define CONNECTOR_JC_LOWER &PORTG,0, &PORTG,1, &PORTF,0, &PORTF,1
#define CONNECTOR_JC CONNECTOR_JC_UPPER, CONNECTOR_JC_LOWER 

#define CONNECTOR_JD_UPPER &PORTD,7, &PORTD,1, &PORTD,9, &PORTC,1
#define CONNECTOR_JD_LOWER &PORTD,6, &PORTD,2, &PORTD,10, &PORTC,2
#define CONNECTOR_JD CONNECTOR_JD_UPPER, CONNECTOR_JD_LOWER 

#define CONNECTOR_JE_UPPER &PORTD,14, &PORTD,15, &PORTF,2, &PORTF,8
#define CONNECTOR_JE_LOWER &PORTD,13, &PORTD,3, &PORTD,11, &PORTC,3
#define CONNECTOR_JE CONNECTOR_JE_UPPER, CONNECTOR_JE_LOWER 

/* TODO: Add CONNECTOR_JF define */

#define CONNECTOR_JH_UPPER &PORTF,12, &PORTF,13, &PORTF,4, &PORTF,5
#define CONNECTOR_JH_LOWER &PORTE,8, &PORTD,0, &PORTD,8, &PORTE,9
#define CONNECTOR_JH CONNECTOR_JH_UPPER, CONNECTOR_JH_LOWER 

#define CONNECTOR_JJ_UPPER &PORTB,0, &PORTB,1, &PORTB,2, &PORTB,3
#define CONNECTOR_JJ_LOWER &PORTB,4, &PORTB,5, &PORTB,8, &PORTB,9
#define CONNECTOR_JJ CONNECTOR_JJ_UPPER, CONNECTOR_JJ_LOWER 

#define CONNECTOR_JK_UPPER &PORTB,10, &PORTB,11, &PORTB,12, &PORTB,13
#define CONNECTOR_JK_LOWER &PORTA,9, &PORTA,10, &PORTD,12, &PORTC,4
#define CONNECTOR_JK CONNECTOR_JK_UPPER, CONNECTOR_JK_LOWER 
 	

#ifdef	__cplusplus
}
#endif

#endif	/* _CEREBOT32MX4_H */

