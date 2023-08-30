#include <stm32f10x.h>


//Definições dos perifiéricos externos da placa
//Leds
#define LED1 0  //PA0
#define LED2 1  //PA1
#define LED3 2  //PA2
#define LED4 15 //PA15
#define LED5 8  //PA8
#define LED6 6  //PA6
#define LED7 5  //PA5
#define LED8 11 //PA11

#define SW1 12 //PB12
#define SW2 13 //PB13
#define SW3 14 //PB14
#define SW4 15 //PB15
#define SW5 5 //PB5
#define SW6 4 //PB4
#define SW7 3 //PB3
#define SW8 3 //PA3
#define SW9 4 //PA4
#define SW10 8 //PB8
#define SW11 9 //PB9
#define SW12 11 //PB11
#define SW13 10 //PB10
#define SW14 7 //PA7
#define SW15 15 //PC15
#define SW16 14 //PC14
#define SW17 13 //PC13

#define BZ1 0 //PB0 

//funções comuns
void corrige_jtag()
{
    RCC->APB2ENR |= 0xFC; //Enable the clocks for GPIO ports 
    RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;
    AFIO->MAPR |= AFIO_MAPR_SWJ_CFG_JTAGDISABLE; 
}

void delay_ms(uint16_t t)
{
    volatile unsigned long l = 0;
    for(uint16_t i = 0; i < t; i++)
        for(l = 0; l < 6000; l++)
        {
        }
}

// Funções para trabalhar com os LEDs
void leds_apaga_todos()
{ 
    GPIOA->ODR &= ~((1<<LED1)|(1<<LED2)|(1<<LED3)|(1<<LED4)|(1<<LED5)|(1<<LED6)|(1<<LED7)|(1<<LED8));
}

void led_acende(uint8_t led_id)
{
  GPIOA->ODR |= (1<<led_id);
}

void leds_acende_todos()
{
    led_acende(LED1);
		delay_ms(100);
		led_acende(LED2);
		delay_ms(100);
		led_acende(LED3);
		delay_ms(100);
		led_acende(LED4);
		delay_ms(100);
		led_acende(LED5);
		delay_ms(100);
		led_acende(LED6);
		delay_ms(100);
		led_acende(LED7);
		delay_ms(100);
		led_acende(LED8);
		delay_ms(100);
}

int chaves_ler_todas(){
	switch(GPIOB->IDR) {
		case 'x':
			return SW1;
			break;
		case 'x2':
			return SW2;
			break;
		case 'x3':
			return SW3;
			break;
		case 'x4':
			return SW4;
			break;
		case 'x5':
			return SW5;
			break;
		case 'x6':
			return SW6;
			break;
		case 'x7':
			return SW7;
			break;
		default:
			return 1111;
			break;
	}
	switch(GPIOB->IDR) {
		case 'x':
			return SW8;
			break;
		default:
			return 1111;
			break;
	}
}

void buzzer_tocar(int freq){
		GPIOB->ODR |= (1<<BZ1);
		delay_ms(1/(freq*2));
		GPIOB->ODR |= ~(1<<BZ1);
		delay_ms(1/(freq*2));
}
