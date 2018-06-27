/* 
 * File:   pmod_clp.c
 * Author: Jose Guerra Carmenate
 *
 * Created on 4 de mayo de 2018, 12:55
 */

#include "../pmod_clp.h"


void PmodCLP_Attach( PmodCLP *clp, port *bkl_port, uint8_t bkl_pin,
        port *rs_port, uint8_t rs_pin, port *rw_port, uint8_t rw_pin,
        port *enable_port, uint8_t enable_pin, 
        port *d0_port, uint8_t d0_pin, port *d1_port, uint8_t d1_pin,
        port *d2_port, uint8_t d2_pin, port *d3_port, uint8_t d3_pin,
        port *d4_port, uint8_t d4_pin, port *d5_port, uint8_t d5_pin,
        port *d6_port, uint8_t d6_pin, port *d7_port, uint8_t d7_pin){
    
    clp->bkl_port_channel = _GetPortChannel( bkl_port );
    clp->bkl_pin = bkl_pin;
    
    clp->rs_port_channel = _GetPortChannel( rs_port );
    clp->rs_pin = rs_pin;
    
    clp->rw_port_channel = _GetPortChannel( rw_port );
    clp->rw_pin = rw_pin;
    
    clp->enable_port_channel = _GetPortChannel( enable_port );
    clp->enable_pin = enable_pin;
    
    clp->data_port_channel[0] = _GetPortChannel(d0_port);
    clp->data_port_channel[1] = _GetPortChannel(d1_port);
    clp->data_port_channel[2] = _GetPortChannel(d2_port);
    clp->data_port_channel[3] = _GetPortChannel(d3_port);
    clp->data_port_channel[4] = _GetPortChannel(d4_port);
    clp->data_port_channel[5] = _GetPortChannel(d5_port);
    clp->data_port_channel[6] = _GetPortChannel(d6_port);
    clp->data_port_channel[7] = _GetPortChannel(d7_port);
    
    clp->data_pin[0] = d0_pin;
    clp->data_pin[1] = d1_pin;
    clp->data_pin[2] = d2_pin;
    clp->data_pin[3] = d3_pin;
    clp->data_pin[4] = d4_pin;
    clp->data_pin[5] = d5_pin;
    clp->data_pin[6] = d6_pin;
    clp->data_pin[7] = d7_pin;
    
    _PinDirectionOutputSet( clp->bkl_port_channel, clp->bkl_pin );
    _PinDirectionOutputSet( clp->enable_port_channel, clp->enable_pin );
    _PinDirectionOutputSet( clp->rs_port_channel, clp->rs_pin );
    _PinDirectionOutputSet( clp->rw_port_channel, clp->rw_pin );
    
    //perform initialization sequence, according to PmodCLP reference manual
    delay_ms(20);
    __CLP_WriteCommand( clp, CLP_CMD_LcdFcnInit );
    delay_us( 400 );
    PmodCLP_SetDisplay( clp, true );
    delay_us( 400 );
    PmodCLP_DisplayClear( clp );
    delay_ms( 20 );

}

uint8_t PmodCLP_SetPosition( PmodCLP *display, uint8_t idxLine, uint8_t idxCol ){
    uint8_t returnCode = CLP_ERROR_SUCCESS;
    uint8_t byteAdrOffset;
    if( idxLine >= CLP_NO_ROW )
        returnCode |= CLP_ERROR_ARG_ROW_RANGE;
    if( idxCol >= CLP_NO_COL )
        returnCode |= CLP_ERROR_ARG_COL_RANGE;
    
    if( returnCode == CLP_ERROR_SUCCESS ){
        byteAdrOffset = ((idxLine == 0)?0:0x40) + idxCol;
        __CLP_SetWriteDdramPosition( display, byteAdrOffset );
    }
        
    
    return returnCode;
}

uint8_t PmodCLP_DefineUserChar( PmodCLP *display, uint8_t *pByte, uint8_t CharNo ){
    uint8_t byteAdr, i;
    uint8_t returnCode = CLP_ERROR_SUCCESS;
    
    if( CharNo >= CLP_NO_UCHARS )
        returnCode = CLP_ERROR_UCHAR_POSITION_INVALID;
    
    if( returnCode == CLP_ERROR_SUCCESS ){
        byteAdr = CharNo << 3;
        __CLP_SetWriteCgramPosition( display, byteAdr );
        
        for( i = 0; i < 8; i++ ){
            __CLP_WriteDataByte( display, pByte[i] );
        }
        
    }
    
    return returnCode;
}

uint8_t PmodCLP_WriteUserCharsAtPosition( PmodCLP *display, uint8_t *rgCharPos, uint8_t noChars, uint8_t idxLine, uint8_t idxCol){
    uint8_t i, byteAddrOffset;
    uint8_t returnCode = PmodCLP_SetPosition( display, idxLine, idxCol );
    
    if( returnCode == CLP_ERROR_SUCCESS ){
        
        //check the array positions
        for( i = 0; i < noChars ; i++ ){
            if( rgCharPos[i] < 0 || rgCharPos[i] >= CLP_NO_UCHARS ){
                returnCode |= CLP_ERROR_UCHAR_POSITION_INVALID;
                break;
            }
        }
        if( returnCode == CLP_ERROR_SUCCESS ){
            byteAddrOffset = ((idxLine==0)?0:0x40) + idxCol;
            __CLP_SetWriteDdramPosition( display, byteAddrOffset );
            
            for( i = 0; i < noChars; i++ ){
                __CLP_WriteDataByte( display, rgCharPos[i] );
            }
        }
        
    }
    
    return returnCode;
}


/*
 * 
 */
