#include <stm32f10x.h>

//Definições
#define IOPAEN 2 //habilita gpio a
#define IOPBEN 3 //habilita gpio b
#define IOPCEN 4 //habilita gpio c

//System tick timer
#define ST72EN 5 //configura o system tick com frequência de 72MHz e habilita o mesmo.
#define STCNTF 16//definir o bit count flag do system tic timer.
#define STSTOP 0 //desabilita o system tick timer

//General Purpose Timer
#define TIM2HAB 0 //habilitar o Timer no APB1ENR
#define TIM2CRL 0 //limpar bit UIF.
#define TIM2CRE 1 //contagem crescente do timer
#define TIM2UIF 1 //bit UIF do módulo TIM2
#define TIM2STP 0 //Parar a contagem no TIM2
#define TIM3HAB 1 //habilitar o timer 3 no APB1ENR
#define OC3PE 3 // CCR3 bufferizado / não bufferizado (CCMR2)
#define OC2PE 11 //CCR2 bufferizado / não bufferizado (CCMR1)
#define OC3M 4 // configura modo de saida (110 para pwm1)
#define OC2M 12
#define CC3E 8 // habilita/desabilita buffer de saída (CCER)
#define CC2E 4 // habilita/desabilita buffer de saída (CCER)


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


void gpio_saida_pp_alternada (uint8_t gpio_id, uint8_t gpio_bit)
{
    switch (gpio_id)
    {
    case 'a':
        if(gpio_bit<8)
        {
            GPIOA->CRL &=~(15<<(gpio_bit*4)); // 0000b nos bits da porta PAX 
            GPIOA->CRL |= (11<<(gpio_bit*4));  // 0011b nos bits da porta PAX
        }
        else
        {
            GPIOA->CRH &=~(15<<((gpio_bit-8)*4)); 
            GPIOA->CRH |= (11<<((gpio_bit-8)*4));
        }
        break;
    
    case 'b':
        if (gpio_bit<8)
        {
            GPIOB->CRL &=~(15<<(gpio_bit*4));  
            GPIOB->CRL |= (11<<(gpio_bit*4));
        }      
        else
        {
            GPIOB->CRH &=~(15<<((gpio_bit-8)*4)); 
            GPIOB->CRH |= (11<<((gpio_bit-8)*4));
        }
        break;
    case 'c':
        if (gpio_bit<8)
        {
            GPIOC->CRL &=~(15<<(gpio_bit*4));  
            GPIOC->CRL |= (11<<(gpio_bit*4));  
        }
        else
        {
            GPIOC->CRH &=~(15<<((gpio_bit-8)*4)); 
            GPIOC->CRH |= (11<<((gpio_bit-8)*4));
        }
        break;
    }
}

// Configura a gpio selecionada como entrada
// Registros CRL e CRH: |CNFXX (2-bits)|MODEXX (2-bits)|
// MODEXX = 00 (entrada)
// CNFXX = 01 (entrada flutuante)
// valor: 1000 (4) nos bits de configuração
// Ex: gpio_entrada('a'); 
void gpio_entrada (uint8_t gpio_id, uint8_t gpio_bit)
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

void gpio_entrada_analogico (uint8_t gpio_id, uint8_t gpio_bit)
{
    switch (gpio_id)
    {
    case 'a':
        if (gpio_bit<8)
        {
            GPIOA->CRL &= ~(1<<gpio_bit);
        }
        else
        {
            GPIOA->CRH &= ~(1<<(gpio_bit-8));
        }
        break;
    
    case 'b':
        if (gpio_bit<8)
        {
            GPIOB->CRL &= ~(4<<gpio_bit);
        }
        else
        {
            GPIOB->CRH &= ~(4<<(gpio_bit-8));
        }
        break;
    case 'c':
        if (gpio_bit<8)
        {
            GPIOC->CRL &= ~(4<<gpio_bit);
        }
        else
        {
            GPIOC->CRH &= ~(4<<(gpio_bit-8));
        }
        break;
    }
}

void delay_st_ms(uint16_t valor)
{

    SysTick->LOAD = (valor*72000000/1000)-1; //divide por 1000 para mili-segundos
    SysTick->CTRL = ST72EN; /* AHB clock , Enable */
    while ((SysTick->CTRL &(1<<STCNTF)) == 0); // wait COUNT flag
    SysTick->CTRL = STSTOP; /* stop the SysTick timer */
}

void delay_gpt_ms (uint16_t valor)
{
    RCC ->APB1ENR |= (1<<TIM2HAB); //habilita TIM2
    TIM2->PSC = 7200-1;
    TIM2 ->ARR = (valor*10)-1; //ARR=delay*fnew (fnew=10000, pois PSC=7200);
    TIM2 ->SR = TIM2CRL; //Limpa UIF
    TIM2 ->CR1 = TIM2CRE; //configura contagem crescente
    while ((TIM2 ->SR & TIM2UIF)==0); //Aguarda o UIF
    TIM2 ->CR1 == TIM2STP; //Pausa a contagem
}

void habilita_timer(timer_id)
{
    switch (timer_id)
    {
    case 2:
        RCC->APB1ENR |= (1<<TIM2HAB);    
        break;
    case 3:
         RCC->APB1ENR |= (1<<TIM3HAB);
         break;
    default:
        break;
    }
}

void pwm_timer_3(uint16_t freq, uint8_t ciclo, uint8_t canal)
{
    uint16_t psc = 72000000/(100*freq)-1;
    TIM3->PSC = psc; // f_new = 2kHz
    TIM3->CCMR2 &= ~((15<<OC3PE)|(7<<OC3M)); //output capture e modo PWM1
    TIM3->CCMR2 |= ((1<<OC3PE)|(6<<OC3M)); 
    TIM3->CCER |= (1<<CC3E); // buffer de saida habilitado
    TIM3->ARR = 100 - 1; // contagem máxima de 100

    switch (canal)
    {
    case 1:
        TIM3->CCR1 = ciclo; // começa com o ct de 25%
        break;
    case 2:
        TIM3->CCR2 = ciclo; // começa com o ct de 25%
        break;
    case 3: 
        TIM3->CCR3 = ciclo; // começa com o ct de 25%
        break;
    case 4:
        TIM3->CCR4 = ciclo; // começa com o ct de 25%
        break;
    default:
        break;
    }
    
    TIM3->CR1 = 1; // inicia o timer 3
}

void pwm_timer_2(uint16_t freq, uint8_t ciclo, uint8_t canal)
{
    uint16_t psc = 72000000/(100*freq)-1;
    TIM2->PSC = psc; // f_new = 2kHz
    TIM2->CCMR1 &= ~((15<<OC2PE)|(7<<OC2M)); //output capture e modo PWM1
    TIM2->CCMR1 |= ((1<<OC2PE)|(6<<OC2M)); 
    TIM2->CCER |= (1<<CC2E); // buffer de saida habilitado
    TIM2->ARR = 100 - 1; // contagem máxima de 100
    
    switch (canal)
    {
    case 1:
        TIM2->CCR1 = ciclo; // começa com o ct de 25%
        break;
    case 2:
        TIM2->CCR2 = ciclo; // começa com o ct de 25%
        break;
    case 3: 
        TIM2->CCR3 = ciclo; // começa com o ct de 25%
        break;
    case 4:
        TIM2->CCR4 = ciclo; // começa com o ct de 25%
        break;
    default:
        break;
    }
    TIM2->CR1 = 1; // inicia o timer 3
}

