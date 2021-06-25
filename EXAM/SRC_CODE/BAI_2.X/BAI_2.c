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

void demNguoc(unsigned int num) {
    unsigned int temp = 0, CH = 0, DV = 0;
    do {
        CH = num / 10;
        DV = num % 10;
        temp = (CH << 4) | DV;
        PORTD = temp;
        __delay_ms(300);
    }while(num--);
}

void demThuan(unsigned int num) {
    unsigned int temp = 0, dem = 0, chuc = 0, donvi = 0;
    do {
        temp = (chuc << 4) | donvi;
        PORTD = temp;
        __delay_ms(300);
        dem++;
        chuc = dem / 10;
        donvi = dem % 10;
    }while(num--);
}

void main(void) {
	ANSEL = ANSELH = 0;
    TRISD = 0;
    PORTD = 0xff;
    TRISB = WPUB = 0x01;
    nRBPU = 0;
    GIE = 1;
    INTF = 0;
    INTE = 1;
    INTEDG = 1;
    while(1) {
        demThuan(60);
    }
}

void __interrupt() myIsr() {
    INTF = 0;
    unsigned int index = 2;
	for(index = 0; index < 2; index++) {
		demNguoc(24);
	}
}
