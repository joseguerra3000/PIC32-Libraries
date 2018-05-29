/* ************************************************************************** */
/** Library for PmodSSD manipulation

  @Author
    Jose Guerra Carmenate

  @File Name
    pmod_ssd.h

  @Summary
    Brief description of the file.

  @Description
    Describe the purpose of this file.
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
#include "../pmod_tools.h"


/* Provide C++ Compatibility */
#ifdef __cplusplus
extern "C" {
#endif
/* ************************************************************************** */
/* Section: Constants                                                         */
/* ************************************************************************** */
//#define SSD_32MX4_Attached_JA
//#define SSD_32MX4_Attached_JB
//#define SSD_32MX4_Attached_JC
//#define SSD_32MX4_Attached_JD
//#define SSD_32MX4_Attached_JE
//#define SSD_32MX4_Attached_JH
//#define SSD_32MX4_Attached_JJ
//#define SSD_32MX4_Attached_JK
//#define SSD_32MX4_Attached_JA_JB_UPPER
//#define SSD_32MX4_Attached_JA_JB_LOWER
//#define SSD_32MX4_Attached_JB_JC_UPPER
//#define SSD_32MX4_Attached_JB_JC_LOWER
//#define SSD_32MX4_Attached_JC_JD_UPPER
//#define SSD_32MX4_Attached_JC_JD_LOWER
//#define SSD_32MX4_Attached_JE_JF_LOWER
//#define SSD_32MX4_Attached_JH_JJ_UPPER
//#define SSD_32MX4_Attached_JH_JJ_LOWER
//#define SSD_32MX4_Attached_JJ_JK_UPPER
//#define SSD_32MX4_Attached_JJ_JK_LOWER

    
    
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
        Full description, explaining the purpose and usage of the data type.
        <p>
        Additional description in consecutive paragraphs separated by HTML 
        paragraph breaks, as necessary.
        <p>
        Type "JavaDoc" in the "How Do I?" IDE toolbar for more information on tags.

      @Remarks
        Any additional remarks
        <p>
        Describe enumeration elements and structure and union members above each 
        element or member.
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
        bool PmodSSD_Attach( PmodSSD *ssd, 
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
        <ul>
          <li>1   Indicates an error occurred
          <li>0   Indicates an error did not occur
        </ul>

      @Example
        @code
        bool f = PmodSSD_Attach( &ssd, &PORTB, 10, &PORTB, 11, &PORTB, 12, &PORTB, 13, 
                                 &PORTA,  0, &PORTA,  1, &PORTA,  2, &PORTA, 4 ); 
     */
    bool PmodSSD_Attach( PmodSSD *ssd, 
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


    /* Provide C++ Compatibility */
#ifdef __cplusplus
}
#endif

#endif /* PMOD_SSD_H */

