/*
Example for Joystick Click

    Date          : Oct 2018.
    Author        : Nenad Filipovic

Test configuration PIC32 :
    
    MCU                : P32MX795F512L
    Dev. Board         : EasyPIC Fusion v7
    PIC32 Compiler ver : v4.0.0.0

---

Description :

The application is composed of three sections :

- System Initialization - Initializes I2C, GPIO and LOG structures, 
     set INT pin as input, CS and RST pins as output.
- Application Initialization - Initialization driver enable's - I2C,
     set default configuration and start write log.
- Application Task - (code snippet) This is a example which demonstrates the use of Joystick Click board.
     Joystick Click communicates with register via I2C by write and read from register,
     read joystick position and press button state.
     Results are being sent to the Usart Terminal where you can track their changes.
     All data logs on usb uart when the sensor is triggered.

Additional Functions :

- UART

*/

#include "Click_Joystick_types.h"
#include "Click_Joystick_config.h"


uint8_t position;
uint8_t buttonState;
uint8_t positionOld = 1;
uint8_t buttonStateOld = 1;

void systemInit()
{
    mikrobus_gpioInit( _MIKROBUS1, _MIKROBUS_INT_PIN, _GPIO_INPUT );
    mikrobus_gpioInit( _MIKROBUS1, _MIKROBUS_CS_PIN, _GPIO_INPUT );
    mikrobus_gpioInit( _MIKROBUS1, _MIKROBUS_RST_PIN, _GPIO_OUTPUT );

    mikrobus_i2cInit( _MIKROBUS1, &_JOYSTICK_I2C_CFG[0] );

    mikrobus_logInit( _MIKROBUS2, 9600 );

    Delay_100ms();
}

void applicationInit()
{
    joystick_i2cDriverInit( (T_JOYSTICK_P)&_MIKROBUS1_GPIO, (T_JOYSTICK_P)&_MIKROBUS1_I2C, _JOYSTICK_I2C_ADDRESS_0 );

    Delay_100ms();

    joystick_setDefaultConfiguration();

    mikrobus_logWrite( "---------------------", _LOG_LINE );
    mikrobus_logWrite( "    Configuration    ", _LOG_LINE );
    mikrobus_logWrite( "---------------------", _LOG_LINE );
    mikrobus_logWrite( "    Joystick Click   ", _LOG_LINE );
    mikrobus_logWrite( "---------------------", _LOG_LINE );

    Delay_100ms();
}

void applicationTask()
{
    buttonState = joystick_pressButton();

    position = joystick_getPosition();

    Delay_10ms();

    if ( buttonState == 1 && buttonStateOld == 0 )
    {
        buttonStateOld = 1;

        mikrobus_logWrite( "  Button is pressed ", _LOG_LINE );
        mikrobus_logWrite( "---------------------", _LOG_LINE );
    }

    if ( buttonState == 0 && buttonStateOld == 1 )
    {
        buttonStateOld = 0;
    }

    if ( positionOld != position )
    {
        switch ( position )
        {
            case 0 :
            {
                mikrobus_logWrite( "    Start position   ", _LOG_LINE );
                break;
            }
            case 1 :
            {
                mikrobus_logWrite( "         Top        ", _LOG_LINE );
                break;
            }
            case 2 :
            {
                mikrobus_logWrite( "      Top-Right     ", _LOG_LINE );
                break;
            }
            case 3 :
            {
                mikrobus_logWrite( "        Right       ", _LOG_LINE );
                break;
            }
            case 4 :
            {
                mikrobus_logWrite( "     Bottom-Right   ", _LOG_LINE );
                break;
            }
            case 5 :
            {
                mikrobus_logWrite( "        Bottom      ", _LOG_LINE );
                break;
            }
            case 6 :
            {
                mikrobus_logWrite( "     Bottom-Left    ", _LOG_LINE );
                break;
            }
            case 7 :
            {
                mikrobus_logWrite( "         Left       ", _LOG_LINE );
                break;
            }
            case 8 :
            {
                mikrobus_logWrite( "       Top-Left     ", _LOG_LINE );
                break;
            }
        }

        mikrobus_logWrite( "---------------------", _LOG_LINE );

        positionOld = position;

        Delay_100ms();
    }
}

void main()
{
    systemInit();
    applicationInit();

    while (1)
    {
            applicationTask();
    }
}