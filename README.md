![MikroE](http://www.mikroe.com/img/designs/beta/logo_small.png)

---

# Joystick Click

---

- **CIC Prefix**  : JOYSTICK
- **Author**      : Nenad Filipovic
- **Verison**     : 1.0.0
- **Date**        : Oct 2018.

---

### Software Support

We provide a library for the Joystick Click on our [LibStock](https://libstock.mikroe.com/projects/view/846/joystick-click-example) 
page, as well as a demo application (example), developed using MikroElektronika 
[compilers](http://shop.mikroe.com/compilers). The demo can run on all the main 
MikroElektronika [development boards](http://shop.mikroe.com/development-boards).

**Library Description**

The library covers all the necessary functions to control Joystick Click board.
Joystick click communicates with the target board via I2C. 
This library contains drivers for write and read data from register address,
read joystick position states and press button states.

Key functions :

- ``` void joystick_writeByte( uint8_t registerAddress, uint8_t dataWrite ) ``` - Generic write 8-bit data to register function
- ``` int8_t joystick_readByte( uint8_t registerAddress ) ``` - Generic read 8-bit data from register function
- ``` uint8_t joystick_getPosition() ``` - Get joystick position function

**Examples Description**

The application is composed of three sections :

- System Initialization - Initializes I2C, GPIO and LOG structures, set INT and CS  pin as input,
     RST pins as output.
- Application Initialization - Initialization driver enable's - I2C,
     set default configuration and start write log.
- Application Task - (code snippet) This is a example which demonstrates the use of Joystick Click board.
     Joystick Click communicates with register via I2C by write and read from register,
     read joystick position and press button state.
     Results are being sent to the Usart Terminal where you can track their changes.
     All data logs on usb uart when the sensor is triggered.


```.c

void applicationTask()
{
    buttonState = joystick_pressButton();
    
    position = joystick_getPosition();
    
    Delay_10ms();
    
    if ( buttonState == 1 && buttonStateOld == 0 )
    {
        buttonStateOld = 1;
        
        mikrobus_logWrite( "  Button is pressed ", _LOG_LINE );
        mikrobus_logWrite( "", _LOG_LINE );
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

        mikrobus_logWrite( "", _LOG_LINE );
        
        positionOld = position;
        
        Delay_100ms();
    }
}

```



The full application code, and ready to use projects can be found on our 
[LibStock](https://libstock.mikroe.com/projects/view/846/joystick-click-example) page.

Other mikroE Libraries used in the example:

- I2C
- UART


**Additional notes and informations**

Depending on the development board you are using, you may need 
[USB UART click](http://shop.mikroe.com/usb-uart-click), 
[USB UART 2 Click](http://shop.mikroe.com/usb-uart-2-click) or 
[RS232 Click](http://shop.mikroe.com/rs232-click) to connect to your PC, for 
development systems with no UART to USB interface available on the board. The 
terminal available in all Mikroelektronika 
[compilers](http://shop.mikroe.com/compilers), or any other terminal application 
of your choice, can be used to read the message.

---
---
