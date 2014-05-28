

#define USE_IMU_MPU9250

#include "stm32f4xx_conf.h"
#include "gpio.h"
#include "i2c.h"
#include "usart.h"
#include "spi.h"
#include "tim.h"
#include "mpu9250.h"
#include <stdio.h>
#include "imu.h"



void Delay_1us(vu32 nCnt_1us)
{
	volatile u32 nCnt;

	for (; nCnt_1us != 0; nCnt_1us--)
		for (nCnt = 45; nCnt != 0; nCnt--);
}
int main(void)
{
	char buffer[100];


while(1){
}


	// imu_unscaled_data_t mpu9250_unscaled_data;
	// imu_raw_data_t mpu9250_raw_data;
	// imu_calibrated_offset_t mpu9250_offset;

	// RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA | RCC_AHB1Periph_GPIOB | RCC_AHB1Periph_GPIOC|RCC_AHB1Periph_GPIOD | RCC_AHB1Periph_GPIOE,  ENABLE);
	// led_init();
	// usart_init();
	// spi_init();
	// pwm_input_output_init();
	// i2c_Init();
	// usart2_dma_init();
	// uint8_t rxdata;
	// uint8_t i2c1_data;
	
	// Delay_1us(10000);

	// imu_initialize();

	// imu_calibrate_gyro_offset(&mpu9250_offset,15000);
	// sprintf(buffer,"%d,%d,%d,\r\n",(int16_t)(mpu9250_offset.gyro[0]),(int16_t)(mpu9250_offset.gyro[1]),(int16_t)(mpu9250_offset.gyro[2]));
	// usart2_dma_send(buffer);

	// Delay_1us(10000);

	// while(1) {

	// 	if(DMA_GetFlagStatus(DMA1_Stream6,DMA_FLAG_TCIF6)!=RESET){

	// 	 buffer[7]=0;
	// 	 buffer[8]=0;
	// 	 buffer[9]=0;
	// 	 buffer[10]=0;
	// 	 buffer[11]=0;
	// 	 buffer[12]=0;
	// 	 buffer[13]=0;
	// 	sprintf(buffer,"%d,%d,%d,\r\n",(int16_t)(mpu9250_raw_data.gyro[0]*10.0),(int16_t)(mpu9250_raw_data.gyro[1]*10.0),(int16_t)(mpu9250_raw_data.gyro[2]*10.0));
		
	// 	//sprintf(buffer,"%d,\r\n",(int16_t)(mpu9250_raw_data.temp*100.0));
		
	// 	usart2_dma_send(buffer);

	// 	}


	// imu_update(&mpu9250_unscaled_data);
	// imu_scale_data(&mpu9250_unscaled_data, &mpu9250_raw_data,&mpu9250_offset);


	// 	GPIO_ToggleBits(GPIOE, GPIO_Pin_8 | GPIO_Pin_10 | GPIO_Pin_12 | GPIO_Pin_15);
	// 	Delay_1us(10000);
	// }

	return 0;
}

