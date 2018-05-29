/* 
 * File:   pwm.c
 * Author: Jose Guerra Carmenate
 *
 * Created on 21 de mayo de 2018, 1:31
 */


/* Include */
#include "pwm.h"
#include <stdint.h>
#include <sys/attribs.h> 
#include <xc.h>
#include <stdbool.h>



/* Global variables */

/* Functions */

PWM_RETURN_FLAG PWM_SetUp( uint8_t pwmMask, uint16_t pwmFreq, bool useT2 ){
    uint8_t i;
    int32_t period;
    volatile __OC1CONbits_t *oc; 
    if( pwmFreq == 0 )
        return PWM_RETURN_ERROR_FREQ_SMALLER;
    
    period = (int32_t)((Pb_Clk)/(int32_t)pwmFreq) ;
    
    if( period <= 0  )
        return PWM_RETURN_ERROR_FREQ_LONGER;
    else if( period >= __PWM_MAX_TIMER_PERIOD )
        return PWM_RETURN_ERROR_FREQ_SMALLER;
    
    // Configure Timer
    if( useT2 ){
        T2CONbits.ON = false;      // stop
        T2CONbits.TCS = 0;         // sources -> peripherial clock
        T2CONbits.TCKPS = 0;       // prescaler -> 1:1
        TMR2 = 0;               
        PR2 = (uint16_t)period;           
        IFS0bits.T2IF = false;      // Clear Interrupt flag
        IPC2bits.T2IP = 7;          // Interrupt priority = 7
        IPC2bits.T2IS = 3;          // Subpriority = 3
        IEC0bits.T2IE = 0;          // enable interrupt
    }
    else{
        T3CONbits.ON = false;      // stop
        T3CONbits.TCS = 0;         // sources -> peripherial clock
        T3CONbits.TCKPS = 0;       // prescaler -> 1:1
        TMR3 = 0;               
        PR3 = (uint16_t)period;           
        IFS0bits.T3IF = false;      // Clear Interrupt flag
        IPC3bits.T3IP = 7;          // Interrupt priority = 7
        IPC3bits.T3IS = 3;          // Subpriority = 3
        IEC0bits.T3IE = 0;          // enable interrupt
    }
    
    for( i = 0; i < 5; i++ ){
        if( (pwmMask>>i) & 1 ){
            oc = (volatile __OC1CONbits_t *)__OC_address[i];
            
            oc->ON = 0;
            oc->w = 0x0000;                 // Turn off the OC when performing the setup
            oc->OCM = 0x6;                  // Configure for PWM mode without Fault pin enabled
            if( useT2 )
                oc->OCTSEL = 0;                 // Configure Timer2 as time clock
            else
                oc->OCTSEL = 1;                 // Configure Timer3 as time clock
        }
    }
    
    return PWM_RETURN_SUCCESSFUL;
}


/* ------------------------------------------------------------ */
/*        PWM_RETURN_FLAG PWM_Start( uint8_t index )
**
**        Synopsis:
**          PWM_Start( index )
** 
**        Parameters:
**          uint8_t index - Is the Pwm signal that we can enable to use.
**        Return Values:
**          PWM_RETURN_FLAG - It can be:
 *              - PWM_RETURN_SUCCESSFUL (Successful operation)
**              - PWM_RETURN_ERROR_WRONG_INDEX (Invalid OC' index)
**        Errors:
**          See Return Values
**        Description:
**          This function enable the OC module number 'index' and start
 *          Timer2 if this is off.
**				
*/
PWM_RETURN_FLAG PWM_Start( uint8_t index ){
    if( index < 1 || index > 5 )
        return PWM_RETURN_ERROR_WRONG_INDEX; 
    volatile uint32_t *OCxR = (volatile uint32_t *)( __OC_address[index-1] + 0x10  );
    volatile uint32_t *OCxRS = (volatile uint32_t *)( __OC_address[index-1] + 0x20  );
    volatile __OC1CONbits_t *oc = (volatile __OC1CONbits_t *)__OC_address[index-1];
    
    *OCxR  = 0x0;                       // Initialize primary Compare register
    *OCxRS = 0x0;                       // Initialize secondary Compare register
    
    if( oc->OCTSEL == false )
        T2CONbits.ON = true;            // start timer 2
    else
        T3CONbits.ON = true;            // start timer 3
    
    asm( "nop" );asm( "nop" );          // delay two ticks
    
    oc->ON = 1;                         // Enable OC1

    return PWM_RETURN_SUCCESSFUL;
}