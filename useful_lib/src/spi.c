/* 
 * File:   spi.h
 * Author: Jose Guerra Carmenate
 *
 * Created on 29 de junio de 2018
 * 
 * 
 * 
 * Summary:
 *  This file have the definition, constants and functions for use
 *  SPI modules built-in a PIC32MX with a low level of complexity.
 */

/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
/* ************************************************************************** */
#include "../spi.h"


/* ************************************************************************** */
/* ************************************************************************** */
/* Section: File Scope or Global Data                                         */
/* ************************************************************************** */
/* ************************************************************************** */
SPIMaster SPI1 = { 
    SPI_ID_1, 
    PORT_CHANNEL_D, 
    PORTS_BIT_POS_9,
    SPI_COMMUNICATION_WIDTH_8BITS,
    SPI_INPUT_SAMPLING_PHASE_AT_END,
    SPI_CLOCK_POLARITY_IDLE_HIGH,
    SPI_OUTPUT_DATA_PHASE_ON_IDLE_TO_ACTIVE_CLOCK,
    SPI_DEFAULT_BAUD_RATE
};

SPIMaster SPI2 = { 
    SPI_ID_2, 
    PORT_CHANNEL_G, 
    PORTS_BIT_POS_9, 
    SPI_COMMUNICATION_WIDTH_8BITS,
    SPI_INPUT_SAMPLING_PHASE_AT_END,
    SPI_CLOCK_POLARITY_IDLE_HIGH,
    SPI_OUTPUT_DATA_PHASE_ON_IDLE_TO_ACTIVE_CLOCK,
    SPI_DEFAULT_BAUD_RATE
};


/* ************************************************************************** */
/* ************************************************************************** */
// Section: Local Functions                                                   */
/* ************************************************************************** */
/* ************************************************************************** */
    
    static void inline SPI_SetConfiguration( SPIMaster *spi,
                              SPI_DATA_WIDTH dataWidth,
                              SPI_INPUT_SAMPLING_PHASE inputPhase,
                              SPI_CLOCK_POLARITY polarity,
                              SPI_OUTPUT_DATA_PHASE outputPhase,
                              uint32_t baudRate){
        spi->dataWidth = dataWidth;
        spi->inPhase = inputPhase;
        spi->polarity = polarity;
        spi->outPhase = outputPhase;
        spi->baudRate = baudRate;
    }
    
    static void inline SPI_SetSlaveSelectorPin( SPIMaster *spi,
                                 PORTS_CHANNEL ssChannel,
                                 PORTS_BIT_POS ssBitPos ){
    }
    
    static void inline SPI_Enable( SPIMaster *spi, uint32_t baudRate ){
        spi->baudRate = baudRate;
        
        PLIB_PORTS_PinDirectionOutputSet( PORTS_ID_0, spi->ssChannel, spi->ssBitPos );
        PLIB_PORTS_PinSet( PORTS_ID_0, spi->ssChannel, spi->ssBitPos );
        PLIB_SPI_Disable( spi->moduleId );
        PLIB_SPI_BufferClear( spi->moduleId );
        PLIB_SPI_StopInIdleDisable( spi->moduleId );
        PLIB_SPI_PinEnable( spi->moduleId, SPI_PIN_DATA_OUT );
        PLIB_SPI_CommunicationWidthSelect( spi->moduleId, spi->dataWidth );
        PLIB_SPI_InputSamplePhaseSelect( spi->moduleId, spi->inPhase );
        PLIB_SPI_ClockPolaritySelect( spi->moduleId, spi->polarity );
        PLIB_SPI_OutputDataPhaseSelect( spi->moduleId, spi->outPhase );
        PLIB_SPI_BaudRateSet( spi->moduleId, Pb_Clk, spi->baudRate );
        PLIB_SPI_MasterEnable( spi->moduleId );
        PLIB_SPI_FramedCommunicationDisable( spi->moduleId );
        asm( "nop" ); asm( "nop" ); asm( "nop" );
        PLIB_SPI_Enable( spi->moduleId );
    }
    
    static void inline SPI_StartTransaction( SPIMaster *spi ){
        PLIB_PORTS_PinClear( PORTS_ID_0, spi->ssChannel, spi->ssBitPos );
    }
    
    static uint8_t inline SPI_Transfer( SPIMaster *spi, uint8_t data ){
        PLIB_SPI_BufferWrite( spi->moduleId, data );
        while( !PLIB_SPI_ReceiverBufferIsFull( spi->moduleId ) );
        return PLIB_SPI_BufferRead( spi->moduleId );
    }
    
    static uint16_t inline SPI_Transfer16bits( SPIMaster *spi, uint16_t data ){
        PLIB_SPI_BufferWrite16bit( spi->moduleId, data );
        while( !PLIB_SPI_ReceiverBufferIsFull( spi->moduleId ) );
        return PLIB_SPI_BufferRead16bit( spi->moduleId );
    }
    
    static uint32_t inline SPI_Transfer32bits(SPIMaster *spi, uint32_t data ){
        PLIB_SPI_BufferWrite32bit( spi->moduleId, data );
        while( !PLIB_SPI_ReceiverBufferIsFull( spi->moduleId ) );
        return PLIB_SPI_BufferRead32bit( spi->moduleId );
    }
    
    static void inline SPI_EndTransaction( SPIMaster *spi ){
        PLIB_PORTS_PinSet( PORTS_ID_0, spi->ssChannel, spi->ssBitPos );
    }
    

/* ************************************************************************** */
/* ************************************************************************** */
// Section: Interface Functions                                               */
/* ************************************************************************** */
/* ************************************************************************** */

  
    /*------------------------------------------------------------------------*/
    /* SPI1 Interface Functions                                               */
    /*------------------------------------------------------------------------*/
    
    
    void SPI1_SetConfiguration( SPI_DATA_WIDTH datawidth,
                              SPI_INPUT_SAMPLING_PHASE inputPhase,
                              SPI_CLOCK_POLARITY polarity,
                              SPI_OUTPUT_DATA_PHASE outputPhase,
                              uint32_t baudRate){
        SPI_SetConfiguration( &SPI1, datawidth, inputPhase, polarity, outputPhase, baudRate);
    }
    
    void SPI1_SetSlaveSelectorPin( PORTS_CHANNEL ssChannel, PORTS_BIT_POS ssBitPos ){
        SPI_SetSlaveSelectorPin( &SPI1, ssChannel, ssBitPos );
    }
    
    void SPI1_Enable( uint32_t baudRate ){
        SPI_Enable( &SPI1, baudRate );
    }
    
    void SPI1_StartTransaction(  ){
        SPI_StartTransaction( &SPI1 );
    }
    
    uint8_t SPI1_Transfer( uint8_t data ){
        SPI_Transfer( &SPI1, data );
    }
    
    uint16_t SPI1_Transfer16bits( uint16_t data ){
        SPI_Transfer16bits( &SPI1, data );
    }
    
    uint32_t SPI1_Transfer32bits( uint32_t data ){
        SPI_Transfer32bits( &SPI1, data );
    }
    
    void SPI1_EndTransaction( ){
        SPI_EndTransaction( &SPI1 );
    }
    
    
    /*------------------------------------------------------------------------*/
    /* SPI2 Interface Functions                                               */
    /*------------------------------------------------------------------------*/
    
    
    void SPI2_SetConfiguration( SPI_DATA_WIDTH datawidth,
                              SPI_INPUT_SAMPLING_PHASE inputPhase,
                              SPI_CLOCK_POLARITY polarity,
                              SPI_OUTPUT_DATA_PHASE outputPhase,
                              uint32_t baudRate){
        SPI_SetConfiguration( &SPI2, datawidth, inputPhase, polarity, outputPhase, baudRate);
    }
    
    void SPI2_SetSlaveSelectorPin( PORTS_CHANNEL ssChannel, PORTS_BIT_POS ssBitPos ){
        SPI_SetSlaveSelectorPin( &SPI2, ssChannel, ssBitPos );
    }
    
    void SPI2_Enable( uint32_t baudRate ){
        SPI_Enable( &SPI2, baudRate );
    }
        
    void SPI2_StartTransaction(  ){
        SPI_StartTransaction( &SPI2 );
    }
    
    uint8_t SPI2_Transfer( uint8_t data ){
        SPI_Transfer( &SPI2, data );
    }
    
    uint16_t SPI2_Transfer16bits( uint16_t data ){
        SPI_Transfer16bits( &SPI2, data );
    }
    
    uint32_t SPI2_Transfer32bits( uint32_t data ){
        SPI_Transfer32bits( &SPI2, data );
    }
    
    void SPI2_EndTransaction( ){
        SPI_EndTransaction( &SPI2 );
    }
    



/* ------------------------------------------------------------ */
/*        LM35_RETURN_CODE LM35_Attach( LM35Sensor *sensor, uint8_t analogChannel )
* 
*         Synopsis:
*           LM35_Attach( &sensor, analogChannel );
*  
*         Parameters:
*           LM35Sensor* sensor - LM35 sensor identifier
*           uint8_t analogChannel - analog channel to use.
* 
*         Return Values:
*           LM35_RETURN_CODE
*  
*         Description:
*           Attach one LM35 temperature sensor on an specified analogChannel.
*           This function check that the analog channel is a valid channel and
*          store the configuration on 'sensor' var.
*           
*/
/*LM35_RETURN_CODE LM35_Attach( LM35Sensor *sensor, uint8_t _analogChannel ){
    if( _analogChannel > 15 )
        return LM35_RETURN_CODE_ANALOG_CHANNEL_INVALID;

    sensor->analogChannel = _analogChannel;
    
    return LM35_RETURN_CODE_SUCCESSFUL;
 }*/



/* ------------------------------------------------------------ */
/*        float LM35_GetTemperature( LM35Sensor sensor, SENSOR_TEMPERATURE_UNIT unit )
* 
*         Synopsis:
*           LM35_GetTemperature( sensor, unit );
*  
*         Parameters:
*           LM35Sensor sensor - LM35 sensor identifier
*           SENSOR_TEMPERATURE_UNIT unit - define the unit of returned value
*
*           
*         Return Values:
*           float - Temperature on the selected unit
*  
*         Description:
*           Return the temperature on the selected unit.
*           
*/
/*float LM35_GetTemperature( LM35Sensor *sensor, SENSOR_TEMPERATURE_UNIT unit ){
    uint32_t raw = analogRead( sensor->analogChannel );
    float Ta = ((float)(raw*3300))/(10240.0);

    if( unit == SENSOR_TEMPERATURE_UNIT_FAHRENHEIT )
        Ta = TEMPERATURE_ConvertCelsiusToFahrenheit( Ta );
    else if( unit == SENSOR_TEMPERATURE_UNIT_KELVIN )
        Ta = TEMPERATURE_ConvertCelsiusToKelvin( Ta );
    
    return Ta;
}*/


/* *****************************************************************************
 End of File
 */
