#include <stm32f10x.h>
#include "internos.h"
#include "externos.h"

#define DO 1047
#define DOs 1109
#define RE 1175
#define REs 1245
#define MI 1319
#define FA 1397
#define FAs 1480
#define SOL 1568
#define SOLs 1661
#define LA 1760
#define LAs 1865
#define SI 1976

void toca_buzzer(){	
	buzzer_toca_nota(DO, 25, 100);
	buzzer_toca_nota(RE, 25, 100);
	buzzer_toca_nota(MI, 25, 100);
	buzzer_toca_nota(FA, 25, 200);
	buzzer_toca_nota(FA, 0, 10);
	buzzer_toca_nota(FA, 25, 100);
	buzzer_toca_nota(FA, 0, 10);
	buzzer_toca_nota(FA, 25, 200);
	buzzer_toca_nota(FA, 0, 20);
	buzzer_toca_nota(DO, 25, 100);
	buzzer_toca_nota(RE, 25, 100);
	buzzer_toca_nota(DO, 25, 100);
	buzzer_toca_nota(RE, 25, 200);
	buzzer_toca_nota(FA, 0, 10);
	buzzer_toca_nota(RE, 25, 100);
	buzzer_toca_nota(FA, 0, 10);
	buzzer_toca_nota(RE, 25, 200);
	buzzer_toca_nota(FA, 0, 20);
	buzzer_toca_nota(DO, 25, 100);
	buzzer_toca_nota(SOL, 25, 100);
	buzzer_toca_nota(FA, 25, 100);
	buzzer_toca_nota(MI, 25, 200);
	buzzer_toca_nota(FA, 0, 10);
	buzzer_toca_nota(MI, 25, 100);
	buzzer_toca_nota(FA, 0, 10);
	buzzer_toca_nota(MI, 25, 200);
	buzzer_toca_nota(FA, 0, 20);
	buzzer_toca_nota(DO, 25, 100);
	buzzer_toca_nota(RE, 25, 100);
	buzzer_toca_nota(MI, 25, 100);
	buzzer_toca_nota(FA, 25, 200);
	buzzer_toca_nota(FA, 0, 20);
	buzzer_toca_nota(FA, 25, 100);
	buzzer_toca_nota(FA, 0, 10);
	buzzer_toca_nota(FA, 25, 200);
	buzzer_toca_nota(FA, 0, 20);
}

int main()
{
	//Configurar GPIO
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
	leds_apaga_todos();
	gpio_saida_pp_alternada('a', LED2);
	gpio_saida_pp_alternada('b', BUZZER);

 //timers
	habilita_timer(2);
	habilita_timer(3);

	while(1)
	{
		toca_buzzer();
	}
}