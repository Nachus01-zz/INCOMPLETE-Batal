#include "Serial.h"
#include <p18f4431.h>
#include "types.h"

void Serial_Init(void)
{
    TRISCbits.RC7=1;
    SYNC=0;
    BRGH=1;
    BRG16=1;
    SPEN=1;
    RCIE=1;
    TXEN=1;
    RX9=0;
    CREN=1;
    if (BAUDRATE == 19200)
    {
        SPBRG=103;
    }
    else if (BAUDRATE == 57600)
    {
        SPBRG=34;
    }
    else if (BAUDRATE == 115200)
    {
        SPBRG=16;
    }
    else 
    {
        SPBRG=207; //Baudrate 9600
    }   
}

void Serial_Write(u8 character)
{
    TXREG=character;
}
