#include "stm32f4xx.h"


GPIO_InitTypeDef  GPIO_InitStructure;


TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
TIM_OCInitTypeDef  TIM_OCInitStructure;
uint16_t PrescalerValue = 0;


int i;
int servo_value = 1611;
int dir_flag = 1;

int main(void)
{
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN; //gpiod enable
	RCC->APB1ENR |= RCC_APB1ENR_TIM4EN;//tim4 enable
	GPIOD->MODER |= GPIO_MODER_MODER14_0;// | GPIO_MODER_MODER15_0; // as output
	GPIOD->OSPEEDR = GPIO_OSPEEDER_OSPEEDR14_0;// very high speed
	GPIOD->OTYPER &= ~GPIO_OTYPER_OT_14;//push pull
	GPIOD->PUPDR &= ~GPIO_PUPDR_PUPDR14; // no pull
	
	GPIOD->ODR = GPIO_ODR_ODR_14;// led on
	
	
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
		while(1)
		{

			
			if(TIM4->CNT > servo_value)
			{
				i++;
				GPIOD->ODR &= ~GPIO_ODR_ODR_14;
				GPIOH->ODR &= ~GPIO_ODR_ODR_0;
			}
				else
			{
				GPIOH->ODR |= GPIO_ODR_ODR_0;
				GPIOD->ODR |= GPIO_ODR_ODR_14;
			} 
			if(dir_flag)
			{
				if(servo_value > 5318)
				{
					dir_flag = 0;
				}
				else
				{
					servo_value += 3;
				}
			}
			else
			{
					if(servo_value < 1611 )
				{
					dir_flag = 1;
				}
				else
				{
					servo_value -= 3;
				}
			}
					//for(i = 0; i < 1000000; i++);
			//GPIOD->ODR = GPIO_ODR_ODR_14;
			//GPIO_SetBits(GPIOD, GPIO_Pin_14);
			//for(i = 0; i < 1000000; i++);
			//GPIOD->ODR &= ~GPIO_ODR_ODR_14;
			//GPIO_ResetBits(GPIOD, GPIO_Pin_14);
		}
	
}
