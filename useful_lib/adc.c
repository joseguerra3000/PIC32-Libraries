/* 
 * File:   adc.c
 * Author: Jose Guerra Carmenate
 *
 * Created on 18 de mayo de 2018, 2:30
 */

#include "adc.h"
#include <peripheral/peripheral.h>
/*
 * 
 */

void ADC_SetUp( uint32_t desiredAdcClock){
    // Disabling ADC peripherial */
    //AD1CON1bits.ON = 0;
    PLIB_ADC_Disable( ADC_ID_1 );
    asm("nop");asm("nop");
    // Internal Counter triggers conversion
    //AD1CON1bits.SSRC = 0x7;
    PLIB_ADC_ConversionTriggerSourceSelect( ADC_ID_1, ADC_CONVERSION_TRIGGER_INTERNAL_COUNT );
    // Disabling ADC Input channels for Scan
    AD1CSSLCLR = 0xFFFF;
    
    // Sample Time = 31TAD and TAD = 
    // AD1CON3bits.SAMC = 30;
    PLIB_ADC_SampleAcquisitionTimeSet(ADC_ID_1, 0x1F);
    // Sets the ADC module conversion clock prescaler.
    PLIB_ADC_ConversionClockSet(ADC_ID_1, Pb_Clk, desiredAdcClock );
    // Set the interrupt every 8 samples
    PLIB_ADC_SamplesPerInterruptSelect(ADC_ID_1, ADC_8SAMPLES_PER_INTERRUPT);
    PLIB_ADC_VoltageReferenceSelect( ADC_ID_1, ADC_REFERENCE_VDD_TO_AVSS );
}


uint16_t ADC_Read( uint8_t analogChannel ){
    if( analogChannel > 15  )
        return 0;
    PLIB_ADC_Disable( ADC_ID_1 );
    uint16_t adcValue = 0;
    uint16_t analogMask = ((uint16_t)1)<<analogChannel;
    bool prevAD1PCFGState = ((AD1PCFG & analogMask) != 0)?true:false;
    //bool prevTRISB_State = ((TRISB & analogMask ) != 0) ?true:false;
    AD1PCFGCLR = analogMask;
    // Connect analogChannel as Positive Input
    //PLIB_ADC_MuxChannel0InputPositiveSelect(ADC_ID_1, ADC_MUX_A, ADC_INPUT_POSITIVE_AN3);
    AD1CHSbits.CH0SA = analogChannel;
    
    PLIB_ADC_Enable(ADC_ID_1);
    asm( "nop" );asm( "nop" );
    
    // Auto Start Sampling and then go to conversion
    PLIB_ADC_SampleAutoStartEnable(ADC_ID_1);
    // Is Conversion Done ??
    while(!PLIB_ADC_ConversionHasCompleted(ADC_ID_1));
    // Yes, stop sample/convert
    PLIB_ADC_SampleAutoStartDisable(ADC_ID_1);
    // Average the 8 ADC value
    int i;
    for(i = 0; i < _ADC_DEFAULT_SAMPLES; i++){
        adcValue = adcValue + PLIB_ADC_ResultGetByIndex(ADC_ID_1, i);
    }
    adcValue >>= 3;

    if( prevAD1PCFGState )
        AD1PCFGSET = analogMask;
    else
        AD1PCFGCLR = analogMask;
    
    return adcValue;
}

