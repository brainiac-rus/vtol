#include "stm32f4xx.h"

int i;
int servo_value = 1611;
int dir_flag = 1;

int main(void)
{
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN; //gpiod enable
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN; // gpiob enable;
	RCC->APB1ENR |= RCC_APB1ENR_TIM4EN;//tim4 enable
	GPIOD->MODER |= GPIO_MODER_MODER14_0;// | GPIO_MODER_MODER15_0; // as output
	GPIOD->OSPEEDR = GPIO_OSPEEDER_OSPEEDR14_0;// very high speed
	GPIOD->OTYPER &= ~GPIO_OTYPER_OT_14;//push pull
	GPIOD->PUPDR &= ~GPIO_PUPDR_PUPDR14; // no pull
	
	GPIOD->ODR = GPIO_ODR_ODR_14;// led on
	
	GPIOB->MODER |= GPIO_MODER_MODER6_1; // PB6 AF
	GPIOB->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR6_0; // very high speed
	GPIOB->OTYPER &= ~GPIO_OTYPER_OT_6;//push pull
	GPIOB->PUPDR &= ~GPIO_PUPDR_PUPDR6; // no pull
	GPIOB->AFR[0] |= (2 << 24);
	
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOHEN;
	GPIOH->MODER |= GPIO_MODER_MODER0_0; // H0 as out
	GPIOH->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR0_0; // very high speed;
	GPIOH->OTYPER &= ~GPIO_OTYPER_OT_0;
	GPIOH->PUPDR &= ~GPIO_PUPDR_PUPDR0;// no pull

  /* Time base configuration */
	TIM4->ARR = 53717; //period ticks
	TIM4->PSC = 10-1; //prescaler
	TIM4->CR1 &= ~TIM_CR1_DIR; // direction up
	TIM4->CR1 |= TIM_CR1_CEN;
	
	TIM4->CCMR1 |= TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1M_2 | TIM_CCMR1_OC1PE | TIM_CCMR1_OC1FE; //pwm mode 1
	TIM4->CCR1 = 4028;
	TIM4->CCER |= TIM_CCER_CC1E;
	TIM4->EGR |= TIM_EGR_UG;
		while(1)
		{
		if(TIM4->CNT == 53000)
		{
			if(dir_flag)
			{
				if(TIM4->CCR1 > 6500)
				{
					dir_flag = 0;
				}
				else
				{
					TIM4->CCR1 += 100;
				}
			}
			else
			{
				if(TIM4->CCR1 < 1500)
				{
					dir_flag = 1;
				}
				else
				{
					TIM4->CCR1 -= 100;
				}
			}
		}
		}
	
}
