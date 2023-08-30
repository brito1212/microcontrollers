#include <stm32f10x.h>
#include "externos.h"
#include "internos.h"


void chaves_loop(){
		int key = chaves_ler_todas();
		leds_apaga_todos();
		switch(key){
			case SW1:
				led_acende(LED1);
				break;
			case SW2:
				led_acende(LED2);
				break;
			case SW3:
				led_acende(LED3);
				break;
			case SW4:
				led_acende(LED4);
				break;
			case SW5:
				led_acende(LED5);
				break;
			case SW6:
				led_acende(LED6);
				break;
			case SW7:
				led_acende(LED7);
				break;
			default:
				leds_acende_todos();
				break;
		}
}

void leds_loop(){
		leds_acende_todos();
		delay_ms(100);
		leds_apaga_todos();
		delay_ms(100);
}

void buzzer_loop(){
	int key = chaves_ler_todas();
	
	switch(key){
		case SW1:
			buzzer_tocar(500);
			break;
		case SW2:
			buzzer_tocar(250);
			break;
		case SW3:
			buzzer_tocar(125);
			break;
	}
}

int main() {
	//Configurações
	habilita_gpio('a');
	habilita_gpio('b');
	corrige_jtag();
	delay_ms(10);
	gpio_saida_pp('a', LED1);
	gpio_saida_pp('a', LED2);
	gpio_saida_pp('a', LED3);
	gpio_saida_pp('a', LED4);
	gpio_saida_pp('a', LED5);
	gpio_saida_pp('a', LED6);
	gpio_saida_pp('a', LED7);
	gpio_saida_pp('a', LED8);
	
	gpio_saida_pp('b', BZ1);
	gpio_entrada_pp('b', SW1);
	gpio_entrada_pp('b', SW2);
	gpio_entrada_pp('b', SW3);
	gpio_entrada_pp('b', SW4);
	gpio_entrada_pp('b', SW5);
	gpio_entrada_pp('b', SW6);
	gpio_entrada_pp('b', SW7);
	
	//Laço principal
	while(1) {
			leds_loop();
			// chaves_loop();
			// buzzer_loop();
	}
}