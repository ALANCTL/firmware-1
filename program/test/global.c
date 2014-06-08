#include <assert.h>
#include "global.h"

global_data_t global_mav_data_list[GLOBAL_DATA_CNT];

#define QUADCOPTER 0
void init_global_data(void)
{
	/* global data information */
	reset_global_data(VEHICLE_TYPE, "vehicle_type", READ_ONLY);
	set_global_data_int(VEHICLE_TYPE, QUADCOPTER);

	/* Boot time */
	reset_global_data(BOOT_TIME, "boot_time", READ_ONLY);
	set_global_data_int(BOOT_TIME, 0);
} 


/**
  * @brief  reset data value and set global data's name and assess right
  * @param  index (int), name (char *), assess_right (AcessRight)
  * @retval None
  */
void reset_global_data(int index, char *name, AccessRight access_right)
{
	ASSERT((index >= 0) && (index < GLOBAL_DATA_CNT)); /* Index is in the range or not */
	ASSERT((access_right == READ_ONLY) || (access_right == READ_WRITE)); /* Available access right or not */

	/* Reset all data to be defalut */
	global_mav_data_list[index].name = name;
	global_mav_data_list[index].type = FLOAT;
	global_mav_data_list[index].flt_value = 0.0;
	global_mav_data_list[index].int_value = 0;
	global_mav_data_list[index].access_right = access_right;
}

/**
  * @brief  get the count of global data
  * @param  None
  * @retval global data count (int)
  */
int get_global_data_count(void)
{
	return GLOBAL_DATA_CNT;
}

/**
  * @brief  set global data's value (int version)
  * @param  index (int), value (int)
  * @retval None
  */
void set_global_data_int(int index, int value)
{
	/* Index is in the range or not */
	ASSERT((index >= 0) && (index < GLOBAL_DATA_CNT));

	/* Set the variable type and value */
	global_mav_data_list[index].type = INTEGER;
	global_mav_data_list[index].int_value = value;
}

/**
  * @brief  set global data's value (float version)
  * @param  index (int), value (int)
  * @retval None
  */
void set_global_data_float(int index, float value)
{
	/* Index is in the range or not */
	ASSERT((index >= 0) && (index < GLOBAL_DATA_CNT));

	/* Set the variable type and value */
	global_mav_data_list[index].type = FLOAT;
	global_mav_data_list[index].flt_value = value;	
}

/**
  * @brief  get the variable type of global data
  * @param  index (int)
  * @retval variable type (Type)
  */
Type get_global_data_type(int index)
{
        /* Index is in the range or not */
	ASSERT((index >= 0) && (index < GLOBAL_DATA_CNT));

	return global_mav_data_list[index].type;
}

/**
  * @brief  get the name of global data
  * @param  index (int)
  * @retval global data's name (char *)
  */
char *read_global_data_name(int index)
{
        /* Index is in the range or not */
	ASSERT((index >= 0) && (index < GLOBAL_DATA_CNT));
	
	return global_mav_data_list[index].name;
}

/**
  * @brief  get the value of global data (int version)
  * @param  index (int)
  * @retval global data's value (int)
  */
int read_global_data_int(int index)
{
        /* Index is in the range or not */
	ASSERT((index >= 0) && (index < GLOBAL_DATA_CNT));
	
	return global_mav_data_list[index].int_value;
}

/**
  * @brief  get the value of global data (float version)
  * @param  index (float)
  * @retval global data's value (float)
  */
float read_global_data_float(int index)
{
        /* Index is in the range or not */
	ASSERT((index >= 0) && (index < GLOBAL_DATA_CNT));

	return global_mav_data_list[index].flt_value;
}

/**
  * @brief  get the boot time value
  * @param  None
  * @retval boot time value (int)
  */
uint32_t get_boot_time(void)
{
	return read_global_data_int(BOOT_TIME);
}
