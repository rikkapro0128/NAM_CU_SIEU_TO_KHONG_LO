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
#include <xc.h>
#include "lcd.h"

void delayMotMs(unsigned int n) {
    while(n--) {
        TMR1H = 252;
        TMR1L = 24;
        TMR1IF = 0;
        TMR1CS = 0;
        GIE = PEIE = TMR1IE = 0;
        T1CKPS1 = 0;
        T1CKPS0 = 0;
        T1SYNC = 1;
        TMR1ON = 1;
        while(!TMR1IF);
    }
}

void main(void) {
    ANSEL = ANSELH = 0;
    TRISB0 = 1;
    TRISB1 = 1;
    TRISB2 = 1;
    nRBPU = 0;
    WPUB = 0x07;
    const char ten[] = {'N', 'g', 'u', 'y', 0x00 , 'n',' ', 'T', 0x01, 'n', ' ', 'P', 'h', 0x02, 'p'};
    const char thongtin[] = {0x03, 'T', 'V', 'T', '1', '5', 'A', '-', '1', '9', '4', '3', '6', '4', '8' ,'1'};
    const char text_1[] = {'T', 'h', 'i', ' ', 'k', 0x00, 't', ' ', 't', 'h', 0x01, 'c', ' ', 'm', 0x02, 'n',};
    const char text_2[] = {'K', 'T', ' ', 'v', 'i', ' ', 'x', 0x03, ' ', 'l', 0x04};   
    const char spec_1[] 
    = {
        13, 18, 8, 20, 8, 20, 30, 0,// eex 0x00
        1, 10, 20, 0, 28, 20, 31, 0,// aas 0x01
        0, 4, 8, 0, 28, 20, 30, 0, //as 0x02
        14, 9, 9, 29, 9, 9, 14, 0, // DD 0x03
        0X99
    };
    const char spec_2[] 
    = {
        1, 5, 10, 4, 10, 12, 7, 0, // ees 0x00
        2, 4, 0, 18, 18, 18, 12, 0, // us 0x01
        12, 18, 0, 12, 18, 18, 12, 0, // oo 0x02
        12, 4, 11, 1, 18, 18, 12, 0, // uwr 0x03
        2, 4, 17, 10, 4, 4, 4, 0, //lys 0x04
        0X99
    };
    unsigned int i = 0, length = 0, times = 3;
    while(1) {
        if(!RB0) {
            while(!RB0);
            lcd_init();
            i = 0;
			lcd_put_byte(0, 0x40);
			while(lcd_busy());
			while(spec_1[i] != 0x99) {
				lcd_put_byte(1, spec_1[i]);
				while(lcd_busy());
				i++;
			}
            lcd_putc('\f');
            lcd_gotoxy(0, 0);
            for(i = 0; i < 15; i++) {
                lcd_putc(ten[i]);
            }
            lcd_gotoxy(0, 1);
            for(i = 0; i < 16; i++) {
                lcd_putc(thongtin[i]);
            }
            delayMotMs(1000);
            lcd_putc('\f');
        }else if(!RB1) {
            while(!RB1);
            lcd_init();
            i = 0;
			lcd_put_byte(0, 0x40);
			while(lcd_busy());
			while(spec_2[i] != 0x99) {
				lcd_put_byte(1, spec_2[i]);
				while(lcd_busy());
				i++;
			}
			lcd_putc('\f');
            lcd_gotoxy(0, 0);
            for(i = 0; i < 16; i++) {
                lcd_putc(text_1[i]);
            }
            lcd_gotoxy(2, 1);
            for(i = 0; i < 11; i++) {
                lcd_putc(text_2[i]);
            }
            delayMotMs(2000);
            lcd_putc('\f');
        }
    }
}
