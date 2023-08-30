#include <stm32f10x.h>

//Definições
#define IOPAEN 2 //habilita gpio a
#define IOPBEN 3 //habilita gpio b
#define IOPCEN 4 //habilita gpio c

// Implementações das funções
// Habilita a gpio de acordo com a letra de identificação
// a, b, c ou d.
// Ex: habilita_gpio('a');
void habilita_gpio (uint8_t gpio_id)
{
    switch (gpio_id)
    {
    case 'a':
        RCC->APB2ENR |= (1<<IOPAEN);
        break;
    
    case 'b':
        RCC->APB2ENR |= (1<<IOPBEN);
        break;

    case 'c':
         RCC->APB2ENR |= (1<<IOPCEN);
        break;
    }
}

void gpio_entrada_pp (uint8_t gpio_id, uint8_t gpio_bit)
{
    switch (gpio_id)
    {
    case 'a':
        if(gpio_bit<8)
        {
            GPIOA->CRL &=~(15<<(gpio_bit*4)); // 0000b nos bits da porta PAX 
            GPIOA->CRL |= (4<<(gpio_bit*4));  // 0011b nos bits da porta PAX
        }
        else
        {
            GPIOA->CRH &=~(15<<((gpio_bit-8)*4)); 
            GPIOA->CRH |= (4<<((gpio_bit-8)*4));
        }
        break;
    
    case 'b':
        if (gpio_bit<8)
        {
            GPIOB->CRL &=~(15<<(gpio_bit*4)); // 0000b nos bits da porta PBX 
            GPIOB->CRL |= (4<<(gpio_bit*4));  // 0011b nos bits da porta PBX
        }
        else
        {
            GPIOB->CRH &=~(15<<((gpio_bit-8)*4)); 
            GPIOB->CRH |= (4<<((gpio_bit-8)*4));
        }
        break;
    case 'c':
        if (gpio_bit<8)
        {
            GPIOC->CRL &=~(15<<(gpio_bit*4)); // 0000b nos bits da porta PBX 
            GPIOC->CRL |= (4<<(gpio_bit*4));  // 0011b nos bits da porta PBX
        }
        else
        {
            GPIOC->CRH &=~(15<<((gpio_bit-8)*4)); 
            GPIOC->CRH |= (4<<((gpio_bit-8)*4));
        }
        break;
    }
}



// Configura a gpio selecionada como saída push-pull para propósito geral a 50 MHz
// Registros CRL e CRH: |CNFXX (2-bits)|MODEXX (2-bits)|
// MODEXX = 11 (entrada)
// CNFXX = 00 (entrada flutuante)
// valor: 0011 (3) nos bits de configuração
// Ex: gpio_saida('a'); 
void gpio_saida_pp (uint8_t gpio_id, uint8_t gpio_bit)
{
    switch (gpio_id)
    {
    case 'a':
        if(gpio_bit<8)
        {
            GPIOA->CRL &=~(15<<(gpio_bit*4)); // 0000b nos bits da porta PAX 
            GPIOA->CRL |= (3<<(gpio_bit*4));  // 0011b nos bits da porta PAX
        }
        else
        {
            GPIOA->CRH &=~(15<<((gpio_bit-8)*4)); 
            GPIOA->CRH |= (3<<((gpio_bit-8)*4));
        }
        break;
    
    case 'b':
        if (gpio_bit<8)
        {
            GPIOB->CRL &=~(15<<(gpio_bit*4)); // 0000b nos bits da porta PBX 
            GPIOB->CRL |= (3<<(gpio_bit*4));  // 0011b nos bits da porta PBX
        }
        else
        {
            GPIOB->CRH &=~(15<<((gpio_bit-8)*4)); 
            GPIOB->CRH |= (3<<((gpio_bit-8)*4));
        }
        break;
    case 'c':
        if (gpio_bit<8)
        {
            GPIOC->CRL &=~(15<<(gpio_bit*4)); // 0000b nos bits da porta PBX 
            GPIOC->CRL |= (3<<(gpio_bit*4));  // 0011b nos bits da porta PBX
        }
        else
        {
            GPIOC->CRH &=~(15<<((gpio_bit-8)*4)); 
            GPIOC->CRH |= (3<<((gpio_bit-8)*4));
        }
        break;
    }
}

