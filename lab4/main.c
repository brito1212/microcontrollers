#include <stm32f10x.h>
#include "internos.h"
#include "externos.h"

void contagem_crescente(int n);
void contagem_decrescente(int n);
void print_menu();
void chaves_loop_lcd();

int main()
{
	habilita_gpio('a');
	corrige_jtag();
	delay_ms(10);
	gpio_saida_pp('a', LCD_EN);
	gpio_saida_pp('a', LCD_RS);
	gpio_saida_pp('a', LED5);
	gpio_saida_pp('a', LED6);
	gpio_saida_pp('a', LED7);
	gpio_saida_pp('a', LED8);
	gpio_entrada_pp('b', SW1);
	gpio_entrada_pp('b', SW2);
	
	lcd_init();

	while(1){
		print_menu();
		chaves_loop_lcd();
	}
	
	return 0;
}

void chaves_loop_lcd(){
		int key = chaves_ler_todas();
		switch(key){
			case SW1:
				contagem_crescente(5);
				break;
			case SW2:
				contagem_decrescente(5);
				break;
			default:
				break;
		}
}


void contagem_decrescente(int n){
	char c, d, u;
	for (int i = n; i >= 0; i--) {
		lcd_command(0x01);
		c = bin_bcd(i, 'c');
		d = bin_bcd(i, 'd');
		u = bin_bcd(i, 'u');
		
		lcd_data(c);
		delay_ms(10);
		lcd_data(d);
		delay_ms(10);
		lcd_data(u);
		
		delay_ms(1000);
	}
}

void contagem_crescente(int n){
	char c, d, u;
	for (int i = 0; i < n + 1; i++) {
		lcd_command(0x01);
		c = bin_bcd(i, 'c');
		d = bin_bcd(i, 'd');
		u = bin_bcd(i, 'u');
		
		lcd_data(c);
		delay_ms(100);
		lcd_data(d);
		delay_ms(100);
		lcd_data(u);
		
		delay_ms(1000);
	}
}


void print_menu(){
	lcd_command(0x80);
	lcd_print("SW1: Crescente");
	lcd_command(0xC0);
	lcd_print("SW2: Decrescente");
}