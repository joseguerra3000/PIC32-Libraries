/* ************************************************************************** */
/** Library for PmodSSD manipulation

  @Author
    Jose Guerra Carmenate

  @File Name
    pmod_ssd.h

  @Summary
    This file have the definition, constants and functions for use
    the Digilent PmodSSD module.

 */
/* ************************************************************************** */

#ifndef _PMOD_SSD_LIB_H    /* Guard against multiple inclusion */
#define _PMOD_SSD_LIB_H

/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
#include <xc.h>
#include <stdbool.h>
#include <stdint.h>
#include "pmod_tools.h"


/* Provide C++ Compatibility */
#ifdef __cplusplus
extern "C" {
#endif
/* ************************************************************************** */
/* Section: Constants                                                         */
/* ************************************************************************** */

/*
 * This Macros define make more easy the use of PmodSSD_Attach function on
 * firmware development for Digilent CEREBOT32MX4 Board.
 * Example: PmodSSD_Attach( &my_ssd, SSD_32MX4_Attached_JA_JB_UPPER_ARGS );
 */

#define SSD_32MX4_Attached_JA_ARGS &PORTE,0, &PORTE,1, &PORTE,2, &PORTE,3, &PORTE,4, &PORTE,5, &PORTE,6, &PORTE,7
#define SSD_32MX4_Attached_JB_ARGS &PORTG,9, &PORTG,8, &PORTG,7, &PORTG,6, &PORTB,15,&PORTD,5, &PORTD,4, &PORTB,14
#define SSD_32MX4_Attached_JC_ARGS &PORTG,12, &PORTG,13, &PORTG,14, &PORTG,15, &PORTG,0, &PORTG,1, &PORTF,0, &PORTF,1 
#define SSD_32MX4_Attached_JD_ARGS &PORTD,7, &PORTD,1, &PORTD,9, &PORTC,1, &PORTD,6, &PORTD,2, &PORTD,10, &PORTC,2
#define SSD_32MX4_Attached_JE_ARGS &PORTD,14, &PORTD,15, &PORTF,2, &PORTF,8, &PORTD,13, &PORTD,3, &PORTD,11, &PORTC,3
#define SSD_32MX4_Attached_JH_ARGS &PORTF,12, &PORTF,13, &PORTF,4, &PORTF,5, &PORTE,8, &PORTD,0, &PORTD,8, &PORTE,9
#define SSD_32MX4_Attached_JJ_ARGS &PORTB,0, &PORTB,1, &PORTB,2, &PORTB,3, &PORTB,4, &PORTB,5, &PORTB,8, &PORTB,9
#define SSD_32MX4_Attached_JK_ARGS &PORTB,10, &PORTB,11, &PORTB,12, &PORTB,13, &PORTA,9, &PORTA,10, &PORTD,12, &PORTC,4
#define SSD_32MX4_Attached_JA_JB_UPPER_ARGS &PORTE,0, &PORTE,1, &PORTE,2, &PORTE,3, &PORTG,9, &PORTG,8, &PORTG,7, &PORTG,6
#define SSD_32MX4_Attached_JA_JB_LOWER_ARGS &PORTE,4, &PORTE,5, &PORTE,6, &PORTE,7, &PORTB,15, &PORTD,5, &PORTD,4, &PORTB,14
#define SSD_32MX4_Attached_JB_JC_UPPER_ARGS &PORTG,9, &PORTG,8, &PORTG,7, &PORTG,6, &PORTG,12, &PORTG,13, &PORTG,14, &PORTG,15
#define SSD_32MX4_Attached_JB_JC_LOWER_ARGS &PORTB,15,&PORTD,5, &PORTD,4, &PORTB,14, &PORTG,0, &PORTG,1, &PORTF,0, &PORTF,1
#define SSD_32MX4_Attached_JC_JD_UPPER_ARGS &PORTG,12, &PORTG,13, &PORTG,14, &PORTG,15, &PORTD,7, &PORTD,1, &PORTD,9, &PORTC,1
#define SSD_32MX4_Attached_JC_JD_LOWER_ARGS &PORTG,0, &PORTG,1, &PORTF,0, &PORTF,1, &PORTD,6, &PORTD,2, &PORTD,10, &PORTC,2
#define SSD_32MX4_Attached_JE_JF_LOWER_ARGS &PORTD,13, &PORTD,3, &PORTD,11, &PORTC,3, &PORTA,2, &PORTA,3, &PORTA,6, &PORTA,7
#define SSD_32MX4_Attached_JH_JJ_UPPER_ARGS &PORTF,12, &PORTF,13, &PORTF,4, &PORTF,5, &PORTB,0, &PORTB,1, &PORTB,2, &PORTB,3
#define SSD_32MX4_Attached_JH_JJ_LOWER_ARGS &PORTE,8, &PORTD,0, &PORTD,8, &PORTE,9, &PORTB,4, &PORTB,5, &PORTB,8, &PORTB,9
#define SSD_32MX4_Attached_JJ_JK_UPPER_ARGS &PORTB,0, &PORTB,1, &PORTB,2, &PORTB,3, &PORTB,10, &PORTB,11, &PORTB,12, &PORTB,13
#define SSD_32MX4_Attached_JJ_JK_LOWER_ARGS &PORTB,4, &PORTB,5, &PORTB,8, &PORTB,9, &PORTA,9, &PORTA,10, &PORTD,12, &PORTC,4

/* ************************************************************************** */
/* Section: File Scope or Global Data                                         */
/* ************************************************************************** */
/* ************************************************************************** */
/** Convertion from Hex to 7 Seg.

  @Summary
    Convert from a number in the range [0-16] to 7-Segment representation.
 */
static const uint8_t __decod_digit_to_7Seg[] = {
        0x3F, //0
        0x06, //1
        0x5B, //2
        0x4F, //3
        0x66, //4
        0x6D, //5
        0x7D, //6
        0x07, //7
        0xFF, //8
        0x6F, //9
        0x77, //A
        0x7C, //b
        0x39, //C
        0x5E, //d
        0x79, //E
        0x71  //F
};


    // *****************************************************************************
    // Section: Data Types
    // *****************************************************************************

    /** Descriptive Data Type Name

      @Summary
        PmodSSD Class.
    
      @Description
        This data type is a abstract representation of PmodSSD module. 
     
      @Remarks
        uint16_t number - 16bit representation of data on PmodSSD module
        uint32_t X_port_channel - port channel of pin 'X' on PmodSSD module
        uint8_t X_pin - bit number ( on respective port of MCU ) of pin 'X' on PmodSSD module
     */
        typedef struct{
            union{
              uint16_t number;
              struct{
                  uint8_t low:8;
                  uint8_t high:8;
              };
            };
            
            union{
                struct{
                    uint32_t A_port_channel, B_port_channel, C_port_channel, 
                            D_port_channel, E_port_channel, F_port_channel, 
                            G_port_channel, CAT_port_channel;
                };
                uint32_t port_channel[8];
            };
            union{
                struct{
                    uint8_t A_pin, B_pin, C_pin, D_pin,
                            E_pin, F_pin, G_pin, CAT_pin;
                };
                uint8_t pin[8];
            };
        } PmodSSD;


    // *****************************************************************************
    // Section: Interface Functions
    // *****************************************************************************

    /**
      @Function
        void PmodSSD_Attach( PmodSSD *ssd, 
                             port *A_port, uint8_t A_pin, port *B_port, uint8_t B_pin, 
                             port *C_port, uint8_t C_pin, port *D_port, uint8_t D_pin, 
                             port *E_port, uint8_t E_pin, port *F_port, uint8_t F_pin, 
                             port *G_port, uint8_t G_pin, port *CAT_port, uint8_t CAT_pin 
                             );

      @Summary
        This function initializes SSD pins.

      @Precondition
        None
    
      @Parameters
        @param param1 Describe the first parameter to the function.
    
        @param param2 Describe the second parameter to the function.

      @Returns
        None

      @Example
        @code
        PmodSSD_Attach( &ssd, &PORTB, 10, &PORTB, 11, &PORTB, 12, &PORTB, 13, 
                                 &PORTA,  0, &PORTA,  1, &PORTA,  2, &PORTA, 4 ); 
     */
    void PmodSSD_Attach( PmodSSD *ssd, 
                         port *A_port, uint8_t A_pin, port *B_port, uint8_t B_pin, 
                         port *C_port, uint8_t C_pin, port *D_port, uint8_t D_pin, 
                         port *E_port, uint8_t E_pin, port *F_port, uint8_t F_pin, 
                         port *G_port, uint8_t G_pin, port *CAT_port, uint8_t CAT_pin 
                        );
    
    /**************************************************************************/
    /**
      @Function
        void PmodSSD_DisplaySingleDigit( PmodSSD *ssd, uint8_t digit, bool leftSide );

      @Summary
        This function set one of the two digits on one PmodSSD.

      @Precondition
        PmodSSD_Attach(&disp, ...);
    
      @Parameters
        @param ssd PmodSSD identifier.
    
        @param digit Value of the digit to write.
        
        @param leftSide digit to write

      @Returns
        None
      @Example
        @code
        PmodSSD_DisplaySingleDigit( &disp, 5, true );
     */
    void PmodSSD_DisplaySingleDigit( PmodSSD *ssd, uint8_t digit, bool leftSide );
    
    
    /****************************************************************************/
    
    /**
      @Function
        void PmodSSD_DisplayDecNumber( PmodSSD *ssd, uint8_t number );

      @Summary
        This function set a number in decimal base on one PmodSSD.

      @Precondition
        PmodSSD_Attach(&disp, ...);
    
      @Parameters
        @param ssd PmodSSD identifier.
    
        @param number number to write.

      @Returns
        None
      @Example
        @code
        PmodSSD_DisplayDecNumber( &disp, 5, true );
     */
    void PmodSSD_DisplayDecNumber( PmodSSD *ssd, uint8_t number );
    /****************************************************************************/
    
    /**
      @Function
        void PmodSSD_DisplayHexNumber( PmodSSD *ssd, uint8_t number );

      @Summary
        This function set a number in Hex base on one PmodSSD.

      @Precondition
        PmodSSD_Attach(&disp, ...);
    
      @Parameters
        @param ssd PmodSSD identifier.
    
        @param number number to write.

      @Returns
        None
      @Example
        @code
        PmodSSD_DisplayHexNumber( &disp, 0x1D, true );
     */
    void PmodSSD_DisplayHexNumber( PmodSSD *ssd, uint8_t number );
    
    /**
      @Function
        void PmodSSD_Multiplex( PmodSSD *ssd );

      @Summary
        This function is used to multiplex beetewn the two 7-SegDisp on PmodSSD.

      @Precondition
        PmodSSD_Attach(&disp, ...);
    
      @Parameters
        @param ssd PmodSSD identifier.
    
      @Returns
        None
      @Example
        @code
        void PmodSSD_Multiplex( &ssd );
     */
    void PmodSSD_Multiplex( PmodSSD *ssd );
    
    
    /* ------------------------------------------------------------ */
    /*        inline void PmodSSD_DisplayClear( PmodSSD *ssd )
    **
    **        @Synopsis:
    **          PmodSSD_DisplayClear( &my_ssd );
    ** 
    **        @Parameters:
    **          PmodSSD *my_ssd - PmodSSD identity
    **
    **        @Return Values:
    **          None
    **
    **        @Errors:
    **          None
    **        
    **        @Description:
    **          This function clear the PmodSSD module displays.
    **				
    */
    inline void PmodSSD_DisplayClear( PmodSSD *ssd ){
        ssd->low = ssd->high = 0;
    }

    /* Provide C++ Compatibility */
#ifdef __cplusplus
}
#endif

#endif /* PMOD_SSD_H */

