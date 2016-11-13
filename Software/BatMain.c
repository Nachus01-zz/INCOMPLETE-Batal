/* 
 * File:   BatMain.c
 * Author: Ignacius
 *
 * Created on 21 de abril de 2016, 11:19 AM
 */

#include <p18f4431.h>
#include "Serial.h"
#include "configurationbits.h"
#include "types.h"

#define SPEEDINCREMENT 818
#define SERVOINCREMENT 82
u8 a;
u16 duty0;
u8 duty0H;
u8 duty0L;
u16 duty1;
u8 duty1H;
u8 duty1L;
u16 duty2;
u8 duty2H;
u8 duty2L;

MotorFWD()
{
    PORTCbits.RC5=1;
    PORTCbits.RC4=0;
    PORTDbits.RD3=1;
    PORTDbits.RD2=0;
}

MotorBWD()
{
    PORTCbits.RC5=0;
    PORTCbits.RC4=1;
    PORTDbits.RD3=0;
    PORTDbits.RD2=1;
}

MotorSTP()
{
    PORTCbits.RC5=0;
    PORTCbits.RC4=0;
    PORTDbits.RD3=0;
    PORTDbits.RD2=0;
}

MotorLFT()
{
    PORTCbits.RC5=0;
    PORTCbits.RC4=1;
    PORTDbits.RD3=1;
    PORTDbits.RD2=0;
}

MotorRGT()
{
    PORTCbits.RC5=1;
    PORTCbits.RC4=0;
    PORTDbits.RD3=0;
    PORTDbits.RD2=1;
}

void interrupt high()
{
    if(RCIE&&RCIF)
    {
        RCIF=0;
        a=RCREG;
        TXREG=a;
        if(a>10&&a<21) duty0=(a-10)*SPEEDINCREMENT;
        if(a>24&&a<33) duty1=(a-20)*SERVOINCREMENT;
        if(a>34&&a<43) duty2=(a-30)*SERVOINCREMENT;
        if(a=='A') MotorFWD();
        if(a=='B') MotorBWD();
        if(a=='C') MotorSTP();
        if(a=='D') MotorRGT();
        if(a=='E') MotorLFT();
        duty0H=duty0>>8;
        duty0L=duty0-duty0H;
        duty1H=duty1>>8;
        duty1L=duty1-duty1H;
        duty2H=duty2>>8;
        duty2L=duty2-duty2H;
        PDC0L=duty0L;
        PDC0H=duty0H;
        PDC1L=duty1L;
        PDC1H=duty1H;
        PDC2L=duty2L;
        PDC2H=duty2H;
    }
}

void main() 
{
    Serial_Init();
    
    //Interrupts_Init
    IPEN=1;
    GIEH=1;
    RCIE=1;
    RCIF=1;
    RCIP=1;
    
    //PowerControl_Init
    //PTCON0
    PTCKPS1=1;
    PTCKPS0=0;
    
    //PTCON1
    PTEN=1;
    
    //PWMCON0
    PWMEN2=1;
    PWMEN1=0;
    PWMEN0=1;
    PMOD3=0;
    PMOD2=0;
    PMOD1=0;
    PMOD0=0;
    
    //IOPorts_Init
    PORTCbits.RC5=0;
    TRISCbits.RC5=0;
    PORTCbits.RC4=0;
    TRISCbits.RC4=0;
    PORTDbits.RD3=0;
    TRISDbits.RD3=0;
    PORTDbits.RD2=0;
    TRISDbits.RD2=0;
    
    
    PTPERH=7;
    PTPERL=208;//*/
    duty0=0;
    duty1=0;
    duty2=0;
    do
    {
        
    }
    while(1);    
}

