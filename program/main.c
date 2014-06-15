//#define DEBUG
#include "stm32f4xx_conf.h"
#include "../common/delay.h"
#include "gpio.h"
#include "led.h"
#include "i2c.h"
#include "usart.h"
#include "spi.h"
#include "tim.h"
#include <stdio.h>
#include "attitude_estimator.h"
#include "vertical_estimator.h"
#include "attitude_stabilizer.h"
#include "pwm.h"
#include "radio_control.h"
#include "test_common.h"
extern uint8_t estimator_trigger_flag;
void gpio_rcc_init(void);
void gpio_rcc_init(void)
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA | RCC_AHB1Periph_GPIOB | 
		RCC_AHB1Periph_GPIOC | RCC_AHB1Periph_GPIOD | RCC_AHB1Periph_GPIOE,  ENABLE);	
}

int main(void)
{
	uint8_t buffer[100];
	imu_unscaled_data_t imu_unscaled_data;
	imu_data_t imu_raw_data;
	imu_data_t imu_filtered_data;
	imu_calibrated_offset_t imu_offset;
	attitude_t attitude;
	//vector3d_t lowpassed_acc_data;
	vector3d_t predicted_g_data;

	vertical_data vertical_raw_data;
	vertical_data vertical_filtered_data;
	radio_controller_t my_rc;
	attitude_stablizer_pid_t pid_roll_info;
	attitude_stablizer_pid_t pid_pitch_info;
	attitude_stablizer_pid_t pid_yaw_info;


	pid_roll_info.kp =0.20;
	pid_roll_info.kd =0.08;
	pid_roll_info.ki =0.0;
	pid_roll_info.setpoint =0.0;

	pid_pitch_info.kp =0.20;
	pid_pitch_info.kd =0.08;
	pid_pitch_info.ki =0.0;
	pid_pitch_info.setpoint =0.0;

	pid_yaw_info.kp =0.0;
	pid_yaw_info.kd =1.2;
	pid_yaw_info.ki =0.0;
	pid_yaw_info.setpoint =0.0;

	attitude_estimator_init(&attitude,&imu_raw_data, &imu_filtered_data,&predicted_g_data);
	vertical_estimator_init(&vertical_raw_data,&vertical_filtered_data);

	gpio_rcc_init();
	led_init();
	usart_init();
	spi_init();
	pwm_input_output_init();
	init_pwm_motor();
	i2c_Init();
	usart2_dma_init();

	cycle_led(5);
	//Delay_1us(2000000);
	imu_initialize(&imu_offset,30000);

	check_rc_safety_init(&my_rc);

 	//barometer_initialize();

	while (1) {


		LED_OFF(LED4);
		if (DMA_GetFlagStatus(DMA1_Stream6, DMA_FLAG_TCIF6) != RESET) {

			buffer[7] = 0;buffer[8] = 0;buffer[9] = 0;buffer[10] = 0;buffer[11] = 0;buffer[12] = 0;	buffer[13] = 0;

			sprintf((char *)buffer, "%d,%d,%d,%d\r\n",
				(int16_t)(attitude.roll * 100.0f),
				(int16_t)(attitude.pitch * 100.0f),
				(int16_t)(vertical_filtered_data.Z * 1.0f),
				(int16_t)(vertical_raw_data.Zd * 1.0f));

			// sprintf((char *)buffer, "%d,%d,%d,%d\r\n",
			// 	(int16_t)(imu_raw_data.gyro[0] * 1.0f +100.0f),
			// 	(int16_t)(imu_filtered_data.gyro[0] * 1.0f - 100.0f),
			// 	(int16_t)(imu_filtered_data.gyro[2] * 1.0f),
			// 	(int16_t)(vertical_raw_data.Zd * 1.0f));

			usart2_dma_send(buffer);

		}	


		attitude_update(&attitude,&imu_filtered_data, &predicted_g_data,&imu_unscaled_data,&imu_raw_data,&imu_offset);
		vertical_sense(&vertical_filtered_data,&vertical_raw_data,&attitude, &imu_raw_data);

		PID_attitude_roll (&pid_roll_info,&imu_filtered_data,&attitude);
		PID_attitude_pitch(&pid_pitch_info,&imu_filtered_data,&attitude);
		PID_attitude_yaw  (&pid_yaw_info,&imu_filtered_data,&attitude);
		PID_output(&my_rc,&pid_roll_info,&pid_pitch_info,&pid_yaw_info);

		update_radio_control_input(&my_rc);
		PID_attitude_rc_pass_command(&pid_roll_info,&pid_pitch_info,&pid_yaw_info,&my_rc);

		LED_ON(LED4);

		while(estimator_trigger_flag==0);
		estimator_trigger_flag=0;


#ifdef DEBUG
		test_bound();
#endif
	}

	return 0;
}

