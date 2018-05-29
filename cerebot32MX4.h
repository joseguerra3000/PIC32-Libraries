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
 *   - 
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
   
#ifdef	__cplusplus
}
#endif

#endif	/* _CEREBOT32MX4_H */

