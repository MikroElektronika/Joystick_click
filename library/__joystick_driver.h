/*
    __joystick_driver.h

-----------------------------------------------------------------------------

  This file is part of mikroSDK.
  
  Copyright (c) 2017, MikroElektonika - http://www.mikroe.com

  All rights reserved.

----------------------------------------------------------------------------- */

/**
@file   __joystick_driver.h
@brief    Joystick Driver
@mainpage Joystick Click
@{

@image html libstock_fb_view.jpg

@}

@defgroup   JOYSTICK
@brief      Joystick Click Driver
@{

| Global Library Prefix | **JOYSTICK** |
|:---------------------:|:-----------------:|
| Version               | **1.0.0**    |
| Date                  | **Oct 2018.**      |
| Developer             | **Nenad Filipovic**     |

*/
/* -------------------------------------------------------------------------- */

#include "stdint.h"

#ifndef _JOYSTICK_H_
#define _JOYSTICK_H_

/** 
 * @macro T_JOYSTICK_P
 * @brief Driver Abstract type 
 */
#define T_JOYSTICK_P    const uint8_t*

/** @defgroup JOYSTICK_COMPILE Compilation Config */              /** @{ */

//  #define   __JOYSTICK_DRV_SPI__                            /**<     @macro __JOYSTICK_DRV_SPI__  @brief SPI driver selector */
   #define   __JOYSTICK_DRV_I2C__                            /**<     @macro __JOYSTICK_DRV_I2C__  @brief I2C driver selector */                                          
// #define   __JOYSTICK_DRV_UART__                           /**<     @macro __JOYSTICK_DRV_UART__ @brief UART driver selector */ 

                                                                       /** @} */
/** @defgroup JOYSTICK_VAR Variables */                           /** @{ */

extern const uint8_t _JOYSTICK_I2C_ADDRESS_0;
extern const uint8_t _JOYSTICK_I2C_ADDRESS_1;
extern const uint8_t _JOYSTICK_ID_CODE;
extern const uint8_t _JOYSTICK_ID_VERSION;
extern const uint8_t _JOYSTICK_SIL_REV;
extern const uint8_t _JOYSTICK_CONTROL1;
extern const uint8_t _JOYSTICK_CONTROL2;
extern const uint8_t _JOYSTICK_X;
extern const uint8_t _JOYSTICK_Y_RES_INT;
extern const uint8_t _JOYSTICK_XP;
extern const uint8_t _JOYSTICK_XN;
extern const uint8_t _JOYSTICK_YP;
extern const uint8_t _JOYSTICK_YN;
extern const uint8_t _JOYSTICK_AGC;
extern const uint8_t _JOYSTICK_M_CTRL;
extern const uint8_t _JOYSTICK_J_CTRL;
extern const uint8_t _JOYSTICK_T_CTRL;
extern const uint8_t _JOYSTICK_CONTROL2_TEST_CMD;
extern const uint8_t _JOYSTICK_AGC_MAX_SENSITIVITY_CMD;
extern const uint8_t _JOYSTICK_T_CTRL_SCALING_90_8_CMD;
extern const uint8_t _JOYSTICK_T_CTRL_SCALING_100_CMD;
extern const uint8_t _JOYSTICK_CONTROL1_RESET_CMD;
extern const uint8_t _JOYSTICK_INVERT_SPINING_CMD;

                                                                       /** @} */
/** @defgroup JOYSTICK_TYPES Types */                             /** @{ */



                                                                       /** @} */
#ifdef __cplusplus
extern "C"{
#endif

/** @defgroup JOYSTICK_INIT Driver Initialization */              /** @{ */

#ifdef   __JOYSTICK_DRV_SPI__
void joystick_spiDriverInit(T_JOYSTICK_P gpioObj, T_JOYSTICK_P spiObj);
#endif
#ifdef   __JOYSTICK_DRV_I2C__
void joystick_i2cDriverInit(T_JOYSTICK_P gpioObj, T_JOYSTICK_P i2cObj, uint8_t slave);
#endif
#ifdef   __JOYSTICK_DRV_UART__
void joystick_uartDriverInit(T_JOYSTICK_P gpioObj, T_JOYSTICK_P uartObj);
#endif


/** @defgroup JOYSTICK_FUNC Driver Functions */                   /** @{ */


/**
 * @brief Generic write 8-bit data to register function
 *
 * @param[in] registerAddress                8-bit register address
 *
 * @param[in] dataWrite                      8-bit data to write
 *
 * Function takes 8-bit register address of the target and
 * write 8-bit data to that register of AS5013 Hall IC.
 */
void joystick_writeByte( uint8_t registerAddress, uint8_t dataWrite );

/**
 * @brief Generic read 8-bit data to register function
 *
 * @param[in] registerAddress                8-bit register address
 *
 * @return
 * 8-bit ( signed ) data from addressed register from the AS5013 Hall IC
 *
 * Function takes the 8-bit register address of the target register
 * and read 8-bit from that register of AS5013 Hall IC.
 */
int8_t joystick_readByte( uint8_t registerAddress );

/**
 * @brief Set default configuration function
 *
 * Function set default configuration,
 * set required Test bits of Control Register 2,
 * set maximum sensitivity,
 * set scaling Factor to 90.8% and
 * reset read value by writing configuration 1 register.
 */
void joystick_setDefaultConfiguration();

/**
 * @brief Check sensor ID code function
 *
 * @return sensor ID code
 * - 1 : OK
 * - 0 : ERROR
 *
 * Function read and return sensor ID code
 * from ID Code register.
 */
uint8_t joystick_checkIdCode();

/**
 * @brief Check sensor ID version function
 *
 * @return sensor ID version
 * - 1 : OK
 * - 0 : ERROR
 *
 * Function read and return sensor ID version
 * from ID Version register.
 */
uint8_t joystick_checkIdVersion();

/**
 * @brief Set Low Power Mode function
 *
 * @param[in] timings                        timings by setting the low power timebase
 *
 * Function set default configuration,
 * The measurements are triggered with an internal low power oscillator – the user can select between 8 different timings by
 * setting the low power timebase.
 * - 0 :  20 ms;
 * - 1 :  40 ms;
 * - 2 :  80 ms;
 * - 3 : 100 ms;
 * - 4 : 140 ms;
 * - 5 : 200 ms;
 * - 6 : 260 ms;
 * - 7 : 320 ms;
 */
void joystick_setLowPowerMode();

/**
 * @brief Set scaling factor function
 *
 * @param[in] scalingFactor                  scaling factor
 *
 * Function set scaling factor value of the XY coordinates
 * to fit to the 8-bit X and Y_res_int register (full dynamic range);
 * - 31 :  31.3 %;
 * - 30 :  32.2 %;
 * - 29 :  33.4 %;
 * - 28 :  34.6 %;
 * - 27 :  35.7 %;
 * - 26 :  37.1 %;
 * - 25 :  38.5 %;
 * - 24 :  40.0 %;
 * - 23 :  41.6 %;
 * - 22 :  43.6 %;
 * - 21 :  45.5 %;
 * - 20 :  47.7 %;
 * - 19 :  50.0 %;
 * - 18 :  52.5 %;
 * - 17 :  55.5 %;
 * - 16 :  58.8 %;
 * - 15 :  62.5 %;
 * - 14 :  66.6 %;
 * - 13 :  71.5 %;
 * - 12 :  77.0 %;
 * - 11 :  83.4 %;
 * - 10 :  90.8 %;
 * -  9 : 100.0 %;
 * -  8 : 111.1 %;
 * -  7 : 125.0 %;
 * -  6 : 142.8 %;
 * -  5 : 166.6 %;
 * -  4 : 200.0 %;
 * -  3 : 250.0 %;
 * -  2 : 333.4 %;
 * -  1 : 500.0 %;
 */
void joystick_setScalingFactor( uint8_t scalingFactor );

/**
 * @brief Set interrupt disabled function
 *
 * Function set interrupt output is disabled.
 */
void joystick_disabledInterrupt();

/**
 * @brief Set interrupt enabled function
 *
 * Function set interrupt output is enabled.
 */
void joystick_enabledInterrupt();

/**
 * @brief Invert the channel voltage function
 *
 * Function set invert the channel voltage,
 * set to invert the magnet polarity.
 */
void joystick_invertSpinning();

/**
 * @brief Get joystick position function
 *
 * @return
 * 8-bit data of position
 * - 0 : Start           Position;
 * - 1 : Top             Position;
 * - 2 : Top-Right       Position;
 * - 3 : Right           Position;
 * - 4 : Bottom-Right    Position;
 * - 5 : Bottom          Position;
 * - 6 : Bottom-Left     Position;
 * - 7 : Left            Position;
 * - 8 : Top-Left        Position
 *
 * Function get position of miniature joystick module ( N50P105 ),
 * return position state value from 0 to 8 that calculeted
 * by the value read from the register of the AS5013 Hall IC.
 */
uint8_t joystick_getPosition();

/**
 * @brief Get state of interrupt pin function
 *
 * @return
 * state of INT pin:
 * - 0 : active low;
 * - 1 : open drain;
 *
 * Function read state of interrupt ( INT ) pin,
 * and return 0 or 1.
 */
uint8_t joystick_getInterrupt();

/**
 * @brief Get state of Joystick button function
 *
 * @return
 * state of CS pin:
 * - 0 : not active;
 * - 1 : active;
 *
 * Function read state of Joystick button ( CS ) pin,
 * and return 0 or 1.
 */
uint8_t joystick_pressButton();

/**
 * @brief General soft reset function
 *
 * Function soft reset register of the AS5013 Hall IC.
 * All the internal registers are loaded with their reset value.
 * The Control Register 1 is loaded as well with
 * the value 0xF0, then the Soft_rst bit goes back to 0 (Normal mode) once the internal reset sequence is finished.
 */
void joystick_softReset();

/**
 * @brief General hardware reset function
 *
 * Function hardware reset register of the AS5013 Hall IC,
 * by set RST pin high.
 */
void joystick_hardwareReset();




                                                                       /** @} */
#ifdef __cplusplus
} // extern "C"
#endif
#endif

/**
    @example Click_Joystick_STM.c
    @example Click_Joystick_TIVA.c
    @example Click_Joystick_CEC.c
    @example Click_Joystick_KINETIS.c
    @example Click_Joystick_MSP.c
    @example Click_Joystick_PIC.c
    @example Click_Joystick_PIC32.c
    @example Click_Joystick_DSPIC.c
    @example Click_Joystick_AVR.c
    @example Click_Joystick_FT90x.c
    @example Click_Joystick_STM.mbas
    @example Click_Joystick_TIVA.mbas
    @example Click_Joystick_CEC.mbas
    @example Click_Joystick_KINETIS.mbas
    @example Click_Joystick_MSP.mbas
    @example Click_Joystick_PIC.mbas
    @example Click_Joystick_PIC32.mbas
    @example Click_Joystick_DSPIC.mbas
    @example Click_Joystick_AVR.mbas
    @example Click_Joystick_FT90x.mbas
    @example Click_Joystick_STM.mpas
    @example Click_Joystick_TIVA.mpas
    @example Click_Joystick_CEC.mpas
    @example Click_Joystick_KINETIS.mpas
    @example Click_Joystick_MSP.mpas
    @example Click_Joystick_PIC.mpas
    @example Click_Joystick_PIC32.mpas
    @example Click_Joystick_DSPIC.mpas
    @example Click_Joystick_AVR.mpas
    @example Click_Joystick_FT90x.mpas
*/                                                                     /** @} */
/* -------------------------------------------------------------------------- */
/*
  __joystick_driver.h

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