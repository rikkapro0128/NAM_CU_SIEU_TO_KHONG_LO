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
#include <math.h>


void main(void) {
    ANSEL = 0x01;
    ANSELH = 0;
    TRISA0 = 1;
    TRISB = TRISC = TRISD = 0;
    PORTB = 0;
    PORTC = 0;
    PORTD = 0;
    ADCON1 = 0x80;
    ADCON0 = 0x81;
    ADFM = 1;
    unsigned int storage = 0;
	const int led[10]={0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90};
    float Vout, Re_Vout;
    unsigned int TR, CH, DV, temp;
    while(1) {
        __delay_us(6);
        GO = 1;
        while(GO);
        storage = (ADRESH << 8) | ADRESL;
        Vout = (float)(storage * 5) / 1023; 
        Re_Vout = round(Vout * 100) / 100;
        if(Vout < 1) {
            temp = (Re_Vout * 1000);
            TR = (temp % 100) % 10;
            CH = temp / 100;
            DV = (temp % 100) / 10;
        }else {
            temp = Re_Vout * 100;
    		TR = temp / 100;
            CH = (temp % 100) / 10;
            DV = (temp % 100) % 10;        
        }
		PORTC = led[TR];
		PORTD = led[CH];
		PORTB = led[DV];
    }
}
