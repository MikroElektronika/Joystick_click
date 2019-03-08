/*
    __joystick_driver.c

-----------------------------------------------------------------------------

  This file is part of mikroSDK.

  Copyright (c) 2017, MikroElektonika - http://www.mikroe.com

  All rights reserved.

----------------------------------------------------------------------------- */

#include "__joystick_driver.h"
#include "__joystick_hal.c"

/* ------------------------------------------------------------------- MACROS */



/* ---------------------------------------------------------------- VARIABLES */

#ifdef   __JOYSTICK_DRV_I2C__
static uint8_t _slaveAddress;
#endif


/* Device I2C Address */
//    J1 is in position 0
const uint8_t _JOYSTICK_I2C_ADDRESS_0                                    = 0x40;
//    J1 is in position 1
const uint8_t _JOYSTICK_I2C_ADDRESS_1                                    = 0x41;
/* Register Map */
//    Manufacture ID code
const uint8_t _JOYSTICK_ID_CODE                                          = 0x0C;
//    Component ID version
const uint8_t _JOYSTICK_ID_VERSION                                       = 0x0D;
//    Silicon revision
const uint8_t _JOYSTICK_SIL_REV                                          = 0x0E;
//    Control register 1
const uint8_t _JOYSTICK_CONTROL1                                         = 0x0F;
//    Control register 2
const uint8_t _JOYSTICK_CONTROL2                                         = 0x2E;
//    Result x
const uint8_t _JOYSTICK_X                                                = 0x10;
//    Result y
const uint8_t _JOYSTICK_Y_RES_INT                                        = 0x11;
//    Positive X direction
const uint8_t _JOYSTICK_XP                                               = 0x12;
//    Negative X direction
const uint8_t _JOYSTICK_XN                                               = 0x13;
//    Positive Y direction
const uint8_t _JOYSTICK_YP                                               = 0x14;
//    Negative Y direction
const uint8_t _JOYSTICK_YN                                               = 0x15;
//    AGC
const uint8_t _JOYSTICK_AGC                                              = 0x2A;
//    Control register for the middle Hall element C5
const uint8_t _JOYSTICK_M_CTRL                                           = 0x2B;
//    Control register for the sector dependent attenuation of the outer Hall elements
const uint8_t _JOYSTICK_J_CTRL                                           = 0x2C;
//    Scale input to fit to the 8 bit result register
const uint8_t _JOYSTICK_T_CTRL                                           = 0x2D;

/* Write Command */
// Required Test bits of Control 2 Register
const uint8_t _JOYSTICK_CONTROL2_TEST_CMD                                = 0x84;
// Maximum sensitivity of Hall Element Direct Read Register
const uint8_t _JOYSTICK_AGC_MAX_SENSITIVITY_CMD                          = 0x3F;
// Scaling Factor to 90.8% of T_ctrl Register
const uint8_t _JOYSTICK_T_CTRL_SCALING_90_8_CMD                          = 0x0A;
// Scaling Factor to 90.8% of T_ctrl Register
const uint8_t _JOYSTICK_T_CTRL_SCALING_100_CMD                           = 0x09;
// Reset Register of Control 1 Register
const uint8_t _JOYSTICK_CONTROL1_RESET_CMD                               = 0x88;
// Invert the channel voltage
const uint8_t _JOYSTICK_INVERT_SPINING_CMD                               = 0x86;



/* -------------------------------------------- PRIVATE FUNCTION DECLARATIONS */



/* --------------------------------------------- PRIVATE FUNCTION DEFINITIONS */



/* --------------------------------------------------------- PUBLIC FUNCTIONS */

#ifdef   __JOYSTICK_DRV_SPI__

void joystick_spiDriverInit(T_JOYSTICK_P gpioObj, T_JOYSTICK_P spiObj)
{
    hal_spiMap( (T_HAL_P)spiObj );
    hal_gpioMap( (T_HAL_P)gpioObj );

    // ... power ON
    // ... configure CHIP
}

#endif
#ifdef   __JOYSTICK_DRV_I2C__

void joystick_i2cDriverInit(T_JOYSTICK_P gpioObj, T_JOYSTICK_P i2cObj, uint8_t slave)
{
    _slaveAddress = slave;
    hal_i2cMap( (T_HAL_P)i2cObj );
    hal_gpioMap( (T_HAL_P)gpioObj );

    hal_gpio_rstSet( 1 );
}

#endif
#ifdef   __JOYSTICK_DRV_UART__

void joystick_uartDriverInit(T_JOYSTICK_P gpioObj, T_JOYSTICK_P uartObj)
{
    hal_uartMap( (T_HAL_P)uartObj );
    hal_gpioMap( (T_HAL_P)gpioObj );

    // ... power ON
    // ... configure CHIP
}

#endif



/* ----------------------------------------------------------- IMPLEMENTATION */


/* Generic write 8-bit data to register function */
void joystick_writeByte( uint8_t registerAddress, uint8_t dataWrite )
{
    uint8_t buffer[ 2 ];
  
    buffer[ 0 ] = registerAddress;
    buffer[ 1 ] = dataWrite;
  
    hal_i2cStart();
    hal_i2cWrite( _slaveAddress, buffer, 2 , END_MODE_STOP );
}

/* Generic read 8-bit data from register function */
int8_t joystick_readByte( uint8_t registerAddress )
{
    uint8_t writeReg[ 1 ];
    uint8_t readReg[ 1 ];
    int8_t result;

    writeReg[ 0 ] = registerAddress;

    hal_i2cStart();
    hal_i2cWrite( _slaveAddress, writeReg, 1, END_MODE_RESTART );
    hal_i2cRead( _slaveAddress, readReg, 1, END_MODE_STOP );
    
    result = readReg[ 0 ];

    return result;
}

/* Set default configuration function */
void joystick_setDefaultConfiguration()
{
    uint8_t tempData;

    joystick_writeByte( _JOYSTICK_CONTROL2, _JOYSTICK_CONTROL2_TEST_CMD );
  
    joystick_writeByte( _JOYSTICK_AGC, _JOYSTICK_AGC_MAX_SENSITIVITY_CMD );
  
    joystick_writeByte( _JOYSTICK_T_CTRL, _JOYSTICK_T_CTRL_SCALING_90_8_CMD );
  
    tempData = joystick_readByte( _JOYSTICK_CONTROL1 );
    tempData &= 0x01;
    
    joystick_writeByte( _JOYSTICK_CONTROL1, _JOYSTICK_CONTROL1_RESET_CMD | tempData );
}

/* Check sensor ID code function */
uint8_t joystick_checkIdCode()
{
    return ( joystick_readByte( _JOYSTICK_ID_CODE ) == _JOYSTICK_ID_CODE ) ? 1 : 0;
}

/* Check sensor ID version function */
uint8_t joystick_checkIdVersion()
{
    return ( joystick_readByte( _JOYSTICK_ID_VERSION ) == _JOYSTICK_ID_VERSION ) ? 1 : 0;
}

/* Set Low Power Mode function */
void joystick_setLowPowerMode( uint8_t timings )
{
    uint8_t tempData;
    
    timings %= 8;

    tempData = joystick_readByte( _JOYSTICK_CONTROL1 );
    tempData &= 0x7F;
    tempData |= timings << 4;

    joystick_writeByte( _JOYSTICK_CONTROL1, tempData );
}

/* Set scaling factor function */
void joystick_setScalingFactor( uint8_t scalingFactor )
{
    if ( scalingFactor < 32 )
        joystick_writeByte( _JOYSTICK_T_CTRL, scalingFactor );
    else
        joystick_writeByte( _JOYSTICK_T_CTRL, _JOYSTICK_T_CTRL_SCALING_100_CMD );
}

/* Set interrupt disabled function */
void joystick_disabledInterrupt()
{
    uint8_t tempData;

    tempData = joystick_readByte( _JOYSTICK_CONTROL1 );
    tempData &= 0x04;

    joystick_writeByte( _JOYSTICK_CONTROL1, _JOYSTICK_CONTROL1_RESET_CMD | tempData );
}

/* Set interrupt enabled function */
void joystick_enabledInterrupt()
{
    uint8_t tempData;

    tempData = joystick_readByte( _JOYSTICK_CONTROL1 );
    tempData |= 0x04;

    joystick_writeByte( _JOYSTICK_CONTROL1, _JOYSTICK_CONTROL1_RESET_CMD | tempData );
}

/* Invert the channel voltage function */
void joystick_invertSpinning()
{
    joystick_writeByte( _JOYSTICK_CONTROL2, _JOYSTICK_INVERT_SPINING_CMD );
}

/* Get joystick position function */
uint8_t joystick_getPosition()
{
    int8_t ox;
    int8_t oy;
    uint8_t position;
    
    position = 0;

    ox = joystick_readByte( _JOYSTICK_X );
    Delay_10us();
    oy = joystick_readByte( _JOYSTICK_Y_RES_INT );
    Delay_10us();
    
    if ( ox <= -60 )
    {
            // right
            position = 3;
    }
    
    if ( ox >= 60 )
    {
            // left
            position = 7;
    }
    
    if ( oy >= 60 )
    {
        if ( ox < 20 && ox >= -20 )
        {
            // top
            position = 1;
        }
    }
    
    if ( oy <= -60 )
    {
        if ( ox <= 20 && ox >= -20 )
        {
            // bottom
            position = 5;
        }
    }
    
    if ( ox < -20 && ox > -60 )
    {
        if ( oy > 20 )
        {
            // top-right
            position = 2;
        }
        else
        {
            // bottom-right
            position = 4;
        }
    }
    
    if ( ox < 60 && ox > 20 )
    {
        if ( oy < -20 )
        {
            // top-left
            position = 6;
        }
        else
        {
            // bottom-left
            position = 8;
        }
    }

    return position;
}

/* Get state of interrupt pin function */
uint8_t joystick_getInterrupt()
{
    return hal_gpio_intGet();
}

/* Get state of Joystick button function */
uint8_t joystick_pressButton()
{
    return hal_gpio_csGet();
}

/* General soft reset function */
void joystick_softReset()
{
    uint8_t buffer;
    
    buffer = joystick_readByte( _JOYSTICK_CONTROL1 );
    buffer &= 0x01;

    joystick_writeByte( _JOYSTICK_CONTROL1, _JOYSTICK_CONTROL1_RESET_CMD | buffer );
}

/* General hardware reset function*/
void joystick_hardwareReset()
{
    hal_gpio_rstSet( 0 );
    Delay_10us();
    hal_gpio_rstSet( 1 );
}





/* -------------------------------------------------------------------------- */
/*
  __joystick_driver.c

  Copyright (c) 2017, MikroElektonika - http://www.mikroe.com

  All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright
   notice, this list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright
   notice, this list of conditions and the following disclaimer in the
   documentation and/or other materials provided with the distribution.

3. All advertising materials mentioning features or use of this software
   must display the following acknowledgement:
   This product includes software developed by the MikroElektonika.

4. Neither the name of the MikroElektonika nor the
   names of its contributors may be used to endorse or promote products
   derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY MIKROELEKTRONIKA ''AS IS'' AND ANY
EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL MIKROELEKTRONIKA BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

----------------------------------------------------------------------------- */