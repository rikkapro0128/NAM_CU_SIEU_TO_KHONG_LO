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
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)

#define _XTAL_FREQ 4000000
#include <xc.h>

void numPortC(unsigned int num) {
    unsigned int NG = num / 1000, TR = (num / 100) % 10;
    PORTC = (NG << 4) | TR;
}

void numPortD(unsigned int num) {
    unsigned int CH = (num / 10) % 10, DV = num % 10;
    PORTD = (DV << 4) | CH;
}

void hienThiLedTong(unsigned int num) {
    numPortC(num);
    numPortD(num);
}

unsigned int state = 0;

void main(void) {
    ANSEL = ANSELH = 0;
    TRISC = TRISD = 0;
    PORTC = PORTD = 0;
    TMR0 = 0;
    TMR0IF = 0;
    T0CS = 1;
    T0SE = 0;
    GIE = PEIE = TMR0IE = 0;
    PSA = 1;
    TRISA4 = 1;
    while(1) {
        if(TMR0) {
            TMR0 = 0;
            state += 50;
            if(state > 1000) {
                state = 0;
            }
            hienThiLedTong(state);
        }
    }
}
