/* ************************************************************************** */
/** PmodSSD Library

  @Author
    Jose Guerra Carmenate

  @File Name
    pmod_ssd.c

  @Summary
    Interface Functions:
     - PmodSSD_Attach
     - PmodSSD_DisplaySingleDigit
     - PmodSSD_DisplayDecNumber
     - PmodSSD_DisplayHexNumber
     - PmodSSD_Multiplex

  @Description
    Library for PmodSSD module manipulation.
 */
/* ************************************************************************** */

/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
#include "../pmod_ssd.h"



/* ************************************************************************** */
// Section: Interface Functions                                               */
/* ************************************************************************** */

/** 
  @Function
    void PmodSSD_Attach( PmodSSD *ssd,
                         uint8_t *A_port, uint8_t A_pin, uint8_t *B_port, uint8_t B_pin, 
                         uint8_t *C_port, uint8_t C_pin, uint8_t *D_port, uint8_t D_pin, 
                         uint8_t *E_port, uint8_t E_pin, uint8_t *F_port, uint8_t F_pin, 
                         uint8_t *G_port, uint8_t G_pin, uint8_t *CAT_port, uint8_t CAT_pin 
                         );

  @Summary
    This function initializes SSD pins.


  @Remarks
    Refer to the pmod_ssd.h interface header for function usage details.
 */
void PmodSSD_Attach( PmodSSD *ssd, 
                     port *A_port, uint8_t A_pin, port *B_port, uint8_t B_pin, 
                     port *C_port, uint8_t C_pin, port *D_port, uint8_t D_pin, 
                     port *E_port, uint8_t E_pin, port *F_port, uint8_t F_pin, 
                     port *G_port, uint8_t G_pin, port *CAT_port, uint8_t CAT_pin){
    int i;
    ssd->A_port_channel = (A_port - &PORTB + 0x10)/0x10;
    ssd->B_port_channel = (B_port - &PORTB + 0x10)/0x10;
    ssd->C_port_channel = (C_port - &PORTB + 0x10)/0x10;
    ssd->D_port_channel = (D_port - &PORTB + 0x10)/0x10;
    ssd->E_port_channel = (E_port - &PORTB + 0x10)/0x10;
    ssd->F_port_channel = (F_port - &PORTB + 0x10)/0x10;
    ssd->G_port_channel = (G_port - &PORTB + 0x10)/0x10;
    ssd->CAT_port_channel = (CAT_port - &PORTB + 0x10)/0x10;

    ssd->A_pin = A_pin;
    ssd->B_pin = B_pin;
    ssd->C_pin = C_pin;
    ssd->D_pin = D_pin;
    ssd->E_pin = E_pin;
    ssd->F_pin = F_pin;
    ssd->G_pin = G_pin;
    ssd->CAT_pin = CAT_pin;

    // Configure pins in output mode and turn off each one.
    for( i = 0; i < 8; i++ ){
        _PinDirectionOutputSet( ssd->port_channel[i], ssd->pin[i] );
        _PinClear( ssd->port_channel[i], ssd->pin[i] );
    }


}
    
    /** 
  @Function
    void PmodSSD_DisplaySingleDigit( PmodSSD *ssd, uint8_t digit, bool leftSide );

  @Summary
    This function set one of the two digits on one PmodSSD.


  @Remarks
    Refer to the pmod_ssd.h interface header for function usage details.
 */
void PmodSSD_DisplaySingleDigit( PmodSSD *ssd, uint8_t digit, bool leftSide ){
    if( digit > 15 )
        return;
    if( leftSide )
        ssd->high = __decod_digit_to_7Seg[ digit ];
    else
        ssd->low  = __decod_digit_to_7Seg[ digit ];
}

    /** 
  @Function
    void PmodSSD_DisplayDecNumber( PmodSSD *ssd, uint8_t number );

  @Summary
    This function set a number in decimal base on one PmodSSD.


  @Remarks
    Refer to the pmod_ssd.h interface header for function usage details.
 */
void PmodSSD_DisplayDecNumber( PmodSSD *ssd, uint8_t number ){
    if( number > 99 ) 
        return;
    
    ssd->low =  __decod_digit_to_7Seg[ number%10 ];
    ssd->high = __decod_digit_to_7Seg[ number/10 ];
}
    

    /** 
  @Function
     void PmodSSD_DisplayHexNumber( PmodSSD *ssd, uint8_t number );

  @Summary
    This function set a number in Hex base on one PmodSSD.


  @Remarks
    Refer to the pmod_ssd.h interface header for function usage details.
 */
void PmodSSD_DisplayHexNumber( PmodSSD *ssd, uint8_t number ){
    if( number > 0xFF )
        return;
    ssd->low =  __decod_digit_to_7Seg[ number%16 ];
    ssd->high = __decod_digit_to_7Seg[ number/16 ];
}


 /** 
  @Function
    void PmodSSD_Multiplex( PmodSSD *ssd );

  @Summary
    This function is used to multiplex beetewn the two 7-SegDisp on PmodSSD.


  @Remarks
    Refer to the pmod_ssd.h interface header for function usage details.
 */
void PmodSSD_Multiplex( PmodSSD *ssd ){
    bool cat;
    int i;
    for( i = 0; i < 7; i++ )
        _PinClear( ssd->port_channel[i], ssd->pin[i] );
    
    _PinToggle( ssd->CAT_port_channel, ssd->CAT_pin );
    cat = _PinRead( ssd->CAT_port_channel, ssd->CAT_pin );
    
    if( cat ){
        for( i = 0; i < 7; i++ ){
            if( (ssd->high) & (1<<i) )
                _PinSet( ssd->port_channel[i], ssd->pin[i] );
            else
                _PinClear( ssd->port_channel[i], ssd->pin[i] );
            
        }
    }
    else{
        for( i = 0; i < 7; i++ ){
            if( (ssd->low) & (1<<i) )
                _PinSet( ssd->port_channel[i], ssd->pin[i] );
            else
                _PinClear( ssd->port_channel[i], ssd->pin[i] );        
        }
    }
    
    
}


/* *****************************************************************************
 End of File
 */
