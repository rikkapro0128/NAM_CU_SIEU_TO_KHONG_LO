
#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator: High-speed crystal/resonator on RA6/OSC2/CLKOUT and RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = ON       // RE3/MCLR pin function select bit (RE3/MCLR pin function is MCLR)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown Out Reset Selection bits (BOR disabled)
#pragma config IESO = OFF       // Internal External Switchover bit (Internal/External Switchover mode is disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is disabled)
#pragma config LVP = OFF        // Low Voltage Programming Enable bit (RB3 pin has digital I/O, HV on MCLR must be used for programming)

// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)

#define _XTAL_FREQ 4000000
#define speed 200
#define delaySee 500
//#define timeTest 2000 
#define flash 1000
#include <xc.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

const int led[10]={0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90};

void demNguoc(unsigned int num) {
    unsigned int CH = 0, DV = 0;
    do {
        CH = num / 10;
        DV = num % 10;
        PORTD = led[DV] << 1;
        PORTC = led[CH];
        __delay_ms(50);
    }while(num--);
    PORTC = PORTD = 0xff;
}

void demThuan(unsigned int num) {
    unsigned int dem = 0, CH = 0, DV = 0;
    do {
        PORTD = led[DV] << 1;
        PORTC = led[CH];
        __delay_ms(50);
        dem++;
        CH = dem / 10;
        DV = dem % 10;
    }while(num--);
    PORTC = PORTD = 0xff;
}

void hienThiFP() {
    PORTD = 0b0001100 << 1;
    PORTC = 0b0001110;
}

void main(void) {
    ANSEL = ANSELH = 0;
    TRISB = WPUB = 0xff; // declare resistance pull-up
    nRBPU = 0; // set permit all PORTB have resistance pull-up
    TRISC = TRISD = 0;
    PORTC = PORTD = 0;
    GIE = 1;
    RBIF = 0;
    RBIE = 1;
    IOCB = 0xff;
    while(1);
}

void __interrupt() myIsr() {
    if(!RB0) {
        while(!RB0);
        demThuan(24);
    }
    else if(!RB1) {
        while(!RB1);
        unsigned int num = 2;
        while(num--) {
            demNguoc(60);
        }
    }
    else if(!RB2) {
        while(!RB2);
        unsigned int num = 3;
        while(num--) {
            PORTC = PORTD = 0xff;
            __delay_ms(500);
            hienThiFP();
            __delay_ms(500);
        }
        PORTC = PORTD = 0xff;
    }
}
