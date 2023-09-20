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

void initial_config();
void toca_nota(int nota, int ciclo_id, int oitava);
void print_oitava(int oitava);
void print_ciclo(int ciclo_id);


int main()
{
	initial_config();
	
	int ciclo, oitava;
	ciclo = 1;
	oitava = 1;
	print_ciclo(ciclo);
	print_oitava(oitava);

	while(1)
	{
		chave = chaves_ler_todas();
		switch(chave){
			case 1:
				oitava = 1;
				print_oitava(oitava);
				break;
			case 2:
				oitava = 2;
				print_oitava(oitava);
				break;
			case 3:
				ciclo += 1;
				if (ciclo > 3){
					ciclo = 1;
				}
				print_ciclo(ciclo);
				break;
			case 4:
				toca_nota(DO, 0, oitava);
				break;
			case 5:
				toca_nota(DO, ciclo, oitava);
				break;
			case 6:
				toca_nota(RE, ciclo, oitava);
				break;
			case 7:
				toca_nota(FA, ciclo, oitava);
				break;
			case 8:
				toca_nota(MI, ciclo, oitava);
				break;
			case 9:
				toca_nota(SOL, ciclo, oitava);
				break;
			case 10:
				toca_nota(LA, ciclo, oitava);
				break;
			case 11:
				toca_nota(SI, ciclo, oitava);
				break;
			case 12:
				toca_nota(DO, 0, oitava);
				break;
			case 13:
				toca_nota(DOs, ciclo, oitava);
				break;
			case 14:
				toca_nota(REs, ciclo, oitava);
				break;
			case 15:
				toca_nota(FAs, ciclo, oitava);
				break;
			case 16:
				toca_nota(SOLs, ciclo, oitava);
				break;
			case 17:
				toca_nota(LAs, ciclo, oitava);
				break;
			default:
				toca_nota(DO, 0, oitava);
				break;
		}
			
	}
}


void initial_config(){
	//Configurar GPIO
	habilita_gpio('a');
	habilita_gpio('b');
	habilita_gpio('c');
	corrige_jtag();
	delay_ms(10);
	gpio_saida_pp('a', LCD_DB4);
	gpio_saida_pp('a', LCD_DB5);
	gpio_saida_pp('a', LCD_DB6);
	gpio_saida_pp('a', LCD_DB7);
	gpio_saida_pp('a', LCD_RS);
	gpio_saida_pp('a', LCD_EN);

	
	gpio_entrada_pp('b', SW1);
	gpio_entrada_pp('b', SW2);
	gpio_entrada_pp('b', SW3);
	gpio_entrada_pp('b', SW4);
	gpio_entrada_pp('b', SW5);
	gpio_entrada_pp('b', SW6);
	gpio_entrada_pp('b', SW7);
	gpio_entrada_pp('a', SW8);
	gpio_entrada_pp('a', SW9);
	gpio_entrada_pp('b', SW10);
	gpio_entrada_pp('b', SW11);
	gpio_entrada_pp('b', SW12);
	gpio_entrada_pp('b', SW13);
	gpio_entrada_pp('a', SW14);
	gpio_entrada_pp('c', SW15);
	gpio_entrada_pp('c', SW16);
	gpio_entrada_pp('c', SW17);
	
	gpio_saida_pp_alternada('b', BUZZER);
	
	lcd_init();

 //timers
	habilita_timer(2);
	habilita_timer(3);
}

void toca_nota(int nota, int ciclo_id, int oitava){
	int ciclo = 0;
	switch(ciclo_id){
		case 1:
			ciclo = 10;
			break;
		case 2:
			ciclo = 25;
			break;
		case 3:
			ciclo = 40;
			break;
	}
	
	pwm_timer_3(nota * oitava, ciclo, 3);
}

void print_oitava(int oitava){
	lcd_command(0x80);
	switch(oitava){
		case 1:
			lcd_print("Oitava: 1");
			break;
		case 2:
			lcd_print("Oitava: 2");
			break;
	}
}

void print_ciclo(int ciclo_id){
	lcd_command(0xC0);
	switch(ciclo_id){
		case 1:
			lcd_print("Ciclo: 10");
			break;
		case 2:
			lcd_print("Ciclo: 25");
			break;
		case 3:
			lcd_print("Ciclo: 40");
			break;
	}
}
