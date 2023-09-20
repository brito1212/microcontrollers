#include <stm32f10x.h>
#include <stdio.h>
// #include "internos.h"

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

//valores lidos quando as chaves são pressionadas
#define SW1_press 0xeffa
#define SW2_press 0xdffa
#define SW3_press 0xbffa
#define SW4_press 0x7ffa
#define SW5_press 0xffda
#define SW6_press 0xffea
#define SW7_press 0xfff2
#define SW8_press 0x5690
#define SW9_press 0x5688
#define SW10_press 0xfefa
#define SW11_press 0xfdfa 
#define SW12_press 0xf7fa
#define SW13_press 0xfbfa
#define SW14_press 0x5618
#define SW15_press 0x6000
#define SW16_press 0xa000
#define SW17_press 0xc000


//Display LCD
#define LCD_DB4 8 //PA8
#define LCD_DB5 6 //PA6
#define LCD_DB6 5 //PA5
#define LCD_DB7 11 //PA11
#define LCD_RS  15 //PA15
#define LCD_EN  12 //PA12

//Buzzer
#define BUZZER 0 //PB0

//Potenciometro
#define POT 1 //PB1

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
	
	if((GPIOB->IDR&(1<<SW1))==0){
		return 1;
	}
	else if((GPIOB->IDR&(1<<SW2))==0){
		return 2;
	}
	else if((GPIOB->IDR&(1<<SW3))==0){
		return 3;
	}
	else if((GPIOB->IDR&(1<<SW4))==0){
		return 4;
	}
	else if((GPIOB->IDR&(1<<SW5))==0){
		return 5;
	}
	else if((GPIOB->IDR&(1<<SW6))==0){
		return 6;
	}
	else if((GPIOA->IDR&(1<<SW7))==0){
		return 7;
	}
	else if((GPIOB->IDR&(1<<SW8))==0){
		return 8;
	}
	else if((GPIOA->IDR&(1<<SW9))==0){
		return 9;
	}
	else if((GPIOB->IDR&(1<<SW10))==0){
		return 10;
	}
	else if((GPIOB->IDR&(1<<SW11))==0){
		return 11;
	}
	else if((GPIOB->IDR&(1<<SW13))==0){
		return 13;
	}
	else if((GPIOA->IDR&(1<<SW14))==0){
		return 14;
	}
	else if((GPIOC->IDR&(1<<SW15))==0){
		return 15;
	}
	else if((GPIOC->IDR&(1<<SW16))==0){
		return 16;
	}
	else if((GPIOC->IDR&(1<<SW17))==0){
		return 17;
	}
	return 0;
}

int chaves_ler_todas2()
{
    uint16_t chave_id_gpiob, chave_id_gpioa, chave_id_gpioc;
    uint8_t chave_id_press = 0;
    chave_id_gpiob = GPIOB->IDR;
    chave_id_gpioa = GPIOA->IDR;
    chave_id_gpioc = GPIOC->IDR;
    switch (chave_id_gpioa)
    {
    case SW8_press:
        chave_id_press = 8;
        break;
    case SW9_press:
        chave_id_press = 9;
        break;
    case SW14_press:
        chave_id_press = 14;
        break;
    }

     switch (chave_id_gpiob)
    {
    case SW1_press:
        chave_id_press = 1;
        break;
    case SW2_press:
        chave_id_press = 2;
        break;
    case SW3_press:
        chave_id_press = 3;
        break;
    case SW4_press:
        chave_id_press = 4;
        break;
    case SW5_press:
        chave_id_press = 5;
        break;
    case SW6_press:
        chave_id_press = 6;
        break;
    case SW7_press:
        chave_id_press = 7;
        break;
    case SW10_press:
        chave_id_press = 10;
        break;
    case SW11_press:
        chave_id_press = 11;
        break;
    case SW12_press:
        chave_id_press = 12;
        break;
    case SW13_press:
        chave_id_press = 13;
        break;
    }

     switch (chave_id_gpioc)
    {
    case SW15_press:
        chave_id_press = 15;
        break;
    case SW16_press:
        chave_id_press = 16;
        break;
    case SW17_press:
        chave_id_press = 17;
        break;                                 
    }
    return chave_id_press;
}


//Functions to use with LCD display
void lcd_init(void); //Iniciar o display corretamente
void lcd_command(unsigned char cmd); //Enviar comandos
void lcd_data(unsigned char data); //Envia dados (caractere ASCII)
void lcd_print(char * str); //Envia strings
void lcd_putValue(unsigned char value); //Usada internamente


//Pin definitions
#define LCD_RS 15
#define LCD_EN 12

void lcd_putValue(unsigned char value)
{
	uint16_t aux; //variable to help to build appropriate data out
	aux = 0x0000; //clear aux
	GPIOA->BRR = (1<<5)|(1<<6)|(1<<8)|(1<<11); // clear data lines
	aux = value & 0xF0;
	aux = aux>>4;
	GPIOA->BSRR = ((aux&0x0008)<<8) | ((aux&0x0004)<<3) | ((aux&0x0002)<<5) | ((aux&0x0001)<<8);
	GPIOA->ODR |= (1<<LCD_EN); /* EN = 1 for H-to-L pulse */
	delay_ms(3);			/* make EN pulse wider */
	GPIOA->ODR &= ~ (1<<LCD_EN);	/* EN = 0 for H-to-L pulse */
	delay_ms(1);			/* wait	*/
	GPIOA->BRR = (1<<5)|(1<<6)|(1<<8)|(1<<11); // clear data lines
	aux = 0x0000; //clear aux
	aux = value & 0x0F;
	GPIOA->BSRR = ((aux&0x0008)<<8) | ((aux&0x0004)<<3) | ((aux&0x0002)<<5) | ((aux&0x0001)<<8);
	GPIOA->ODR |= (1<<LCD_EN); /* EN = 1 for H-to-L pulse */
	delay_ms(3);			/* make EN pulse wider */
  GPIOA->ODR &= ~(1<<LCD_EN);	/* EN = 0 for H-to-L pulse */
  delay_ms(1);			/* wait	*/
}

void lcd_command(unsigned char cmd)
{
	GPIOA->ODR &= ~ (1<<LCD_RS);	/* RS = 0 for command */
	lcd_putValue(cmd);
}

void lcd_data(unsigned char data)
{
	GPIOA->ODR |= (1<<LCD_RS);	/* RS = 1 for data */
	lcd_putValue(data); 
}

void lcd_print(char * str)
{
  unsigned char i = 0;

	while(str[i] != 0) /* while it is not end of string */
	{
		lcd_data(str[i]); /* show str[i] on the LCD */
		i++;
	}
}

void lcd_init()
{
	delay_ms(15);
	GPIOA->ODR &= ~(1<<LCD_EN);	/* LCD_EN = 0 */
	delay_ms(3); 			/* wait 3ms */
	lcd_command(0x33); //lcd init.
	delay_ms(5);
	lcd_command(0x32); //lcd init.
	delay_ms(1);
	lcd_command(0x28); // 4-bit mode, 1 line and 5x8 charactere set
	delay_ms(3);
	lcd_command(0x0e); // display on, cursor on
	delay_ms(3);
	lcd_command(0x01); // display clear
	delay_ms(3);
	lcd_command(0x06); // move right
	delay_ms(3);
}

char bcd_ascii(char valor) {
    
    return valor |= 0x30;
}

char bin_bcd(char valor, char retorno) {
    int centenas, dezenas, unidades;
    centenas = valor / 100;
    valor %= 100;
    dezenas = valor / 10;
    unidades = valor % 10;

		char result = 0;
	
    switch (retorno) {
        case 'c':
            result = bcd_ascii(centenas);
            break;
        case 'd':
            result = bcd_ascii(dezenas);
            break;
        case 'u':
            result = bcd_ascii(unidades);
            break;
        default:
            break;
    }
		
		return result;
}

void buzzer_toca_nota(uint16_t freq, uint8_t ciclo, uint16_t tempo)
{
    pwm_timer_3(freq, ciclo, 3);
    delay_ms(tempo);
}
// Função para converter valor BCD para ASCII
