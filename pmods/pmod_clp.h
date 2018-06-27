/* 
 * File:   pmod_clp.h
 * Author: jose
 *
 * Created on 4 de mayo de 2018, 12:55
 */

#ifndef _PMOD_CLP_LIB_H
#define	_PMOD_CLP_LIB_H

#include "pmod_tools.h"
#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>

/**Macros**/
/*Command macros*/

#define CLP_CMD_LcdFcnInit 0x38                 // function set command ( 8-bit interface, 2-lines and 5x8 dots )
#define CLP_CMD_LcdCtrInit 0x08                 // display on/off control ( no display, no cursor, no blinking cursor )
#define CLP_CMD_LcdClear  0x01                  // clear display command
#define CLP_CMD_LcdRetHome 0x02                 // Return home command
#define CLP_CMD_LcdDisplayShift 0x18            // DisplayShift command
#define CLP_CMD_LcdCursorShift 0x10             // Cursor shift command
#define CLP_CMD_LcdSetDdramPos	0x80            // set DDRAM position command
#define CLP_CMD_LcdSetCgramPos	0x40            // set CGRAM position command

#define CLP_MSK_BusyStatus 0x80                 // mask of bit busy
#define CLP_MSK_ShiftRL    0x04                 // shift direction mask

#define CLP_OPT_DisplayOn 0x4                   // Set display on option
#define CLP_OPT_CursorOn  0x2                   // Set cursor on option
#define CLP_OPT_BlinkOn   0x1                   // Set blink on option

#define CLP_READ_DATA true
#define CLP_READ_STATUS false

/*Error Macros*/

#define CLP_ERROR_SUCCESS       0               // The action completed successfully 
#define CLP_ERROR_ARG_ROW_RANGE 0x80            // The row index is not valid
#define CLP_ERROR_ARG_COL_RANGE 0x40            // The column index is not valid 
#define CLP_ERROR_UCHAR_POSITION_INVALID 0x20   // The user character position is not correct

/*Limits Macros*/

#define CLP_NO_ROW 2
#define CLP_NO_COL 40
#define CLP_NO_UCHARS 8

/*Attach Macros*/

/*Args for connect the PmodCLP on JA and JB connectors*/
#define CLP_32MX4_Attached_JA_JB_ARGS &PORTB, 14, &PORTB, 15, &PORTD, 5, &PORTD, 4, &PORTE, 0, &PORTE, 1, &PORTE, 2, &PORTE, 3, &PORTE, 4, &PORTE, 5, &PORTE, 6, &PORTE, 7
//#define CLP_32MX4_Attached_JB_JC_ARGS
//#define CLP_32MX4_Attached_JC_JD_ARGS
//#define CLP_32MX4_Attached_JE_JF_ARGS
//#define CLP_32MX4_Attached_JH_JJ_ARGS
//#define CLP_32MX4_Attached_JJ_JK_ARGS

/**Data Types**/

typedef struct _pmod_clp{
    uint8_t byte_display_mode; // Blink, Cursor, DisplayON
    
    uint32_t bkl_port_channel, //backlight port
             bkl_pin;          //backlight pin
    /*
     * Register Select: 
     *   - High for Data transfer 
     *   - Low for intruction Transfer
     */
    uint32_t rs_port_channel, //Register Select port
             rs_pin;          //Register Select pin
    
    /*
     * Read/Write Signal:
     *   - High for read mode
     *   - Low for write mode
     */
    uint32_t rw_port_channel,  // Read/Write Signal port
             rw_pin;           // Read/Write Signal pin
    
    /*
     * Read/Write Enable:
     *   - High for Read
     *   - Falling edge write data
     */
    uint32_t enable_port_channel, //Read/Write Enable port
             enable_pin;          //Read/Write Enable pin
    
    uint32_t data_port_channel[8];  //Ports for data transfer
    uint8_t data_pin[8];            //Pin for data transfer
    
} PmodCLP;

/**Functions**/

/*Private Function*/


/*        
          __CLP_ReadByte

          @Synopsis
            __CLP_ReadByte( typeOfRead )
          
		  @Parameters
            bool typeOfRead - true for read data and false for read status.
  
          @Return
            uint8_t - the byte that was read
  
          @Errors
  
          @Description
		    The function implements a CLP read sequence. 
			The function is used to read data or to read status.
*/
inline uint8_t __CLP_ReadByte( PmodCLP *clp ){
    uint8_t i, byteData = 0;
    
    _PinSet( clp->rw_port_channel, clp->rw_pin ); // read mode
    _PinSet( clp->enable_port_channel, clp->enable_pin ); // enable
    for( i = 0; i < 8; i++ )
        _PinDirectionInputSet( clp->data_port_channel[i], clp->data_pin[i] );
    asm volatile("nop");
    asm volatile("nop");    
    for( i = 0; i < 8; i++ ){
        byteData += ((uint8_t)_PinRead( clp->data_port_channel[i], clp->data_pin[i] )) << i;
    }
    
    _PinClear( clp->enable_port_channel, clp->enable_pin ); // disable
    _PinClear( clp->rw_port_channel, clp->rw_pin );  // read mode out
    
    return byteData;
}

/* ------------------------------------------------------------ */
/*        __CLP_WriteByte

          @Synopsis
            __CLP_WriteByte( cmd_data, byteData )
          @Parameters
  		    uint8_t byteData - data to be written to display
            bool cmd_data - true for write data and false for write command
  
          @Return
            void 
  
          @Errors
            None

          @Description:
            The function implements a CLP write sequence. 
            The function is used to write data (RS set before calling this function) or to write commands (RS cleared before calling this function).
            When writing data it writes in DDRAM or CGRAM according to the last set write position.
*/
inline void __CLP_WriteByte( PmodCLP* clp, uint8_t byteData ){
    int i;
    _PinClear( clp->rw_port_channel, clp->rw_pin ); // write mode
    asm volatile("nop");
    _PinSet( clp->enable_port_channel, clp->enable_pin );//enable
    asm volatile("nop");
    for( i = 0; i < 8; i++ )
        _PinDirectionOutputSet( clp->data_port_channel[i], clp->data_pin[i] );
    
    asm volatile("nop");
    
    for( i = 0; i < 8; i++ ){
        _PinWrite( clp->data_port_channel[i], clp->data_pin[i], ((byteData>>i) & 1) );
    }

    asm volatile("nop");
    _PinClear( clp->enable_port_channel, clp->enable_pin );//write and disable

    asm volatile("nop");
    _PinSet( clp->rw_port_channel, clp->rw_pin ); // write mode out
    
}

/* ------------------------------------------------------------ */
/*        __CLP_ReadStatus

          @Synopsis
            __CLP_ReadStatus( &my_clp );
          @Parameters
  
  
          @Return
            uint8_t - the byte that was read.

          @Errors
            None
          @Description:
  			Reads the status of the CLP. It calls ReadByte( false ) function.

*/
inline uint8_t __CLP_ReadStatus( PmodCLP* clp ){
    uint8_t status;
    _PinClear( clp->rs_port_channel, clp->rs_pin );
    
    status = __CLP_ReadByte( clp );
    return status;
}


/* ------------------------------------------------------------ */
/*        __CLP_WaitUntilNoBusy
**
**        Synopsis:
**				__CLP_WaitUntilNoBusy( &my_clp );
**        Parameters:
**		
**
**        Return Values:
**                void 
**
**        Errors:
**
**
**        Description:
**				Waits until the status of the CLP is not busy. This function 
 *          relies on ReadStatus().
**
**
*/
inline void __CLP_WaitUntilNoBusy( PmodCLP *clp ){
    uint8_t byteStatus = 0;
    
	byteStatus = __CLP_ReadStatus(clp);
	while (byteStatus & CLP_MSK_BusyStatus)
	{
		delay_us(10);
		byteStatus = __CLP_ReadStatus(clp);
	}
}


/* ------------------------------------------------------------ */
/*        WriteCommand
**
**        Synopsis:
**				WriteCommand( &my_clp, byteCmd);
**        Parameters:
**				uint8_t byteCmd - the command code byte
**
**
**        Return Values:
**                void 
**
**        Errors:
**
**
**        Description:
**				Writes the specified byte as command. When the device is ready it clears the RS and writes byte.
**
**
*/
inline void __CLP_WriteCommand( PmodCLP *clp, uint8_t byteCmd ){
    __CLP_WaitUntilNoBusy( clp );
    
    _PinClear( clp->rs_port_channel, clp->rs_pin ); // active for command write
    
    __CLP_WriteByte( clp, byteCmd );
}

/* ------------------------------------------------------------ */
/*        __CLP_WriteDataByte
**
**        Synopsis:
**				__CLP_WriteDataByte( &my_clp, byteData);
**        Parameters:
**				uint8_t byteData		- the data byte
**
**
**        Return Values:
**                void 
**
**        Errors:
**
**
**        Description:
**				Writes the specified byte as data. When the device is ready it 
 *          sets the RS and writes byte.
**
**
*/
inline void __CLP_WriteDataByte( PmodCLP *clp, uint8_t byteData ){
    __CLP_WaitUntilNoBusy( clp );
    
    _PinSet( clp->rs_port_channel, clp->rs_pin );
    __CLP_WriteByte( clp, byteData );
}

/* ------------------------------------------------------------ */
/*        __CLP_SetWriteCgramPosition
**
**        Synopsis:
**				__CLP_SetWriteCgramPosition( &my_clp, bAdr);
**        Parameters:
**				uint8_t bAdr - the write location. The position in CGRAM where 
 *                  the next data writes will put bytes.
**
**
**        Errors:
**
**
**        Description:
**				Sets the CGRAM write position. This is the location where the 
 *          next data write will be performed.
**				Be aware that writing to a location auto-increments the write 
 *          location.
**
*/
inline void __CLP_SetWriteCgramPosition( PmodCLP *clp, uint8_t byteAdr ){
    uint8_t byteCmd = CLP_CMD_LcdSetCgramPos | byteAdr;
    __CLP_WriteCommand( clp, byteCmd );
}


/* ------------------------------------------------------------ */
/*        __CLP_SetWriteDdramPosition
**
**        Synopsis:
**				__CLP_SetWriteDdramPosition( &my_clp, bAddrOffset);
**        Parameters:
**				uint8_t bAdr - the write location. The position in DDRAM 
 *          where the next data writes will put bytes.
**					0x00-0x27 refer to the first row
**					0x40-0x67 refer to the second row
**
**
**        Errors:
**
**
**        Description:
**				Sets the DDRAM write position. This is the location where the 
 *          next data write will be performed.
**				Be aware that writing to a location auto-increments the write 
 *          location.
**
*/
inline void __CLP_SetWriteDdramPosition( PmodCLP* clp, uint8_t byteAdr ){
    uint8_t byteCmd = CLP_CMD_LcdSetDdramPos | byteAdr;
    __CLP_WriteCommand( clp, byteCmd );
}


/*Public Function*/

/* ------------------------------------------------------------ */
/*        PmodCLP_Attach
**
**        Synopsis:
**				
**        Parameters:
 *              PmodCLP*    my_clp      - CLP Pmod to be used
 *              port*   bkl_port    - the port corresponding to Backlight pin
**				uint8_t     bkl_pin     - the pin corresponding to Backlight pin
**				port*   rs_port     - the port corresponding to RS pin
**				uint8_t     rs_pin      - the pin corresponding to RS pin
**				port*   rw_port     - the port corresponding to RW pin
**				uint8_t     rw_pin      - the pin corresponding to RW pin
**				port*   enable_port - the port corresponding to Enable pin
**				uint8_t     enable_pin  - the pin corresponding to Enable pin
**				
 * 
**				port*       d0_port - the port corresponding to D0 pin
 *              uint8_t     d0_pin	- the pin corresponding to D0 pin
**				port*       d1_port - the port corresponding to D1pin
**				uint8_t     d1_pin	- the pin corresponding to D1 pin
**				port*       d2_port - the port corresponding to D2 pin
**				uint8_t     d2_pin	- the pin corresponding to D2 pin
**				port*       d3_port - the port corresponding to D3 pin
**				uint8_t     d3_pin	- the pin corresponding to D3 pin
**				port*       d4_port - the port corresponding to D4 pin
**				uint8_t     d4_pin	- the pin corresponding to D4 pin
**				port*       d5_port - the port corresponding to D5 pin
**				uint8_t     d5_pin	- the pin corresponding to D5 pin
**				port*       d6_port - the port corresponding to D6 pin
**				uint8_t     d6_pin	- the pin corresponding to D6 pin
**				port*       d7_port - the port corresponding to D7 pin
**				uint8_t     d7_pin	- the pin corresponding to D7 pin
**
**        Return Values:
**
**        Errors:
**
**
**        Description:
**				This function saves the ports and pins corresponding to the 
 *              PmodCLP and performs the required LCD initialization tasks.
**
**
*/
void PmodCLP_Attach( PmodCLP *display, port *bkl_port, uint8_t bkl_pin,
        port *rs_port, uint8_t rs_pin, port *rw_port, uint8_t rw_pin,
        port *enable_port, uint8_t enable_pin, 
        port *d0_port, uint8_t d0_pin, port *d1_port, uint8_t d1_pin,
        port *d2_port, uint8_t d2_pin, port *d3_port, uint8_t d3_pin,
        port *d4_port, uint8_t d4_pin, port *d5_port, uint8_t d5_pin,
        port *d6_port, uint8_t d6_pin, port *d7_port, uint8_t d7_pin);

/* ------------------------------------------------------------ */
/*        PmodCLP_DisplayClear
**
**        Synopsis:
**				PmodCLP_DisplayClear( &my_clp );
**        Parameters:
**
**
**        Return Values:
**                void 
**
**        Errors:
**
**
**        Description:
**				Clears the display and returns the cursor home (upper left corner).
**
**
*/
inline void PmodCLP_DisplayClear( PmodCLP *display ){
    __CLP_WriteCommand( display, CLP_CMD_LcdClear );
}

/* ------------------------------------------------------------ */
/*        PmodCLP_ReturnHome
**
**        Synopsis:
**				PmodCLP_ReturnHome( &my_clp );
**        Parameters:
**
**
**        Return Values:
**                void 
**
**        Errors:
**
**
**        Description:
**				Returns the cursor home (upper left corner).
**
**
*/
inline void PmodCLP_ReturnHome( PmodCLP *display ){
    __CLP_WriteCommand( display, CLP_CMD_LcdRetHome );
}


/* ------------------------------------------------------------ */
/*        PmodCLP_SetDisplay
**
**        Synopsis:
**				PmodCLP_SetDisplay( &my_clp, displayOn );
**        Parameters:
**				bool displayOn - Display option
**						- true in order to set the display ON	
**						- false in order to set the display OFF
**
**
**        Return Values:
**
**        Errors:
**
**
**        Description:
**				Sets the display option. If true, display is on, if false, 
 *          the display is off.
**
*/
inline void PmodCLP_SetDisplay( PmodCLP *clp, bool displayOn ){
    if( displayOn ){
        clp->byte_display_mode |= CLP_OPT_DisplayOn;
    }
    else{
        clp->byte_display_mode &= ~CLP_OPT_DisplayOn;
    }
    
    __CLP_WriteCommand( clp, CLP_CMD_LcdCtrInit | clp->byte_display_mode );
     
}


/* ------------------------------------------------------------ */
/*        PmodCLP_SetCursor
**
**        Synopsis:
**              PmodCLP_SetCursor( &my_clp, cursorOn);
**        Parameters:
**	            bool cursorOn - Cursor option
**	                    - true in order to set the Cursor ON	
**	                    - false in order to set the Cursor OFF
**
**
**        Return Values:
**
**        Errors:
**
**
**        Description:
**				Sets the cursor option. If true, Cursor is on, if false, the 
 *          Cursor is off.
**
*/
inline void PmodCLP_SetCursor( PmodCLP *display, bool cursorOn ){
    if( cursorOn )
        display->byte_display_mode |= CLP_OPT_CursorOn;
    else
        display->byte_display_mode &= ~CLP_OPT_CursorOn;
    __CLP_WriteCommand( display, CLP_CMD_LcdCtrInit | display->byte_display_mode );
}


/* ------------------------------------------------------------ */
/*        PmodCLP_SetBlink
**
**        Synopsis:
**				PmodCLP_SetBlink( &my_clp, blinkOn);
**        Parameters:
**				bool blinkOn - Blink option
**						- true in order to set the Blink ON	
**						- false in order to set the Blink OFF
**
**
**        Return Values:
**
**        Errors:
**
**
**        Description:
**				Sets the Blink option. If true, Blink is on, if false, the 
 *          Blink is off.
**
*/
inline void PmodCLP_SetBlink( PmodCLP *display, bool blinkOn ){
    if( blinkOn )
        display->byte_display_mode |= CLP_OPT_BlinkOn;
    else
        display->byte_display_mode &= ~CLP_OPT_BlinkOn;
    
    __CLP_WriteCommand( display, CLP_CMD_LcdCtrInit | display->byte_display_mode );
}


/* ------------------------------------------------------------ */
/*        PmodCLP_SetBacklight
**
**        Synopsis:
**				PmodCLP_SetBacklight( &my_clp, backlightOn);
**        Parameters:
**				bool backlightOn - Backlight option
**						- true in order to set the backlight ON	
**						- false in order to set the backlight OFF
**
**
**        Return Values:
**                void 
**
**        Errors:
**
**
**        Description:
**				This function turns the backlight on or off, according to the 
 *          user's selection.
**				Note that there are CLP Pmods that do not have backlight 
 *          functionality. Using this function for this type of modules will 
 *          have no effect.
**
**
*/
inline void PmodCLP_SetBacklight( PmodCLP *display, bool backlightOn ){
    _PinWrite( display->bkl_port_channel, display->bkl_pin, backlightOn );
}


/* ------------------------------------------------------------ */
/*        PmodCLP_SetPosition
**
**        Synopsis:
**				PmodCLP_SetPosition(&my_clp, idxLine, idxCol);
**        Parameters:
**				uint8_t idxLine	- the line where the position will be set
**				uint8_t idxCol	- the column where the position will be set
**
**
**        Return Value:
**                uint8_t 
**					- CLP_ERROR_SUCCESS (0) 	- The action completed successfully 
**					- a combination (OR-ed) of the following errors:
**						- CLP_ERROR_ARG_ROW_RANGE (0x80) - The row index is not valid
**						- CLP_ERROR_ARG_COL_RANGE (0x40) - The column index is not valid 
**						
**
**        Errors:
**				See Return Value
**
**        Description:
**				This function sets the corresponding LCD position. This is used 
 *          for write position and cursor position.
**				If position set is invalid (outside the display), errors are 
 *          returned.
**
**
*/
uint8_t PmodCLP_SetPosition( PmodCLP *display, uint8_t idxLine, uint8_t idxCol );



/* ------------------------------------------------------------ */
/*        PmodCLP_WriteStringAtPosition
**
**        Synopsis:
**				PmodCLP_WriteStringAtPosition( &my_clp, str, idxLine, idxCol);
**        Parameters:
**				char *str	- string to be written to LCD
**				uint8_t idxLine	- the line where the string will be displayed
**				uint8_t idxCol	- the column line where the string will be displayed
**
**
**        Return Value:
**                uint8_t 
**					- CLP_ERROR_SUCCESS (0) 	- The action completed successfully 
**					- a combination (OR-ed) of the following errors:
**						- CLP_ERROR_ARG_ROW_RANGE (0x80) - The row index is not valid
**						- CLP_ERROR_ARG_COL_RANGE (0x40) - The column index is not valid 
**						
**
**        Errors:
**				See Return Value
**
**        Description:
**				The function writes the specified string at the specified 
 *          position (line and column). 
**				It sets the corresponding write position and then writes 
 *          data bytes when the device is ready.
**				Strings that span over the end of line are trimmed so 
 *          they fit in the line.
**				If position is invalid (outside the display), errors are 
 *          returned.
**
*/
inline uint8_t PmodCLP_WriteStringAtPosition( PmodCLP *display, char *str, uint8_t idxLine, uint8_t idxCol ){
    uint8_t len, i;
    uint8_t returnCode = PmodCLP_SetPosition( display, idxLine, idxCol);
    
    if( returnCode == CLP_ERROR_SUCCESS ){
       len = strlen( str );
       if( len + idxCol > CLP_NO_COL )
           len = CLP_NO_COL - idxCol;
       
       for( i = 0; i < len; i++ )
           __CLP_WriteDataByte( display, str[i] );
       
    }
    
    return returnCode;    
}

/* ------------------------------------------------------------ */
/*        PmodCLP_DisplayShift
**
**        Synopsis:
**				PmodCLP_DisplayShift(&my_clp, right );
**        Parameters:
**				bool right - parameter indicating the direction of the display shift
**						- true in order to shift the display right
**						- false in order to shift the display left
**
**        Return Values:
**                void 
**
**        Errors:
**
**
**        Description:
**				This function shifts the display one position right or left, 
 *          depending on the right parameter.
**
**
**
*/
void PmodCLP_DisplayShift( PmodCLP *display, bool right ){
    uint8_t byteCmd = CLP_CMD_LcdDisplayShift | ( right?CLP_MSK_ShiftRL:0 );
    __CLP_WriteCommand( display, byteCmd );
}


/* ------------------------------------------------------------ */
/*        PmodCLP_CursorShift
**
**        Synopsis:
**				PmodCLP_CursorShift( &my_clp, right);
**        Parameters:
**				bool right - parameter indicating the direction of the cursor shift
**						- true in order to shift the cursor right
**						- false in order to shift the cursor left
**
**        Return Values:
**                void 
**
**        Errors:
**
**
**        Description:
**				This function shifts the cursor one position right or left, 
 *          depending on the fRight parameter.
**
**
*/
inline void PmodCLP_CursorShift( PmodCLP *display, bool right ){
    uint8_t byteCmd = CLP_CMD_LcdCursorShift | ( right?CLP_MSK_ShiftRL:0 );
    __CLP_WriteCommand( display, byteCmd );
}


/* ------------------------------------------------------------ */
/*        PmodCLP_DefineUserChar
**
**        Synopsis:
**				PmodCLP_DefineUserChar( &my_clp, pointerBytes, byteCharNo);
**        Parameters:
**				uint8_t *pointerBytes	- pointer to the string that contains the 8 bytes definition of the character. 
**				uint8_t byteCharNo      - the position of the user character to be saved in the memory 
**
**        Return Values:
**                uint8_t 
**					- LCDP_ERROR_SUCCESS (0) 				- The action completed successfully 
**					- LCDP_ERROR_UCHAR_POSITION_INVALID	(0x20) - The user character position is not within 0 - 7 
**
**        Errors:
**
**
**        Description:
**				This function writes the specified number of bytes to CGRAM 
 *          starting at the specified position.
**				It sets the corresponding write position and then writes 
 *          data bytes when the device is ready.
**				If the user character position is not within 0 - 7 range, 
 *          error is returned. 
**
*/
uint8_t PmodCLP_DefineUserChar( PmodCLP *display, uint8_t *pByte, uint8_t CharNo );


/* ------------------------------------------------------------ */
/*        PmodCLP_WriteUserCharsAtPosition
**
**        Synopsis:
**				PmodCLP_WriteUserCharsAtPosition( &my_clp, rgCharPos, idxLine, idxCol);
**        Parameters:
**				uint8_t* rgCharPos  - an array containing the index (position) 
 *          of the user characters to be displayed 
**				uint8_t* bNoChars   - an array containing the index (position) 
 *          of the user characters to be displayed
**				uint8_t idxLine 	- line where the string will be displayed
**				uint8_t idxCol      - the starting position of the string 
 *          within the line

**
**        Return Value:
**                uint8_t 
**					- LCDP_ERROR_SUCCESS (0) 	- The action completed successfully 
**					- a combination (ORed) of the following errors:
**						- LCDP_ERROR_ARG_ROW_RANGE (0x80) - The row index is not valid
**						- LCDP_ERROR_ARG_COL_RANGE (0x40) - The column index is not valid 
**						- LCDP_ERROR_UCHAR_POSITION_INVALID	(0x20) - The user character position is not within the accepted range (0 \96 7)
**
**	Errors:
**		none
**
**	Description:
**		This function displays one or more user defined characters at the 
 *      specified positions on the LCD. 
**		If the position set or the user character position is not correct, 
 *      errors are returned.
**		
**
**
**/
uint8_t PmodCLP_WriteUserCharsAtPosition( PmodCLP *my_clp, uint8_t *rg_char_pos, uint8_t b_no_chars, uint8_t idx_line, uint8_t idx_col);

#endif	/* PMOD_CLP_H */

