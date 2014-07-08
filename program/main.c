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

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "timers.h"

#include "global.h"
#include "communication.h"

extern uint8_t estimator_trigger_flag;

/* FreeRTOS */
extern xSemaphoreHandle serial_tx_wait_sem;
extern xQueueHandle serial_rx_queue;

xTimerHandle xTimers[1];

void vApplicationStackOverflowHook( xTaskHandle xTask, signed char *pcTaskName );
void vApplicationIdleHook(void);
void vApplicationMallocFailedHook(void);

void gpio_rcc_init(void);
void gpio_rcc_init(void)
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA | RCC_AHB1Periph_GPIOB | 
		RCC_AHB1Periph_GPIOC | RCC_AHB1Periph_GPIOD | RCC_AHB1Periph_GPIOE,  ENABLE);	
}

void vApplicationStackOverflowHook( xTaskHandle xTask, signed char *pcTaskName )
{
	while(1);

}
void vApplicationIdleHook(void)
{
	
}
void vApplicationMallocFailedHook(void)
{
	while(1);
}

void flight_control_task(void)
{

}

#define BOOT_TIME_TIMER 0
static uint32_t counter = 0;
void boot_time_timer(void)
{
	counter++;
	set_global_data_int(BOOT_TIME, counter);
}

int main(void)
{
	vSemaphoreCreateBinary(serial_tx_wait_sem);
	serial_rx_queue = xQueueCreate(1, sizeof(serial_msg));

	/* Global data initialazition */
	init_global_data();

	/* Hardware initialization */
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
	gpio_rcc_init();
	led_init();
	usart_init();
	spi_init();
	pwm_input_output_init();
	init_pwm_motor();
	i2c_Init();
	usart2_dma_init();


	cycle_led(5);

	/* Register the FreeRTOS task */
	/* Flight control task */
	xTaskCreate(
		(pdTASK_CODE)flight_control_task,
		(signed portCHAR*)"flight control task",
		2048,
		NULL,
		tskIDLE_PRIORITY + 9,
		NULL
	);

	/* Ground station communication task */	
        xTaskCreate(
		(pdTASK_CODE)ground_station_task,
		(signed portCHAR *)"ground station send task",
		2048,
		NULL,
		tskIDLE_PRIORITY + 5,
		NULL
	);

	xTaskCreate(
		(pdTASK_CODE)mavlink_receiver_task,
		(signed portCHAR *) "ground station receive task",
		2048,
		NULL,
		tskIDLE_PRIORITY + 6, NULL
	);

	/* Timer */
	xTimers[BOOT_TIME_TIMER] = xTimerCreate(
		    (signed portCHAR *) "boot time",
		    configTICK_RATE_HZ,
		    pdTRUE,
		    BOOT_TIME_TIMER,
		    (tmrTIMER_CALLBACK)boot_time_timer
	);

	xTimerStart(xTimers[BOOT_TIME_TIMER], 0);
	vTaskStartScheduler();

	return 0;
}

