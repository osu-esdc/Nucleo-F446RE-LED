//	Author: Gabriel Rodgers, with modifications by Quinn Yockey
//	Date: 2025-04-24
//	Purpose: To get the LD2 on the Nucleo-F446RE to turn on. 

// #include <stdint.h>

#define GPIOA 0x40020000
#define RCC 0x40023800

#define GPIOA_ODR (*((volatile unsigned *) (GPIOA + 0x14)))
#define GPIOA_MODER (*((volatile unsigned *) GPIOA))
#define GPIOA_OTYPER (*((volatile unsigned *) (GPIOA + 0x04)))
#define GPIOA_OSPEEDR (*((volatile unsigned *) (GPIOA + 0x08)))
#define GPIOA_PUPDR (*((volatile unsigned *) (GPIOA + 0x0C)))
#define GPIOA_BSRR (*((volatile unsigned *) (GPIOA + 0x18)))

//define the first register in the RCC memory section
//this method directly dereferences the memory itself to access the registers
#define RCC_CR (*((volatile unsigned *) RCC)) 	//sysclk config
#define RCC_CFGR (*((volatile unsigned *) (RCC + 0x08)))	//clk config
#define RCC_AHB1ENR (*((volatile unsigned *) (RCC + 0x30)))	//clk enable for peripherals
#define RCC_AHB2ENR (*((volatile unsigned *) (RCC + 0x34)))	//clk enable for peripherals
#define RCC_APB1ENR (*((volatile unsigned *) (RCC + 0x40)))	//clk enable for peripherals

void led_on(void){

	//set LED pin (GPIOA pin 5) to be general purpose output mode
	GPIOA_MODER |= (1 << 10);
	GPIOA_MODER &= ~(1 << 11);

	GPIOA_OTYPER &= ~(1 << 5); // set PA5 to be push-pull
				   
	GPIOA_ODR |= (1 << 5); // set led ON
}

int main(void) {
	
	//enable clk for peripherals (GPIO Port A)
	RCC_AHB1ENR |= (1 << 0);	

	for(unsigned i=0; i < 2; i++); 

	led_on();

	unsigned val = 0;

	while (1) {
		
		if (val == 100000) {

		//	GPIOA_ODR ^= (1 << 5); // set led ON
			val = 0;
		}

		val++;
	}

	return 0;
}
